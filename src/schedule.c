#include "schedule.h"

Schd_TaskTCB * TaskCurrent;
Schd_TaskTCB * TaskNext;

Schd_TaskTCB * Schd_GetTaskTCBCurrent()
{
	return TaskCurrent;
}

Schd_TaskTCB * Schd_GetTaskTCBNext()
{
	return TaskNext;
}

void Schd_SetTaskTCBCurrent(Schd_TaskTCB * task_tcb)
{
	TaskCurrent = task_tcb;
}

void Schd_SetTaskTCBNext(Schd_TaskTCB * task_tcb)
{
	TaskNext = task_tcb;
}
