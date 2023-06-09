#include "unity.h"

#include "fsm.h"
#include "mock_test_fsm.h"

/**
 * @file test_fsm.c
 * @author Andres Alvarez Mendez
 * @author Oier Lauzirika Zarrabeitia
 * @brief Tests for fsm.h module
 * @version 0.1
 * @date 2023-04-24
 * 
 * 1. La transición inválida final es {-1, NULL, -1, NULL}
 * 2. Cualquier otra transición debe tener un estado válido de entrada y salida
 * 3. Las funciones de guarda y actualización pueden ser NULL
 * 4. Puede haber varias máquinas de estados simultáneamente sin que afecte una a otra si no tienen conexión externa
 * 5. Si hay datos erróneos no debe reservar la memoria
 * 6. Si falla en la reserva, devuelve NULL
 * 7. Si La funcion de inicialización falla o hay datos erróneos, devuelve false
 * 8. La memoria pasada no es NULL (para la estática)
 * 9. La tabla de transiciones no es NULL
 * 10. Todos los estados son naturales e inferiores al estado máximo
 * 11. El estado inicial es el estado de origen de la primera transición
 * 12. Solo se comprueban las funciones de guarda de las transiciones con estado de origen igual al de la máquina de estados
 * 13. Si para una transición a comprobar tiene una función de guarda NULL, se cumple siempre
 * 14. Si para una transición a comprobar tiene una función de guarda, se ejecuta la función y si devuelve distinto de 0, se cumple.
 * 15. Si se cumple, se cambia el estado actual al de destino, no se comprueban más transiciones y se ejecuta la función de actualización, si es distinto de NULL y devuelve 1
 * 16. Si ninguna transición tiene un estado de origen coincidente con el estado actual, la función de comprobación de transiciones devuelve -1.
 * 17. Si hay transiciones pero no se cumplen las condiciones, devuelve 0
 */

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * @brief Comprueba que la funcion de fsm_new devuelve NULL si la tabla de transiciones es NULL 
 * 
 * Requisitos comprobados: 5, 9
 * 
 */

void test_fsm_new_nullWhenNullTransition(void)
{
    fsm_t *f = (fsm_t*)1;

    f = fsm_new(NULL);

    TEST_ASSERT_EQUAL (NULL, f);
}

void test_fsm_nullWhenEmptyTransition(void)
{
    fsm_trans_t tt[] = {{-1, NULL, -1, NULL}};

    fsm_t *f = (fsm_t*)1;

    f = fsm_new(tt);

    //TEST_ASSERT_EQUAL (XXX);
    TEST_FAIL_MESSAGE("Implement the test");
}

void test_fsm_validTransitionNoOutput(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);

    fsm_t *f = (fsm_t*)1;

    f = fsm_new(tt);
    fsm_fire(f);

    TEST_ASSERT_NOT_NULL (f);
    TEST_ASSERT_EQUAL (1, f->current_state);

    fsm_destroy(f);
}

void test_fsm_validTransitionWithOutput(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, do_nothing},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();

    fsm_t *f = (fsm_t*)1;

    f = fsm_new(tt);
    fsm_fire(f);

    TEST_ASSERT_NOT_NULL (f);
    TEST_ASSERT_EQUAL (1, f->current_state);

    fsm_destroy(f);
}
