#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdint.h>

typedef uint8_t Schd_TaskStk;

typedef struct Schd_TaskRegList {
	// uint32_t PSR;
	// uint32_t PC;
	// uint32_t LR;
	// uint32_t R12;
	// uint32_t R3;
	// uint32_t R2;
	// uint32_t R1;
	// uint32_t R0;
	uint32_t R11;
	uint32_t R10;
	uint32_t R9;
	uint32_t R8;
	uint32_t R7;
	uint32_t R6;
	uint32_t R5;
	uint32_t R4;
} Schd_TaskRegList;

typedef struct Schd_TaskTCB {
	Schd_TaskStk * Stk;
	Schd_TaskRegList * RegList;
} Schd_TaskTCB;

Schd_TaskTCB * Schd_GetTaskTCBCurrent();
Schd_TaskTCB * Schd_GetTaskTCBNext();
void Schd_SetTaskTCBCurrent(Schd_TaskTCB * task_tcb);
void Schd_SetTaskTCBNext(Schd_TaskTCB * task_tcb);

__attribute__( ( always_inline ) ) static inline void Schd_SaveRegs(void)
{
}

#endif
