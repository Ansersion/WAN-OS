#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEM_FREE 	0
#define MEM_BUSY 	1

struct Mem_Block
{
	uint32_t Size; 
  uint32_t Addr;
  int State; 
	struct Mem_Block * Prev;
	struct Mem_Block * Next;
};

uint32_t Mem_GetKernelEndAddr(void);
uint32_t Mem_Init(void);
void * Mem_Malloc(uint32_t Size);
void Mem_Free(void * Ptr);

void * Malloc(uint32_t size);
void Free(void * Ptr);

#endif

