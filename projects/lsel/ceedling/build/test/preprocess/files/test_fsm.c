#include "build/test/mocks/mock_test_fsm.h"
#include "../common/include/fsm.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






static void* test_malloc_wrapper(size_t s, int n) {

    return malloc(s);

}



void setUp(void)

{

}



void tearDown(void)

{

}















void test_fsm_new_nullWhenNullTransition(void)

{

    fsm_t *f = (fsm_t*)1;



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(

               ((void *)0)

                   , 0, 0);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_init_falseWhenNullFsm(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {2, 

           ((void *)0)

               , -1, 

                     ((void *)0)

                         }

    };



    int res = fsm_init(

                      ((void *)0)

                          , tt, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_init_falseWhenNullTransitions(void)

{

    fsm_t f;

    int res = fsm_init(&f, 

                          ((void *)0)

                              , 0, 0);



    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_new_nullWhenInvalidTransitionTerminator(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {2, 

           ((void *)0)

               , -1, 

                     ((void *)0)

                         }

    };



    fsm_t *f = (fsm_t*)1;



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT);

}













void test_fsm_init_falseWhenInvalidTransitionTerminator(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {2, 

           ((void *)0)

               , -1, 

                     ((void *)0)

                         }

    };



    fsm_t f;

    int res = fsm_init(&f, tt, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_new_nullWhenEmptyTransition(void)

{

    fsm_trans_t tt[] = {{-1, 

                            ((void *)0)

                                , -1, 

                                      ((void *)0)

                                          }};



    fsm_t *f = (fsm_t*)1;



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt, 1, 0);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_init_falseWhenEmptyTransition(void)

{

    fsm_trans_t tt[] = {{-1, 

                            ((void *)0)

                                , -1, 

                                      ((void *)0)

                                          }};



    fsm_t f;

    int res = fsm_init(&f, tt, 1, 0);



    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(169), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_new_nullWhenInvalidOriginState(void)

{

    fsm_t *f = (fsm_t*)1;



    fsm_trans_t tt1[] = {

        {1, is_true, 0, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt1, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_INT);



    fsm_trans_t tt2[] = {

        {-1, is_true, 0, 

                        ((void *)0)

                            },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt2, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(201), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_init_falseWhenInvalidOriginState(void)

{

    int res;

    fsm_t f;



    fsm_trans_t tt1[] = {

        {1, is_true, 0, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    res = fsm_init(&f, tt1, 2, 1);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(223), UNITY_DISPLAY_STYLE_INT);



    fsm_trans_t tt2[] = {

        {-1, is_true, 0, 

                        ((void *)0)

                            },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    res = fsm_init(&f, tt2, 2, 1);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(231), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_new_nullWhenInvalidDestinationState(void)

{

    fsm_t *f = (fsm_t*)1;



    fsm_trans_t tt1[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt1, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(256), UNITY_DISPLAY_STYLE_INT);



    fsm_trans_t tt2[] = {

        {0, is_true, -1, 

                        ((void *)0)

                            },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt2, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(266), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_init_falseWhenInvalidDestinationState(void)

{

    int res;

    fsm_t f;



    fsm_trans_t tt1[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    res = fsm_init(&f, tt1, 2, 1);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(288), UNITY_DISPLAY_STYLE_INT);



    fsm_trans_t tt2[] = {

        {0, is_true, -1, 

                        ((void *)0)

                            },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    res = fsm_init(&f, tt2, 2, 1);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(296), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_new_nonNullWhenNullTransitionCondition(void)

{

    fsm_trans_t tt[] = {

        {0, 

           ((void *)0)

               , 0, 

                    ((void *)0)

                        },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_t *f = (fsm_t*)1;



    fsm_malloc_Stub(test_malloc_wrapper);

    f = fsm_new(tt, 2, 1);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(318))));}} while(0);



    fsm_destroy(f);

}

void test_fsm_init_trueWhenNullTransitionCondition(void)

{

    fsm_trans_t tt[] = {

        {0, 

           ((void *)0)

               , 0, 

                    ((void *)0)

                        },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_t f;

    int res = fsm_init(&f, tt, 2, 1);



    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(340), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_new_validInitialState(void)

{

    fsm_trans_t tt[] = {

        {0x12345678, is_true, 0, 

                                ((void *)0)

                                    },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_malloc_Stub(test_malloc_wrapper);

    fsm_t* f = fsm_new(tt, 2, 0x12345679);

    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(358))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((0x12345678)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(359), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}

void test_fsm_init_validInitialState(void)

{

    fsm_trans_t tt[] = {

        {0x12345678, is_true, 0, 

                                ((void *)0)

                                    },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_t f;

    int res = fsm_init(&f, tt, 2, 0x12345679);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(380), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x12345678)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(381), UNITY_DISPLAY_STYLE_INT);

}

void test_fsm_fire_validTransitionNoCondition(void)

{

    fsm_trans_t tt[] = {

        {0, 

           ((void *)0)

               , 1, 

                    ((void *)0)

                        },

        {1, 

           ((void *)0)

               , 0, 

                    ((void *)0)

                        },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_t f;

    int res;

    res = fsm_init(&f, tt, 3, 2);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(403), UNITY_DISPLAY_STYLE_INT);



    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(406), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(407), UNITY_DISPLAY_STYLE_INT);

    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(409), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(410), UNITY_DISPLAY_STYLE_INT);

}













void test_fsm_fire_validTransitionNoOutput(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {1, is_true, 0, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(426, 1);



    fsm_t f;

    int res;

    res = fsm_init(&f, tt, 3, 2);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(431), UNITY_DISPLAY_STYLE_INT);



    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(434), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(435), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_fire_validTransitionWithOutput(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {1, is_true, 0, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(452, 1);

    do_nothing_CMockExpectAnyArgs(453);



    fsm_t f;

    int res;

    res = fsm_init(&f, tt, 3, 2);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(458), UNITY_DISPLAY_STYLE_INT);



    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(461), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(462), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_fire_noTransition(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {1, is_true, 0, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(479, 0);



    fsm_t f;

    int res;

    res = fsm_init(&f, tt, 3, 2);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(484), UNITY_DISPLAY_STYLE_INT);



    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((0)), (

   ((void *)0)

   ), (UNITY_UINT)(487), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(488), UNITY_DISPLAY_STYLE_INT);

}













void test_fsm_fire_endState(void)

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



    is_true_CMockExpectAnyArgsAndReturn(503, 1);



    fsm_t f;

    int res;

    res = fsm_init(&f, tt, 2, 2);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(508), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(509), UNITY_DISPLAY_STYLE_INT);



    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(512), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(513), UNITY_DISPLAY_STYLE_INT);



    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((-1)), (

   ((void *)0)

   ), (UNITY_UINT)(516), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(517), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_memory_full(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {1, is_true, 0, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_malloc_CMockIgnoreAndReturn(534, 

   ((void *)0)

   );

    fsm_t* fsm = fsm_new(tt, 3, 2);



    UnityAssertEqualNumber((UNITY_INT)((fsm)), (UNITY_INT)((

   ((void *)0)

   )), (

   ((void *)0)

   ), (UNITY_UINT)(537), UNITY_DISPLAY_STYLE_INT);

}















void test_fsm_fire_onlyCheckCurrentGuard(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {1, is_true2, 2, 

                        ((void *)0)

                            },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    fsm_t f;

    int res;

    res = fsm_init(&f, tt, 3, 3);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(557), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(558), UNITY_DISPLAY_STYLE_INT);



    is_true_CMockExpectAnyArgsAndReturn(560, 1);

    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(562), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(563), UNITY_DISPLAY_STYLE_INT);



    is_true2_CMockExpectAnyArgsAndReturn(565, 1);

    res = fsm_fire(&f);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(567), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((f.current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(568), UNITY_DISPLAY_STYLE_INT);

}













void test_fsm_concurrent(void) {

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {1, is_true, 2, 

                       ((void *)0)

                           },

        {2, is_true, 3, 

                       ((void *)0)

                           },

        {3, is_true, 0, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    int res;

    fsm_t fs[2];

    res = fsm_init(fs+0, tt, 5, 4);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(588), UNITY_DISPLAY_STYLE_INT);

    res = fsm_init(fs+1, tt, 5, 4);

    UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

   ((void *)0)

   ), (UNITY_UINT)(590), UNITY_DISPLAY_STYLE_INT);



    for(int i = 0; i < 16; ++i) {

        is_true_CMockExpectAnyArgsAndReturn(593, 1);

        res = fsm_fire(fs+0);

        UnityAssertEqualNumber((UNITY_INT)((res)), (UNITY_INT)((1)), (

       ((void *)0)

       ), (UNITY_UINT)(595), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((fs[1].current_state)), (

       ((void *)0)

       ), (UNITY_UINT)(596), UNITY_DISPLAY_STYLE_INT);

    }

}
