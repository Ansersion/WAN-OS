#ifndef MUTEX_H
#define MUTEX_H

struct PidQueueNode {
	int * Pid;
	struct PidQueueNode * Next;
};

struct PidQueue {
	int Size;
	struct PidQueueNode N;
};

struct Mutex {
	int X;
	struct PidQueue PQ;
};

int MutexTryLock(struct Mutex * Mtx);
int MutexLock(struct Mutex * Mtx);
int MutexUnlock(struct Mutex * Mtx);

#endif

