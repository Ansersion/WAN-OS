#include "schedule.h"

static TaskTCB * TaskNow;
static TaskTCB * TaskNext;

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
