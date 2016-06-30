#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

#ifdef __KEIL__
#define IRQ_Reset 	Reset_Handler     
#define IRQ_Nmi 	NMI_Handler       
#define IRQ_HardFault 	HardFault_Handler 
#define IRQ_MemManage 	MemManage_Handler 
#define IRQ_BusFault 	BusFault_Handler  
#define IRQ_UsageFault 	UsageFault_Handler
// #define IRQ_NULL_7 	Reserved_Handler                 
// #define IRQ_NULL_8 	Reserved_Handler              
// #define IRQ_NULL_9 	Reserved_Handler                 
// #define IRQ_NULL_10 	Reserved_Handler                 
#define IRQ_SVC 	SVC_Handler       
#define IRQ_DebugMon	DebugMon_Handler  
// #define IRQ_NULL_13	Reserved_Handler                 
#define IRQ_PendSV	PendSV_Handler    
#define IRQ_SysTick	SysTick_Handler   
#endif

/*****Register of IRQ Vectors Offset***
 */
#define REG_IRQ_VTOR 	((uint32_t *)0xE000ED08)
#define REG_AIRCR 		((uint32_t *)0xE000ED0C)

#define REG_SETENA0 	((uint32_t *)0xE000E100)
#define REG_SETENA1 	((uint32_t *)0xE000E104)
#define REG_SETENA2 	((uint32_t *)0xE000E108)
#define REG_SETENA3 	((uint32_t *)0xE000E10C)
#define REG_SETENA4 	((uint32_t *)0xE000E110)
#define REG_SETENA5 	((uint32_t *)0xE000E114)
#define REG_SETENA6 	((uint32_t *)0xE000E118)
#define REG_SETENA7 	((uint32_t *)0xE000E11C)

#define REG_CLRENA0 	((uint32_t *)0xE000E180)
#define REG_CLRENA1 	((uint32_t *)0xE000E184)
#define REG_CLRENA2 	((uint32_t *)0xE000E188)
#define REG_CLRENA3 	((uint32_t *)0xE000E18C)
#define REG_CLRENA4 	((uint32_t *)0xE000E190)
#define REG_CLRENA5 	((uint32_t *)0xE000E194)
#define REG_CLRENA6 	((uint32_t *)0xE000E198)
#define REG_CLRENA7 	((uint32_t *)0xE000E19C)

#define REG_SETPEND0 	((uint32_t *)0xE000E200)
#define REG_SETPEND1 	((uint32_t *)0xE000E204)
#define REG_SETPEND2 	((uint32_t *)0xE000E208)
#define REG_SETPEND3 	((uint32_t *)0xE000E20C)
#define REG_SETPEND4 	((uint32_t *)0xE000E210)
#define REG_SETPEND5 	((uint32_t *)0xE000E214)
#define REG_SETPEND6 	((uint32_t *)0xE000E218)
#define REG_SETPEND7 	((uint32_t *)0xE000E21C)

#define REG_CLRPEND0 	((uint32_t *)0xE000E280)
#define REG_CLRPEND1 	((uint32_t *)0xE000E284)
#define REG_CLRPEND2 	((uint32_t *)0xE000E288)
#define REG_CLRPEND3 	((uint32_t *)0xE000E28C)
#define REG_CLRPEND4 	((uint32_t *)0xE000E290)
#define REG_CLRPEND5 	((uint32_t *)0xE000E294)
#define REG_CLRPEND6 	((uint32_t *)0xE000E298)
#define REG_CLRPEND7 	((uint32_t *)0xE000E29C)

#define WAN_OS_RAM 	((uint32_t)0x20004000)
#define WAN_VTOR_ADDRESS 	((uint32_t)0x00000200)
#define VTOR_RAM 	((uint32_t)0x20000000)
#define VTOR_R0M 	((uint32_t)0x00000000)
#define REG_ICSR 	((uint32_t *)0xE000ED04)
#define MSK_SYSTICK_CLRPEND 0x02000000
#define MSK_PENDSV_CLRPEND 	0x08000000

/* WARNING: Setup the interrupt of systick first, before
   using the function.
 */
volatile int32_t Init_SysTickIRQ(uint32_t Ticks, uint32_t Priority);
volatile int32_t Init_IRQGroup(uint32_t GroupLimit);
void IRQ_Init(void);
volatile int32_t IRQ_SetPriority(uint32_t IRQ_Number, uint8_t Priority);
volatile int32_t IRQ_Enalbe(uint32_t IRQ_Number);
volatile int32_t IRQ_Disable(uint32_t IRQ_Number);
volatile int32_t IRQ_SetPend(uint32_t IRQ_Number);
volatile int32_t IRQ_ClrPend(uint32_t IRQ_Number);

typedef void (* IRQ_HANDLER)(void);

void IRQ_Reset(void);
void IRQ_Nmi(void);
void IRQ_HardFault(void);
void IRQ_MemManage(void);
void IRQ_BusFault(void);
void IRQ_UsageFault(void);
void IRQ_NULL_7(void);
void IRQ_NULL_8(void);
void IRQ_NULL_9(void);
void IRQ_NULL_10(void);
void IRQ_SVC(void);
void IRQ_DebugMon(void);
void IRQ_NULL_13(void);
void IRQ_PendSV(void);
void IRQ_SysTick(void);

void IRQ_LOCK(void); // asm function(asm_tool.s)
void IRQ_UNLOCK(void); // asm function(asm_tool.s)

#endif
