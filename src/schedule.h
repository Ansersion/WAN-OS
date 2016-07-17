#include <stdint.h>

typedef struct TaskRegList {
	uint32_t PSR;
	uint32_t PC;
	uint32_t LR;
	uint32_t R12;
	uint32_t R3;
	uint32_t R2;
	uint32_t R1;
	uint32_t R0;
} TaskRegList;

typedef struct TaskTCB {
	TaskRegList * Regs;
	uint32_t R11;
	uint32_t R10;
	uint32_t R9;
	uint32_t R8;
	uint32_t R7;
	uint32_t R6;
	uint32_t R5;
	uint32_t R4;
} TaskTCB;

TaskTCB * Schd_GetTaskTCBNow();
TaskTCB * Schd_GetTaskTCBNext();
void Schd_SetTaskTCBNow(TaskTCB * task_tcb);
void Schd_SetTaskTCBNext(TaskTCB * task_tcb);
