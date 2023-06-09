#include <stdlib.h>
#include "fsm.h"

fsm_t*
fsm_new (fsm_trans_t* tt)
{
  fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));
  fsm_init (f, tt);
  return f;
}

/**
*/
void
fsm_init (fsm_t* f, fsm_trans_t* tt)
{
  f->tt = tt;
  f->current_state = tt[0].orig_state;
  
}

void
fsm_destroy (fsm_t* f)
{
  free(f);
}

void
fsm_fire (fsm_t* f)
{
  fsm_trans_t* t;
  for (t = f->tt; t->orig_state >= 0; ++t) {
    if ((f->current_state == t->orig_state) && t->in(f)) {
      f->current_state = t->dest_state;
      if (t->out)
        t->out(f);
      break;
    }
  }
}

