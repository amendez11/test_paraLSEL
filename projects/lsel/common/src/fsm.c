#include <stdlib.h>
#include "fsm.h"

#include <string.h>
#include <stdio.h>

#ifdef TEST
  #include "../../test/support/test_fsm.h"
#else

  /**
   * @brief Replacement of builtin malloc
   * 
   * Replaced by a mock in tests, so that allocation
   * faults can be simulated
   * 
   * @param s Required space in bytes
   * @return void* Pointer to the newly allocated space
   */
  void* fsm_malloc(size_t s) {
    return malloc(s);
  }
#endif

/**
 * @brief Check if an state is valid
 * 
 * A state is considered to be valid if it
 * is strictly less than the maximum state
 * and non-negative
 * 
 * @param state State to be checked
 * @param n_states Maximum allowed state (excluded)
 * @return int 1 if valid, otherwise 0
 */
static int check_state(int state, size_t n_states)
{
  return state >= 0 && state < (int)(n_states);
}

/**
 * @brief Check if a transition definition is valid
 * 
 * A transition is considered to be valid if both source
 * and destination states are valid
 * 
 * @param transition Read only pointer to the transition to be checked
 * @param n_states Maximum allowed state (excluded)
 * @return int 1 if valid, otherwise 0
 */
static int check_transition(const fsm_trans_t* transition, size_t n_states)
{
  if(!check_state(transition->orig_state, n_states))
    return 0;

  if(!check_state(transition->dest_state, n_states))
    return 0;

  return 1;
}

/**
 * @brief Check if transition list has an array terminator at the end
 * 
 * A transition is considered to be an array terminator
 * if source and destination states are -1 and the callback
 * function pointers are NULL. This function will check if the
 * last element of the array adjusts to this definition
 * 
 * @param tt Read only pointer to the transition to be checked
 * @param n_transitions Number of transitions in the array, terminator included
 * @return int 1 if terminator is present at the end, 0 otherwise
 */
static int check_terminator(const fsm_trans_t* tt, size_t n_transitions)
{
  static const fsm_trans_t terminator = {-1, NULL, -1, NULL};
  const fsm_trans_t* last = tt + n_transitions - 1;
  return last->orig_state == terminator.orig_state &&
         last->in == terminator.in &&
         last->dest_state == terminator.dest_state &&
         last->out == terminator.out;
}

/**
 * @brief Checks if the transition table is well defined
 * 
 * A transition list is well defined if it is correctly terminated 
 * (see \ref check_terminator) and all other transitions are valid 
 * (see \ref check_transition)
 * 
 * @param tt Transition table to be checked
 * @param n_transitions Number of transitions in the array, terminator included
 * @param n_states Maximum state (excluded)
 * @return int 1 if transtion table is valid, 0 otherwise
 */
static int check_args(fsm_trans_t* tt, size_t n_transitions, size_t n_states)
{
  if (!tt || n_transitions <= 1)
    return 0;

  if(!check_terminator(tt, n_transitions))
    return 0;

  for(size_t i = 0; i < n_transitions-1; ++i)
  {
    if(!check_transition(tt+i, n_states))
      return 0;
  }
  return 1;
}

/**
 * @brief Initialize FSM object.
 * 
 * check_args is assumed to return 1 for these arguments.
 * The initial state of the FSM will be the first state
 * of origin of the transition table
 * 
 * @param f The FSM to be initialized
 * @param tt The transition table
 * @param n_transitions Length of the transition table
 * @param n_states Maximum state (excluded)
 */
static void initialize(fsm_t* f, fsm_trans_t* tt, size_t n_transitions, size_t n_states)
{
  f->tt = tt;
  f->current_state = tt[0].orig_state;
}

/**
 * @brief Creates a new FSM object
 * 
 * A FSM object is allocated in heap and it is initialized
 * accordig to the provided parameters. When input parameters 
 * are not valid (see \ref check_args) the FSM object is not allocated
 * and a NULL pointer is returned
 * 
 * @param tt The transition table
 * @param n_transitions Length of the transition table
 * @param n_states Maximum state (excluded)
 * @return fsm_t* The newly cleated FSM
 */
fsm_t*
fsm_new (fsm_trans_t* tt, size_t n_transitions, size_t n_states)
{
  fsm_t* result = NULL;
  if(check_args(tt, n_transitions, n_states))
  {
    result = (fsm_t*) fsm_malloc (sizeof (fsm_t));
    if(result) {
      initialize(result, tt, n_transitions, n_states);
    }
  }

  return result;
}

/**
 * @brief Initializes an existing FSM object
 * 
 * Initializes the state of an user allocated FSM object.
 * When input parameters are not valid (see \ref check_args) 
 * the FSM object is not initialized and 0 is returned
 * 
 * @param f Pointer to the FSM to be initialzied
 * @param tt The transition table
 * @param n_transitions Length of the transition table
 * @param n_states Maximum state (excluded)
 * @return int 1 if sucess, 0 when failure
 */
int
fsm_init (fsm_t* f, fsm_trans_t* tt, size_t n_transitions, size_t n_states)
{
  int result = 0;
  if(f && check_args(tt, n_transitions, n_states))
  {
    initialize(f, tt, n_transitions, n_states);
    result = 1;
  }

  return result;
}

/**
 * @brief Release a FSM object
 * 
 * This functions destroys and frees the space
 * allocated for an FSM object
 * 
 * @param f The FSM to be destroyed
 */
void
fsm_destroy (fsm_t* f)
{
  free(f);
}

/**
 * @brief Fire a FSM object
 * 
 * The provided FSM is fired. Only guard functions belonging to the
 * current source state are checked. If a guard function evaluated
 * to true (or it is NULL), the transition is executed. Current state
 * is updated and the output function is called when provided
 * 
 * @param f The FSM to be fired.
 * @return int 1 if transition occurred. -1 if the FSM is in its 
 * final state (and hence there will not be transitions anymore)
 * 0 if no transition ocurred.
 */
int
fsm_fire (fsm_t* f)
{
  fsm_trans_t* t;
  int available = 0;
  for (t = f->tt; t->orig_state >= 0; ++t) {
    if (f->current_state == t->orig_state) {
      available = 1;
      int do_transition;
      if(t->in) {
        do_transition = t->in(f);
      } else {
        do_transition = 1;
      }

      if(do_transition) {
        f->current_state = t->dest_state;
        if (t->out)
          t->out(f);
        return 1;
      }
    }
  }

  return available ? 0 : -1;
}
