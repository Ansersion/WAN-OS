#include <stdio.h>
#include <irq.h>
#include <schedule.h>
#include <core_header.h>

static TaskTCB * TaskList[MAX_TASK_NUM];

static TaskTCB * TaskNow;
static TaskTCB * TaskNext;

int Schd_Init()
{
	int i;
	for(i = 0; i < MAX_TASK_NUM; i++) {
		TaskList[i] = NULL;
	}
	return 0;
}

int Schd_CreateTask(TaskType Task, void * Arg, TaskTCB * Tcb)
{
	TASK_STK * stk_top;
	int i;
	if(NULL == Tcb) {
		return -1;
	}
	if(Tcb->StkSize < MIN_STK_SIZE) {
		return -2;
	}
	stk_top = Tcb->StkTopPtr + Tcb->StkSize / sizeof(TASK_STK);
	*(--stk_top) = (TASK_STK)0x01000000L;       // PSR
	*(--stk_top) = (TASK_STK)Task;              // Task Entry
	*(--stk_top)  = (TASK_STK)0xFFFFFFFEL;      // R14 (LR) 
	*(--stk_top)  = (TASK_STK)0x12121212L;      // R12
	*(--stk_top)  = (TASK_STK)0x03030303L;      // R3
	*(--stk_top)  = (TASK_STK)0x02020202L;      // R2
	*(--stk_top)  = (TASK_STK)0x01010101L;      // R1
	*(--stk_top)  = (TASK_STK)Arg;              // R0
	*(--stk_top)  = (TASK_STK)0x11111111L;      // R11
	*(--stk_top)  = (TASK_STK)0x10101010L;      // R10
	*(--stk_top)  = (TASK_STK)0x09090909L;      // R9
	*(--stk_top)  = (TASK_STK)0x08080808L;      // R8
	*(--stk_top)  = (TASK_STK)0x07070707L;      // R7
	*(--stk_top)  = (TASK_STK)0x06060606L;      // R6
	*(--stk_top)  = (TASK_STK)0x05050505L;      // R5
	*(--stk_top)  = (TASK_STK)0x04040404L;      // R4

	Tcb->StkTopPtr = stk_top;
	for(i = 0; i < MAX_TASK_NUM; i++) {
		if(NULL == TaskList[i]) {
			TaskList[i] = Tcb;
			TaskList[i]->Pid = i;
			return 0;
		}
	}

	/* There are 'MAX_TASK_NUM' tasks running.
	So creating task failed.
	   */
	return -3;
}

void Schd_TaskCtxSw()
{
	IRQ_LOCK();
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	IRQ_UNLOCK();
}

TaskTCB * Schd_Schdule()
{
	uint32_t i;
	for(i = TaskNow->Pid + 1; i < MAX_TASK_NUM; i++) {
		if(TaskList[i]) {
			TaskNext = TaskList[i];
			return TaskNext;
		}
	}
	for(i = 0; i <= TaskNow->Pid; i++) {
		if(TaskList[i]) {
			TaskNext = TaskList[i];
			return TaskNext;
		}
	}
	/* Never come here */
	return NULL;
}

TaskTCB * Schd_GetTaskTCBNow()
{
	return TaskNow;
}

TaskTCB * Schd_GetTaskTCBNext()
{
	return TaskNext;
}

void Schd_SetTaskTCBNow(TaskTCB * task_tcb)
{
	TaskNow = task_tcb;
}

void Schd_SetTaskTCBNext(TaskTCB * task_tcb)
{
	TaskNext = task_tcb;
}
