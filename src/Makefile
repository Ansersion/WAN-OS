ARM_GCC_MAIN_DIR=/opt/gcc-arm-none-eabi-5_3-2016q1
PREFIX=$(ARM_GCC_MAIN_DIR)/bin/arm-none-eabi
# PREFIX=arm-linux-gnueabi
# PREFIX=arm-linux-gnueabi

CORE_DIR=core
ARCH_DIR=arch
KERNEL_DIR=kernel

TARGET=wan-kernel.bin

LIB_CORE 	+= $(CORE_DIR)/core.a
LIB_ARCH 	+= $(ARCH_DIR)/arch.a
LIB_KERNEL 	+= $(KERNEL_DIR)/kernel.a

AS=$(PREFIX)-as
CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

INCLUDE=
MACRO=

INCLUDE += -I$(CORE_DIR)
INCLUDE += -I$(ARCH_DIR)
INCLUDE += -I$(KERNEL_DIR)

MACRO += -DSTM32F10X_HD

CFLAGS 	=
CFLAGS 	+=-g -T $(ARCH_DIR)/gnu/sct.ld -Wall -c -mcpu=cortex-m3 -mthumb -nostartfiles

CFLAGS += $(INCLUDE)
CFLAGS += $(MACRO)

C_SRC 	=
A_SRC 	=
SRC 	=

# C_OBJ 	=
# A_OBJ 	=
# OBJ 	=
 
C_SRC 	+= ${wildcard *.c}
A_SRC 	+= ${wildcard *.s}
SRC 	+= $(C_SRC)
SRC 	+= $(A_SRC)

# C_OBJ 	+= ${patsubst %.c, %.o, $(C_SRC)}
# A_OBJ 	+= ${patsubst %.s, %.o, $(A_SRC)}
# OBJ 	+= $(C_OBJ)
# OBJ 	+= $(A_OBJ)

ALL: $(TARGET)

$(TARGET): $(LIB_KERNEL) $(LIB_ARCH) $(LIB_CORE)
	ar xv $(LIB_CORE)
	ar xv $(LIB_ARCH)
	ar xv $(LIB_KERNEL)

	$(CC) -T $(ARCH_DIR)/gnu/sct.ld -mcpu=cortex-m3 -mthumb -flto -fno-builtin -nostartfiles -o wan-kernel.out *.o
	$(OBJCOPY) -Obinary wan-kernel.out $(TARGET)
	rm -f *.o
	rm -f $(LIB_CORE) $(LIB_ARCH) $(LIB_KERNEL)
	$(OBJDUMP) -S wan-kernel.out > wan-kernel.list
	$(OBJDUMP) -D wan-kernel.out > wan-kernel.dis
	cscope -Rbq

$(LIB_KERNEL):
	(cd $(KERNEL_DIR); make)

$(LIB_ARCH):
	(cd $(ARCH_DIR); make)

$(LIB_CORE):
	(cd $(CORE_DIR); make)

# $(A_OBJ):%.o:%.s
# 	$(AS) -mcpu=cortex-m3 -mthumb $< -o $@
# 
# $(C_OBJ):%.o:%.c
# 	$(CC) $(CFLAGS) $< -o $@

clean:
	(cd $(CORE_DIR); make clean)
	(cd $(ARCH_DIR); make clean)
	(cd $(KERNEL_DIR); make clean)
	rm -f *.o $(TARGET) *.out *.list
