/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'NIOSII' in SOPC Builder design 'qsys'
 * SOPC Builder design path: ../../qsys/qsys.sopcinfo
 *
 * Generated: Mon Sep 27 22:32:57 YEKT 2021
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x01000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x19
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00800020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x19
#define ALT_CPU_NAME "NIOSII"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00800000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x01000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x19
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00800020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x19
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00800000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_I2C
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SPI
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2


/*
 * I2C_EEPROM configuration
 *
 */

#define ALT_MODULE_CLASS_I2C_EEPROM altera_avalon_i2c
#define I2C_EEPROM_BASE 0x1001000
#define I2C_EEPROM_FIFO_DEPTH 8
#define I2C_EEPROM_FREQ 50000000
#define I2C_EEPROM_IRQ -1
#define I2C_EEPROM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define I2C_EEPROM_NAME "/dev/I2C_EEPROM"
#define I2C_EEPROM_SPAN 64
#define I2C_EEPROM_TYPE "altera_avalon_i2c"
#define I2C_EEPROM_USE_AV_ST 0


/*
 * I2C_TEMP configuration
 *
 */

#define ALT_MODULE_CLASS_I2C_TEMP altera_avalon_i2c
#define I2C_TEMP_BASE 0x1001040
#define I2C_TEMP_FIFO_DEPTH 8
#define I2C_TEMP_FREQ 50000000
#define I2C_TEMP_IRQ -1
#define I2C_TEMP_IRQ_INTERRUPT_CONTROLLER_ID -1
#define I2C_TEMP_NAME "/dev/I2C_TEMP"
#define I2C_TEMP_SPAN 64
#define I2C_TEMP_TYPE "altera_avalon_i2c"
#define I2C_TEMP_USE_AV_ST 0


/*
 * JTAG_UART configuration
 *
 */

#define ALT_MODULE_CLASS_JTAG_UART altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x1001118
#define JTAG_UART_IRQ 3
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/JTAG_UART"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * PIO_BTN configuration
 *
 */

#define ALT_MODULE_CLASS_PIO_BTN altera_avalon_pio
#define PIO_BTN_BASE 0x10010f0
#define PIO_BTN_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_BTN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_BTN_CAPTURE 1
#define PIO_BTN_DATA_WIDTH 8
#define PIO_BTN_DO_TEST_BENCH_WIRING 0
#define PIO_BTN_DRIVEN_SIM_VALUE 0
#define PIO_BTN_EDGE_TYPE "FALLING"
#define PIO_BTN_FREQ 50000000
#define PIO_BTN_HAS_IN 1
#define PIO_BTN_HAS_OUT 0
#define PIO_BTN_HAS_TRI 0
#define PIO_BTN_IRQ -1
#define PIO_BTN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_BTN_IRQ_TYPE "EDGE"
#define PIO_BTN_NAME "/dev/PIO_BTN"
#define PIO_BTN_RESET_VALUE 0
#define PIO_BTN_SPAN 16
#define PIO_BTN_TYPE "altera_avalon_pio"


/*
 * PIO_D7SEG configuration
 *
 */

#define ALT_MODULE_CLASS_PIO_D7SEG altera_avalon_pio
#define PIO_D7SEG_BASE 0x10010e0
#define PIO_D7SEG_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_D7SEG_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_D7SEG_CAPTURE 0
#define PIO_D7SEG_DATA_WIDTH 16
#define PIO_D7SEG_DO_TEST_BENCH_WIRING 0
#define PIO_D7SEG_DRIVEN_SIM_VALUE 0
#define PIO_D7SEG_EDGE_TYPE "NONE"
#define PIO_D7SEG_FREQ 50000000
#define PIO_D7SEG_HAS_IN 0
#define PIO_D7SEG_HAS_OUT 1
#define PIO_D7SEG_HAS_TRI 0
#define PIO_D7SEG_IRQ -1
#define PIO_D7SEG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_D7SEG_IRQ_TYPE "NONE"
#define PIO_D7SEG_NAME "/dev/PIO_D7SEG"
#define PIO_D7SEG_RESET_VALUE 0
#define PIO_D7SEG_SPAN 16
#define PIO_D7SEG_TYPE "altera_avalon_pio"


/*
 * PIO_LED configuration
 *
 */

#define ALT_MODULE_CLASS_PIO_LED altera_avalon_pio
#define PIO_LED_BASE 0x1001100
#define PIO_LED_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LED_CAPTURE 0
#define PIO_LED_DATA_WIDTH 4
#define PIO_LED_DO_TEST_BENCH_WIRING 0
#define PIO_LED_DRIVEN_SIM_VALUE 0
#define PIO_LED_EDGE_TYPE "NONE"
#define PIO_LED_FREQ 50000000
#define PIO_LED_HAS_IN 0
#define PIO_LED_HAS_OUT 1
#define PIO_LED_HAS_TRI 0
#define PIO_LED_IRQ -1
#define PIO_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_LED_IRQ_TYPE "NONE"
#define PIO_LED_NAME "/dev/PIO_LED"
#define PIO_LED_RESET_VALUE 0
#define PIO_LED_SPAN 16
#define PIO_LED_TYPE "altera_avalon_pio"


/*
 * RAM configuration
 *
 */

#define ALT_MODULE_CLASS_RAM altera_avalon_new_sdram_controller
#define RAM_BASE 0x800000
#define RAM_CAS_LATENCY 2
#define RAM_CONTENTS_INFO
#define RAM_INIT_NOP_DELAY 0.0
#define RAM_INIT_REFRESH_COMMANDS 2
#define RAM_IRQ -1
#define RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RAM_IS_INITIALIZED 1
#define RAM_NAME "/dev/RAM"
#define RAM_POWERUP_DELAY 100.0
#define RAM_REFRESH_PERIOD 31.25
#define RAM_REGISTER_DATA_IN 1
#define RAM_SDRAM_ADDR_WIDTH 0x16
#define RAM_SDRAM_BANK_WIDTH 2
#define RAM_SDRAM_COL_WIDTH 8
#define RAM_SDRAM_DATA_WIDTH 16
#define RAM_SDRAM_NUM_BANKS 4
#define RAM_SDRAM_NUM_CHIPSELECTS 1
#define RAM_SDRAM_ROW_WIDTH 12
#define RAM_SHARED_DATA 0
#define RAM_SIM_MODEL_BASE 0
#define RAM_SPAN 8388608
#define RAM_STARVATION_INDICATOR 0
#define RAM_TRISTATE_BRIDGE_SLAVE ""
#define RAM_TYPE "altera_avalon_new_sdram_controller"
#define RAM_T_AC 5.4
#define RAM_T_MRD 3
#define RAM_T_RCD 20.0
#define RAM_T_RFC 70.0
#define RAM_T_RP 20.0
#define RAM_T_WR 14.0


/*
 * SPI_MASTER configuration
 *
 */

#define ALT_MODULE_CLASS_SPI_MASTER altera_avalon_spi
#define SPI_MASTER_BASE 0x1001080
#define SPI_MASTER_CLOCKMULT 1
#define SPI_MASTER_CLOCKPHASE 0
#define SPI_MASTER_CLOCKPOLARITY 0
#define SPI_MASTER_CLOCKUNITS "Hz"
#define SPI_MASTER_DATABITS 8
#define SPI_MASTER_DATAWIDTH 16
#define SPI_MASTER_DELAYMULT "1.0E-9"
#define SPI_MASTER_DELAYUNITS "ns"
#define SPI_MASTER_EXTRADELAY 0
#define SPI_MASTER_INSERT_SYNC 0
#define SPI_MASTER_IRQ -1
#define SPI_MASTER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SPI_MASTER_ISMASTER 1
#define SPI_MASTER_LSBFIRST 0
#define SPI_MASTER_NAME "/dev/SPI_MASTER"
#define SPI_MASTER_NUMSLAVES 1
#define SPI_MASTER_PREFIX "spi_"
#define SPI_MASTER_SPAN 32
#define SPI_MASTER_SYNC_REG_DEPTH 2
#define SPI_MASTER_TARGETCLOCK 20000000u
#define SPI_MASTER_TARGETSSDELAY "0.0"
#define SPI_MASTER_TYPE "altera_avalon_spi"


/*
 * SYSID configuration
 *
 */

#define ALT_MODULE_CLASS_SYSID altera_avalon_sysid_qsys
#define SYSID_BASE 0x1001110
#define SYSID_ID 233492483
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/SYSID"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1632681293
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * SYS_TIMER configuration
 *
 */

#define ALT_MODULE_CLASS_SYS_TIMER altera_avalon_timer
#define SYS_TIMER_ALWAYS_RUN 0
#define SYS_TIMER_BASE 0x10010c0
#define SYS_TIMER_COUNTER_SIZE 32
#define SYS_TIMER_FIXED_PERIOD 0
#define SYS_TIMER_FREQ 50000000
#define SYS_TIMER_IRQ 2
#define SYS_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_TIMER_LOAD_VALUE 499999
#define SYS_TIMER_MULT 0.001
#define SYS_TIMER_NAME "/dev/SYS_TIMER"
#define SYS_TIMER_PERIOD 10
#define SYS_TIMER_PERIOD_UNITS "ms"
#define SYS_TIMER_RESET_OUTPUT 0
#define SYS_TIMER_SNAPSHOT 1
#define SYS_TIMER_SPAN 32
#define SYS_TIMER_TICKS_PER_SEC 100
#define SYS_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_TIMER_TYPE "altera_avalon_timer"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/JTAG_UART"
#define ALT_STDERR_BASE 0x1001118
#define ALT_STDERR_DEV JTAG_UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/JTAG_UART"
#define ALT_STDIN_BASE 0x1001118
#define ALT_STDIN_DEV JTAG_UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/JTAG_UART"
#define ALT_STDOUT_BASE 0x1001118
#define ALT_STDOUT_DEV JTAG_UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "qsys"


/*
 * TS_TIMER configuration
 *
 */

#define ALT_MODULE_CLASS_TS_TIMER altera_avalon_timer
#define TS_TIMER_ALWAYS_RUN 0
#define TS_TIMER_BASE 0x10010a0
#define TS_TIMER_COUNTER_SIZE 32
#define TS_TIMER_FIXED_PERIOD 0
#define TS_TIMER_FREQ 50000000
#define TS_TIMER_IRQ -1
#define TS_TIMER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TS_TIMER_LOAD_VALUE 4999
#define TS_TIMER_MULT 1.0E-6
#define TS_TIMER_NAME "/dev/TS_TIMER"
#define TS_TIMER_PERIOD 100
#define TS_TIMER_PERIOD_UNITS "us"
#define TS_TIMER_RESET_OUTPUT 0
#define TS_TIMER_SNAPSHOT 1
#define TS_TIMER_SPAN 32
#define TS_TIMER_TICKS_PER_SEC 10000
#define TS_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TS_TIMER_TYPE "altera_avalon_timer"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_TIMER
#define ALT_TIMESTAMP_CLK none

#endif /* __SYSTEM_H_ */
