#include "unity.h"

#include "fsm.h"
#include "mock_test_fsm.h"

#include <stdlib.h>

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

static void* test_malloc_wrapper(size_t s, int n) {
    return malloc(s);
}

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

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(NULL, 0, 0);

    TEST_ASSERT_EQUAL (NULL, f);
}

/**
 * @brief Comprueba que la función de inicialización devuelve false si el puntero a la maquina de estado es NULL
 * 
 * Requisitos comprobados: 8
 * 
 */
void test_fsm_init_falseWhenNullFsm(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {2, NULL, -1, NULL}
    };

    int res = fsm_init(NULL, tt, 2, 1);

    TEST_ASSERT_EQUAL (res, 0);
}

/**
 * @brief Función de inicializacion devuelve false si la tabla de transiciones es nula
 * 
 * Requisito(s) comprobadors: 7
 * 
 */

void test_fsm_init_falseWhenNullTransitions(void)
{
    fsm_t f;
    int res = fsm_init(&f, NULL, 0, 0);

    TEST_ASSERT_EQUAL (res, 0);
}

/**
 * @brief La creación de una nueva maquina de estado devuelve un puntero a NULL si el estado invalido no tiene la forma correcta
 * 
 * Requisito(s) comprobados: 1, 5 
 * 
 */
void test_fsm_new_nullWhenInvalidTransitionTerminator(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {2, NULL, -1, NULL}
    };

    fsm_t *f = (fsm_t*)1;

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt, 2, 1);

    TEST_ASSERT_EQUAL (NULL, f);
}
/**
 * @brief Iniciacilización devuelve false si el estado invalido tiene la forma incorrecta. 
 * 
 * Requisito(s) comprobado: 1, 7
 * 
 */
void test_fsm_init_falseWhenInvalidTransitionTerminator(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {2, NULL, -1, NULL}
    };

    fsm_t f;
    int res = fsm_init(&f, tt, 2, 1);

    TEST_ASSERT_EQUAL (res, 0);
}
/**
 * @brief El puntero de la maquina de estados nueva es NULL si unicamente se tiene el estado invalido en la tabla de transiciones. 
 * Nota: Si bien tener unicamente la transición invalida cumple con los requisitos 10 y 11, consideramos que eso incumple el requisito 11 
 * y además no tiene sentido crear una maquina de estados con solo la transición invalida.
 * 
 * Requisito(s) comprobados: 5, 11
 * 
 */
void test_fsm_new_nullWhenEmptyTransition(void)
{
    fsm_trans_t tt[] = {{-1, NULL, -1, NULL}};

    fsm_t *f = (fsm_t*)1;

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt, 1, 0);

    TEST_ASSERT_EQUAL (NULL, f);
}

/**
 * @brief La inicialización devuelve false si solo se tiene el estado invalido. Mismo razonamiento que el test anterior
 * 
 * Requisito(s): 11
 * 
 */


void test_fsm_init_falseWhenEmptyTransition(void)
{
    fsm_trans_t tt[] = {{-1, NULL, -1, NULL}};

    fsm_t f;
    int res = fsm_init(&f, tt, 1, 0);

    TEST_ASSERT_EQUAL (res, 0);
}

/**
 * @brief La creación de la nueva maquina de estados devuelve un puntero NULL si el estado de origen es invalido (Estado <0 || Estado >= max_estado)
 * 
 * Requisito(s): 5, 10
 * 
 */

void test_fsm_new_nullWhenInvalidOriginState(void)
{
    fsm_t *f = (fsm_t*)1;

    fsm_trans_t tt1[] = {
        {1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt1, 2, 1);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_trans_t tt2[] = {
        {-1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt2, 2, 1);

    TEST_ASSERT_EQUAL (NULL, f);
}

/**
 * @brief La inicialización devuelve un false si el estado de origen es invalido (Estado <0 || Estado >= max_estado)
 * 
 * Requisito(s): 10
 * 
 */


void test_fsm_init_falseWhenInvalidOriginState(void)
{
    int res;
    fsm_t f;

    fsm_trans_t tt1[] = {
        {1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    res = fsm_init(&f, tt1, 2, 1);
    TEST_ASSERT_EQUAL (res, 0);

    fsm_trans_t tt2[] = {
        {-1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };
    
    res = fsm_init(&f, tt2, 2, 1);
    TEST_ASSERT_EQUAL (res, 0);
}



/**
 * @brief La creación de la nueva maquina de estados devuelve un puntero NULL si el estado de destino es invalido (Estado <0 || Estado >= max_estado)
 * 
 * Requisito(s): 5, 10
 * 
 */


void test_fsm_new_nullWhenInvalidDestinationState(void)
{
    fsm_t *f = (fsm_t*)1;

    fsm_trans_t tt1[] = {
        {0, is_true, 1, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt1, 2, 1);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_trans_t tt2[] = {
        {0, is_true, -1, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt2, 2, 1);

    TEST_ASSERT_EQUAL (NULL, f);
}

/**
 * @brief La inicialización devuelve un flase si el estado de destino es invalido (Estado <0 || Estado >= max_estado)
 * 
 * Requisito(s): 10
 * 
 */


void test_fsm_init_falseWhenInvalidDestinationState(void)
{
    int res;
    fsm_t f;

    fsm_trans_t tt1[] = {
        {0, is_true, 1, NULL},
        {-1, NULL, -1, NULL}
    };

    res = fsm_init(&f, tt1, 2, 1);
    TEST_ASSERT_EQUAL (res, 0);

    fsm_trans_t tt2[] = {
        {0, is_true, -1, NULL},
        {-1, NULL, -1, NULL}
    };
    
    res = fsm_init(&f, tt2, 2, 1);
    TEST_ASSERT_EQUAL (res, 0);
}

/**
 * @brief Devuelve puntero no NULL al crear la maquina de estados aun que las funciones de guarda y actualización sean nulas. 
 * Tambien se comprueba que la tabla de transicion sea correcta (todos los estados validos). 
 * Siempre que se verifique que el puntero creado no sea NULL, se comprueba la validez de la tabla de transicion
 * 
 * Requisito (s): 2, 3
 */
void test_fsm_new_nonNullWhenNullTransitionCondition(void)
{
    fsm_trans_t tt[] = {
        {0, NULL, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_t *f = (fsm_t*)1;

    fsm_malloc_Stub(test_malloc_wrapper);
    f = fsm_new(tt, 2, 1);

    TEST_ASSERT_NOT_NULL(f);

    fsm_destroy(f);
}

/**
 * @brief Inicializar devuelve true aun que las funciones de guarda y actualización sean nulas.
 * Tambien se comprueba que la tabla de transicion sea correcta (todos los estados validos)
 * Siempre que se verifique el resultado de la inicialización es true, se comprueba la validez de la tabla de transicion.
 * 
 * Requisito (s): 2, 3
 */
void test_fsm_init_trueWhenNullTransitionCondition(void)
{
    fsm_trans_t tt[] = {
        {0, NULL, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_t f;
    int res = fsm_init(&f, tt, 2, 1);

    TEST_ASSERT_EQUAL (res, 1);
}

/**
 * @brief Estado  inicial estado inicial corresponde al estado de entrada de la primera transición de la lista al crear la maquiina de estados y es valido. 
 * 
 * Requisito(s): 10, 11 
 * 
 */
void test_fsm_new_validInitialState(void)
{
    fsm_trans_t tt[] = {
        {0x12345678, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_malloc_Stub(test_malloc_wrapper);
    fsm_t* f = fsm_new(tt, 2, 0x12345679);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL (0x12345678, f->current_state);

    fsm_destroy(f);
}

/**
 * @brief Estado  inicial estado inicial corresponde al estado de entrada de la primera transición de la lista al inicializar la maquiina de estados y es valido. 
 * 
 * Requisito(s): 10, 11 
 * 
 */

void test_fsm_init_validInitialState(void)
{
    fsm_trans_t tt[] = {
        {0x12345678, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_t f;
    int res = fsm_init(&f, tt, 2, 0x12345679);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (0x12345678, f.current_state);
}


/**
 * @brief La maquina cambia de estado si la función de transición es NULL
 * 
 * Requisito(s): 13
 * 
 */

void test_fsm_fire_validTransitionNoCondition(void)
{
    fsm_trans_t tt[] = {
        {0, NULL, 1, NULL},
        {1, NULL, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_t f;
    int res;
    res = fsm_init(&f, tt, 3, 2);
    TEST_ASSERT_EQUAL (res, 1);

    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (1, f.current_state);
    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (0, f.current_state);
}
/**
 * @brief La maquina de estado al transicionar de estado devuelve 1 incluso si la funcion de actualizacion es NULL
 * 
 * Requisito(s): 3, 14, 15
 * 
 */
void test_fsm_fire_validTransitionNoOutput(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);

    fsm_t f;
    int res;
    res = fsm_init(&f, tt, 3, 2);
    TEST_ASSERT_EQUAL (res, 1);

    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (1, f.current_state);
}

/**
 * @brief La maquina de estado al transicionar de estado devuelve 1
 * 
 * Requisito(s): 14, 15
 * 
 */
void test_fsm_fire_validTransitionWithOutput(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, do_nothing},
        {1, is_true, 0, do_nothing},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();

    fsm_t f;
    int res;
    res = fsm_init(&f, tt, 3, 2);
    TEST_ASSERT_EQUAL (res, 1);

    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (1, f.current_state);
}

/**
 * @brief La maquina de estado no transiciona si la funcion devuelve 0
 * 
 * Requisito(s): 14, 17
 * 
 */
void test_fsm_fire_noTransition(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(0);

    fsm_t f;
    int res;
    res = fsm_init(&f, tt, 3, 2);
    TEST_ASSERT_EQUAL (res, 1);

    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 0);
    TEST_ASSERT_EQUAL (0, f.current_state);
}
/**
 * @brief La maquina de estados devuelve -1 (fin) se encuentra en un estado que no es el origen de ninguna transicion 
 * 
 * Requisito(s): 16
 * 
 */
void test_fsm_fire_endState(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);

    fsm_t f;
    int res;
    res = fsm_init(&f, tt, 2, 2);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (0, f.current_state);

    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (1, f.current_state);

    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, -1);
    TEST_ASSERT_EQUAL (1, f.current_state);
}

/**
 * @brief La reserva de memoria falla 
 * 
 * Requisto(s): 6
 * 
 */
void test_fsm_memory_full(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {1, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_malloc_IgnoreAndReturn(NULL);
    fsm_t* fsm = fsm_new(tt, 3, 2);

    TEST_ASSERT_EQUAL(fsm, NULL);
}

/**
 * @brief Comprueba que solo se llame a la funciones de guarda asociadas al estado actual
 * 
 * Requisitos(s): 12
 * 
 */
void test_fsm_fire_onlyCheckCurrentGuard(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {1, is_true2, 2, NULL},
        {-1, NULL, -1, NULL}
    };

    fsm_t f;
    int res;
    res = fsm_init(&f, tt, 3, 3);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (0, f.current_state);

    is_true_ExpectAnyArgsAndReturn(1);
    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (1, f.current_state);

    is_true2_ExpectAnyArgsAndReturn(1);
    res = fsm_fire(&f);
    TEST_ASSERT_EQUAL (res, 1);
    TEST_ASSERT_EQUAL (2, f.current_state);
}

/**
 * @brief Comprobar que no hay interferencia entre maquinas de estado creadas con la misma tabla de transiciones
 * 
 * Requisito(s): 4
 */
void test_fsm_concurrent(void) {
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {1, is_true, 2, NULL},
        {2, is_true, 3, NULL},
        {3, is_true, 0, NULL},
        {-1, NULL, -1, NULL}
    };

    int res;
    fsm_t fs[2];
    res = fsm_init(fs+0, tt, 5, 4);
    TEST_ASSERT_EQUAL (res, 1);
    res = fsm_init(fs+1, tt, 5, 4);
    TEST_ASSERT_EQUAL (res, 1);

    for(int i = 0; i < 16; ++i) {
        is_true_ExpectAnyArgsAndReturn(1);
        res = fsm_fire(fs+0);
        TEST_ASSERT_EQUAL (res, 1);
        TEST_ASSERT_EQUAL (0, fs[1].current_state);
    }
}