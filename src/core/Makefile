ARM_GCC_MAIN_DIR=/opt/gcc-arm-none-eabi-5_3-2016q1
PREFIX=$(ARM_GCC_MAIN_DIR)/bin/arm-none-eabi
# PREFIX=arm-linux-gnueabi
# PREFIX=arm-linux-gnueabi

TARGET=core.a

CORE_DIR=./
ARCH_DIR=../arch
KERNEL_DIR=../kernel
MM_DIR=../mm

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
INCLUDE += -I$(MM_DIR)

MACRO += -DSTM32F10X_HD

CFLAGS 	=

CFLAGS 	+=-g -T $(ARCH_DIR)/gnu/sct.ld -Wall -c -mcpu=cortex-m3 -mthumb -nostartfiles $(INCLUDE) $(MACRO)

C_SRC 	=
A_SRC 	=
SRC 	=

C_OBJ 	=
A_OBJ 	=
OBJ 	=

C_SRC 	+= ${wildcard *.c}
C_SRC 	+= ${wildcard ./gnu/*.c}
A_SRC 	+= ${wildcard *.s}
A_SRC 	+= ${wildcard ./gnu/*.s}
SRC 	+= $(C_SRC)
SRC 	+= $(A_SRC)

C_OBJ 	+= ${patsubst %.c, %.o, $(C_SRC)}
A_OBJ 	+= ${patsubst %.s, %.o, $(A_SRC)}
OBJ 	+= $(C_OBJ)
OBJ 	+= $(A_OBJ)

ALL: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)
	cscope -Rbq

$(A_OBJ):%.o:%.s
	$(AS) -mcpu=cortex-m3 -mthumb $< -o $@

$(C_OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) *.out *.list
