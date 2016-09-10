#ifndef SYS_CALL_H
#define SYS_CALL_H

#include <stdint.h>

typedef struct SvcMallocType{
	uint32_t size;
	void * ret;
}SvcMallocType;

typedef struct SvcFreeType {
	void * ptr;
}SvcFreeType;

int SysCall(int SysCallNum, void * arg);

#endif
