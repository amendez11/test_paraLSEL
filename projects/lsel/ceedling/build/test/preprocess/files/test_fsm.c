#include "mock_test_fsm.h"
#include "../common/include/fsm.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}

void test_fsm_new_nullWhenNullTransition(void)

{

    fsm_t *f = (fsm_t*)1;



    f = fsm_new(

               ((void *)0)

                   );



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_INT);

}



void test_fsm_nullWhenEmptyTransition(void)

{

    fsm_trans_t tt[] = {{-1, 

                            ((void *)0)

                                , -1, 

                                      ((void *)0)

                                          }};



    fsm_t *f = (fsm_t*)1;



    f = fsm_new(tt);





    UnityFail( (("Implement the test")), (UNITY_UINT)(66));

}



void test_fsm_validTransitionNoOutput(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(76, 1);



    fsm_t *f = (fsm_t*)1;



    f = fsm_new(tt);

    fsm_fire(f);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(83))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}



void test_fsm_validTransitionWithOutput(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(96, 1);

    do_nothing_CMockExpectAnyArgs(97);



    fsm_t *f = (fsm_t*)1;



    f = fsm_new(tt);

    fsm_fire(f);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(104))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}
