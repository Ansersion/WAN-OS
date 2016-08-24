#include <sys_call.h>

int SysCall(int SysCallNum, void * arg)
{
	__asm("svc 0x80");
	return 0;
}
