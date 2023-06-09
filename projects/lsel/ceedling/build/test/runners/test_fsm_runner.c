/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_test_fsm.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_fsm_new_nullWhenNullTransition(void);
extern void test_fsm_nullWhenEmptyTransition(void);
extern void test_fsm_validTransitionNoOutput(void);
extern void test_fsm_validTransitionWithOutput(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_test_fsm_Init();
}
static void CMock_Verify(void)
{
  mock_test_fsm_Verify();
}
static void CMock_Destroy(void)
{
  mock_test_fsm_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_fsm.c");
  run_test(test_fsm_new_nullWhenNullTransition, "test_fsm_new_nullWhenNullTransition", 48);
  run_test(test_fsm_nullWhenEmptyTransition, "test_fsm_nullWhenEmptyTransition", 57);
  run_test(test_fsm_validTransitionNoOutput, "test_fsm_validTransitionNoOutput", 69);
  run_test(test_fsm_validTransitionWithOutput, "test_fsm_validTransitionWithOutput", 89);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}