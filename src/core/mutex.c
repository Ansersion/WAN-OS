#include <mutex.h>
#include <irq.h>

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
	if(0 == Mtx->X) {
		Mtx->X = 1;
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
	if(Mtx->X != 0) {
		Mtx->X = 0;
		ret = 0;
	} else {
		ret = -2;
	}
	IRQ_UNLOCK();

	return ret;
}

