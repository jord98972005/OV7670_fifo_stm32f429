# Put your stlink folder here so make burn will work.
STLINK=../stlink

# Put your source files here (or *.c, etc)
SRCS=main.c \
	system_stm32f4xx.c \
	Sensor.c \
	fifo.c\
	sccb.c\
	delay.c\
	stm32f4xx_it.c\
	/home/jord98972005/stm32/ov76fifo/lcd/tm_stm32f4_fonts.c\
	/home/jord98972005/stm32/ov76fifo/lcd/tm_stm32f4_ili9341.c\
	/home/jord98972005/stm32/ov76fifo/lcd/tm_stm32f4_spi.c\
	/home/jord98972005/stm32/ov76fifo/tool/stm32f429i_discovery_lcd.c\
	/home/jord98972005/stm32/ov76fifo/tool/stm32f429i_discovery_sdram.c\
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c 

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=mco

# Put your STM32F4 library code directory here
STM_COMMON=../STM32F429I-Discovery_FW_V1.0.1

# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy


CFLAGS = -g -std=c99 -O2 -Wall -Tstm32f429zi_flash.ld -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.
CFLAGS += -DSTM32F429_439xx
CFLAGS += -Wl,--start-group -lm -Wl,--end-group -lc

# eliminate the unused code data
CFLAGS += -Wl,--gc-sections

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F429I-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc
CFLAGS += -I/home/jord98972005/stm32/ov76fifo/lcd



# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f429_439xx.s
OBJS = $(SRCS:.c=.o)


.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F429I
burn: proj
	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000