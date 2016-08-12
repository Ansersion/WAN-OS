/* STD headers */
#include <stdio.h>

/* kernel headers */
#include <memory.h>

/* arch headers */
#include <hardware.h>


struct Mem_Block * FirstBlock;


uint32_t Mem_GetKernelEndAddr(void)
{
	/* Kernel size is in 'FLASH_BASE', the same as initial 'MSP'*/
	return *((uint32_t *)(FLASH_BASE));
}

uint32_t Mem_Init(void)
{
	uint32_t free_mem_start;
	uint32_t free_mem_size;
	int i;
	free_mem_start = Mem_GetKernelEndAddr();
	for(i = free_mem_start; i < MEMORY_BASE + MEMORY_SIZE; i+=sizeof(uint32_t)) {
		if(*(uint32_t *)(i) != 0) {
			break;
		}
	}
	free_mem_size = i - free_mem_start;
	if(free_mem_size < sizeof(struct Mem_Block)) {
		return 0;
	}
	
	/* Must: free_mem_size >= sizeof(struct Mem_Block) */
	FirstBlock = (struct Mem_Block *)free_mem_start;
	FirstBlock->Addr = (uint32_t)(FirstBlock + sizeof(struct Mem_Block));
	FirstBlock->Size = free_mem_size - sizeof(struct Mem_Block);
	FirstBlock->State = MEM_FREE;
	FirstBlock->Prev = NULL;
	FirstBlock->Next = NULL;
	
	return free_mem_size;
}

void * Mem_Malloc(uint32_t Size)
{
	struct Mem_Block * block;
  uint32_t tmp_size;
	struct Mem_Block * tmp_next;
	struct Mem_Block * child_block;
	block = FirstBlock;
	Size = (Size + sizeof(uint32_t) - 1) / sizeof(uint32_t) * sizeof(uint32_t);
	do {
		if(MEM_FREE != block->State) {
			continue;
		}
		if(block->Size < Size + sizeof(struct Mem_Block)) {
			continue;
		}
		tmp_size = block->Size;
		if(block->Size - Size < sizeof(struct Mem_Block)) {
			Size = block->Size;
			child_block = block->Next;
		} else {
			child_block = (struct Mem_Block *)(block->Addr + Size);
		}
		block->Size = Size;
		block->State = MEM_BUSY;
		tmp_next = block->Next;
		block->Next = child_block;
		
		if(tmp_next != child_block) {
			block->Next->Prev = block;
			block->Next->Next = tmp_next;
			block->Next->State = MEM_FREE;
			block->Next->Addr = (uint32_t)(block->Next + sizeof(struct Mem_Block));
			block->Next->Size = tmp_size - Size - sizeof(struct Mem_Block);
		}
		
		return (void *)(block->Addr);
		
	} while((block = block->Next) != NULL);
	
	return NULL;
}

void Mem_Free(void * Ptr)
{
	struct Mem_Block * block;
	struct Mem_Block * tmp;
//	uint32_t tmp_size;
//	struct Mem_Block * tmp_next;
	block = FirstBlock;
	
	do {
		if((uint32_t)Ptr != block->Addr) {
			continue;
		}
		if(MEM_FREE == block->State) {
			/* alread freed */
			return;
		}
		
		tmp = block->Prev;
		while(tmp != NULL && MEM_FREE == tmp->State) {
			tmp->Next = block->Next;
			tmp->Size += block->Size + sizeof(struct Mem_Block);
			block = tmp;
			tmp = block->Prev;
		}
		
		tmp = block->Next;
		while(tmp != NULL && MEM_FREE == tmp->State) {
			block->Next = tmp->Next;
			block->Size += tmp->Size + sizeof(struct Mem_Block);
			block = tmp;
			tmp = block->Next;
		}
		
	} while((block = block->Next) != NULL);
}
