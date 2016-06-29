ARM_GCC_MAIN_DIR=/opt/gcc-arm-none-eabi-5_3-2016q1
PREFIX=$(ARM_GCC_MAIN_DIR)/bin/arm-none-eabi
# PREFIX=arm-linux-gnueabi
# PREFIX=arm-linux-gnueabi

TARGET=wan-kernel.bin

AS=$(PREFIX)-as
CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

CFLAGS 	=
CFLAGS 	+=-g -T sct.ld -Wall -c -mcpu=cortex-m3 -mthumb -nostartfiles 

C_SRC 	=
A_SRC 	=
SRC 	=

C_OBJ 	=
A_OBJ 	=
OBJ 	=

C_SRC 	+= ${wildcard *.c}
A_SRC 	+= ${wildcard *.s}
SRC 	+= $(C_SRC)
SRC 	+= $(A_SRC)

C_OBJ 	+= ${patsubst %.c, %.o, $(C_SRC)}
A_OBJ 	+= ${patsubst %.s, %.o, $(A_SRC)}
OBJ 	+= $(C_OBJ)
OBJ 	+= $(A_OBJ)

ALL: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -T sct.ld -mcpu=cortex-m3 -mthumb -flto -fno-builtin -nostartfiles -o wan-kernel.out $(OBJ)
	$(OBJCOPY) -Obinary wan-kernel.out $(TARGET)
	$(OBJDUMP) -S wan-kernel.out > wan-kernel.list
	cscope -Rbq

$(A_OBJ):%.o:%.s
	$(AS) -mcpu=cortex-m3 -mthumb $< -o $@

$(C_OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) *.out *.list
