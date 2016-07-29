#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <stdint.h>

#define MIN_STK_SIZE 	 	128
#define MAX_TASK_NUM 		16
// #define TASK_STK_SIZE_DEF 	64

/* consistent with register size */
#define TASK_STK 	uint32_t

typedef void * (*TaskType)(void *);

typedef struct TaskRegList {
} TaskRegList;

typedef struct TaskTCB {
	TASK_STK * 	StkTopPtr;
	uint32_t  	StkSize;
	/* Stack contents list as following(from top to bottom) */
	/*
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t psr;
	*/
	uint32_t 	Pid;
	uint8_t 	TaskState;
} TaskTCB;

int Schd_Init();
int Schd_CreateTask(TaskType Task, void * Arg, TaskTCB * Tcb);
void Schd_TaskCtxSw();
TaskTCB * Schd_Schdule();

TaskTCB * Schd_GetTaskTCBNow();
TaskTCB * Schd_GetTaskTCBNext();
void Schd_SetTaskTCBNow(TaskTCB * task_tcb);
void Schd_SetTaskTCBNext(TaskTCB * task_tcb);

#endif
