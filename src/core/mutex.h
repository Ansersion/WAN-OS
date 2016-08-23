#ifndef MUTEX_H
#define MUTEX_H

/*
struct PidQueueNode {
	int * Pid;
	struct PidQueueNode * Next;
};

struct PidQueue {
	int Size;
	struct PidQueueNode N;
};
*/

struct Mutex {
	volatile int X;
	// struct PidQueue PQ;
};

int MutexInit(struct Mutex * Mtx);
int MutexTryLock(struct Mutex * Mtx);
int MutexLock(struct Mutex * Mtx);
int MutexUnlock(struct Mutex * Mtx);

#endif

