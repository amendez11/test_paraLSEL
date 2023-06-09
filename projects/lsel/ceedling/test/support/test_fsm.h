#ifndef _TEST_FSM_H
#define _TEST_FSM_H

#include "fsm.h"

int is_true(fsm_t* f);
int is_true2(fsm_t* f);
void do_nothing(fsm_t* f);
void* fsm_malloc(size_t s);

#endif