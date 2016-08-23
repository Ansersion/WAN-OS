#include <mutex.h>
#include <irq.h>
#include <schedule.h>

int MutexInit(struct Mutex * Mtx)
{
	Mtx->X = 1;
	return 0;
}

int MutexLock(struct Mutex * Mtx)
{
	if(!Mtx) {
		return -1;
	}
	while(MutexTryLock(Mtx) != 0) {
		// Push PidQueue
		// TODO: Add PidQueue
		// schedule
		Schd_TaskCtxSw();
	}
	return 0;
}

int MutexTryLock(struct Mutex * Mtx)
{
	int ret;
	if(!Mtx) {
		ret = -1;
		return ret;
	}
	IRQ_LOCK();
	if(Mtx->X > 0) {
		Mtx->X--;
		ret = 0;
	} else {
		ret = -2;
	}
	IRQ_UNLOCK();

	return ret;
}

int MutexUnlock(struct Mutex * Mtx)
{
	int ret;
	if(!Mtx) {
		ret = -1;
		return ret;
	}
	IRQ_LOCK();
	if(Mtx->X <= 0) {
		Mtx->X++;
		ret = 0;
	} else {
		ret = -2;
	}
	IRQ_UNLOCK();

	return ret;
}

