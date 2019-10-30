/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'sopc4'
 * SOPC Builder design path: ../../sopc4.sopcinfo
 *
 * Generated: Tue Oct 29 18:36:28 ART 2019
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
#define ALT_CPU_BREAK_ADDR 0x00080820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x14
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00040020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x14
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00040000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00080820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x14
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00040020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x14
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00040000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag"
#define ALT_STDERR_BASE 0x81200
#define ALT_STDERR_DEV jtag
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag"
#define ALT_STDIN_BASE 0x81200
#define ALT_STDIN_DEV jtag
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag"
#define ALT_STDOUT_BASE 0x81200
#define ALT_STDOUT_DEV jtag
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "sopc4"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * in0 configuration
 *
 */

#define ALT_MODULE_CLASS_in0 altera_avalon_pio
#define IN0_BASE 0x81020
#define IN0_BIT_CLEARING_EDGE_REGISTER 0
#define IN0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN0_CAPTURE 0
#define IN0_DATA_WIDTH 8
#define IN0_DO_TEST_BENCH_WIRING 0
#define IN0_DRIVEN_SIM_VALUE 0
#define IN0_EDGE_TYPE "NONE"
#define IN0_FREQ 50000000
#define IN0_HAS_IN 1
#define IN0_HAS_OUT 0
#define IN0_HAS_TRI 0
#define IN0_IRQ -1
#define IN0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN0_IRQ_TYPE "NONE"
#define IN0_NAME "/dev/in0"
#define IN0_RESET_VALUE 0
#define IN0_SPAN 16
#define IN0_TYPE "altera_avalon_pio"


/*
 * in1 configuration
 *
 */

#define ALT_MODULE_CLASS_in1 altera_avalon_pio
#define IN1_BASE 0x81030
#define IN1_BIT_CLEARING_EDGE_REGISTER 0
#define IN1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN1_CAPTURE 0
#define IN1_DATA_WIDTH 8
#define IN1_DO_TEST_BENCH_WIRING 0
#define IN1_DRIVEN_SIM_VALUE 0
#define IN1_EDGE_TYPE "NONE"
#define IN1_FREQ 50000000
#define IN1_HAS_IN 1
#define IN1_HAS_OUT 0
#define IN1_HAS_TRI 0
#define IN1_IRQ -1
#define IN1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN1_IRQ_TYPE "NONE"
#define IN1_NAME "/dev/in1"
#define IN1_RESET_VALUE 0
#define IN1_SPAN 16
#define IN1_TYPE "altera_avalon_pio"


/*
 * in2 configuration
 *
 */

#define ALT_MODULE_CLASS_in2 altera_avalon_pio
#define IN2_BASE 0x81040
#define IN2_BIT_CLEARING_EDGE_REGISTER 0
#define IN2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN2_CAPTURE 0
#define IN2_DATA_WIDTH 8
#define IN2_DO_TEST_BENCH_WIRING 0
#define IN2_DRIVEN_SIM_VALUE 0
#define IN2_EDGE_TYPE "NONE"
#define IN2_FREQ 50000000
#define IN2_HAS_IN 1
#define IN2_HAS_OUT 0
#define IN2_HAS_TRI 0
#define IN2_IRQ -1
#define IN2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN2_IRQ_TYPE "NONE"
#define IN2_NAME "/dev/in2"
#define IN2_RESET_VALUE 0
#define IN2_SPAN 16
#define IN2_TYPE "altera_avalon_pio"


/*
 * in3 configuration
 *
 */

#define ALT_MODULE_CLASS_in3 altera_avalon_pio
#define IN3_BASE 0x81050
#define IN3_BIT_CLEARING_EDGE_REGISTER 0
#define IN3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN3_CAPTURE 0
#define IN3_DATA_WIDTH 8
#define IN3_DO_TEST_BENCH_WIRING 0
#define IN3_DRIVEN_SIM_VALUE 0
#define IN3_EDGE_TYPE "NONE"
#define IN3_FREQ 50000000
#define IN3_HAS_IN 1
#define IN3_HAS_OUT 0
#define IN3_HAS_TRI 0
#define IN3_IRQ -1
#define IN3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN3_IRQ_TYPE "NONE"
#define IN3_NAME "/dev/in3"
#define IN3_RESET_VALUE 0
#define IN3_SPAN 16
#define IN3_TYPE "altera_avalon_pio"


/*
 * in4 configuration
 *
 */

#define ALT_MODULE_CLASS_in4 altera_avalon_pio
#define IN4_BASE 0x81060
#define IN4_BIT_CLEARING_EDGE_REGISTER 0
#define IN4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN4_CAPTURE 0
#define IN4_DATA_WIDTH 8
#define IN4_DO_TEST_BENCH_WIRING 0
#define IN4_DRIVEN_SIM_VALUE 0
#define IN4_EDGE_TYPE "NONE"
#define IN4_FREQ 50000000
#define IN4_HAS_IN 1
#define IN4_HAS_OUT 0
#define IN4_HAS_TRI 0
#define IN4_IRQ -1
#define IN4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN4_IRQ_TYPE "NONE"
#define IN4_NAME "/dev/in4"
#define IN4_RESET_VALUE 0
#define IN4_SPAN 16
#define IN4_TYPE "altera_avalon_pio"


/*
 * in5 configuration
 *
 */

#define ALT_MODULE_CLASS_in5 altera_avalon_pio
#define IN5_BASE 0x81070
#define IN5_BIT_CLEARING_EDGE_REGISTER 0
#define IN5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN5_CAPTURE 0
#define IN5_DATA_WIDTH 8
#define IN5_DO_TEST_BENCH_WIRING 0
#define IN5_DRIVEN_SIM_VALUE 0
#define IN5_EDGE_TYPE "NONE"
#define IN5_FREQ 50000000
#define IN5_HAS_IN 1
#define IN5_HAS_OUT 0
#define IN5_HAS_TRI 0
#define IN5_IRQ -1
#define IN5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN5_IRQ_TYPE "NONE"
#define IN5_NAME "/dev/in5"
#define IN5_RESET_VALUE 0
#define IN5_SPAN 16
#define IN5_TYPE "altera_avalon_pio"


/*
 * in6 configuration
 *
 */

#define ALT_MODULE_CLASS_in6 altera_avalon_pio
#define IN6_BASE 0x81080
#define IN6_BIT_CLEARING_EDGE_REGISTER 0
#define IN6_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN6_CAPTURE 0
#define IN6_DATA_WIDTH 8
#define IN6_DO_TEST_BENCH_WIRING 0
#define IN6_DRIVEN_SIM_VALUE 0
#define IN6_EDGE_TYPE "NONE"
#define IN6_FREQ 50000000
#define IN6_HAS_IN 1
#define IN6_HAS_OUT 0
#define IN6_HAS_TRI 0
#define IN6_IRQ -1
#define IN6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN6_IRQ_TYPE "NONE"
#define IN6_NAME "/dev/in6"
#define IN6_RESET_VALUE 0
#define IN6_SPAN 16
#define IN6_TYPE "altera_avalon_pio"


/*
 * in7 configuration
 *
 */

#define ALT_MODULE_CLASS_in7 altera_avalon_pio
#define IN7_BASE 0x81090
#define IN7_BIT_CLEARING_EDGE_REGISTER 0
#define IN7_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN7_CAPTURE 0
#define IN7_DATA_WIDTH 8
#define IN7_DO_TEST_BENCH_WIRING 0
#define IN7_DRIVEN_SIM_VALUE 0
#define IN7_EDGE_TYPE "NONE"
#define IN7_FREQ 50000000
#define IN7_HAS_IN 1
#define IN7_HAS_OUT 0
#define IN7_HAS_TRI 0
#define IN7_IRQ -1
#define IN7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN7_IRQ_TYPE "NONE"
#define IN7_NAME "/dev/in7"
#define IN7_RESET_VALUE 0
#define IN7_SPAN 16
#define IN7_TYPE "altera_avalon_pio"


/*
 * in_aux configuration
 *
 */

#define ALT_MODULE_CLASS_in_aux altera_avalon_pio
#define IN_AUX_BASE 0x81180
#define IN_AUX_BIT_CLEARING_EDGE_REGISTER 0
#define IN_AUX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IN_AUX_CAPTURE 0
#define IN_AUX_DATA_WIDTH 8
#define IN_AUX_DO_TEST_BENCH_WIRING 0
#define IN_AUX_DRIVEN_SIM_VALUE 0
#define IN_AUX_EDGE_TYPE "NONE"
#define IN_AUX_FREQ 50000000
#define IN_AUX_HAS_IN 1
#define IN_AUX_HAS_OUT 0
#define IN_AUX_HAS_TRI 0
#define IN_AUX_IRQ -1
#define IN_AUX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IN_AUX_IRQ_TYPE "NONE"
#define IN_AUX_NAME "/dev/in_aux"
#define IN_AUX_RESET_VALUE 0
#define IN_AUX_SPAN 16
#define IN_AUX_TYPE "altera_avalon_pio"


/*
 * jtag configuration
 *
 */

#define ALT_MODULE_CLASS_jtag altera_avalon_jtag_uart
#define JTAG_BASE 0x81200
#define JTAG_IRQ 0
#define JTAG_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_NAME "/dev/jtag"
#define JTAG_READ_DEPTH 64
#define JTAG_READ_THRESHOLD 8
#define JTAG_SPAN 8
#define JTAG_TYPE "altera_avalon_jtag_uart"
#define JTAG_WRITE_DEPTH 64
#define JTAG_WRITE_THRESHOLD 8


/*
 * memory configuration
 *
 */

#define ALT_MODULE_CLASS_memory altera_avalon_onchip_memory2
#define MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define MEMORY_BASE 0x40000
#define MEMORY_CONTENTS_INFO ""
#define MEMORY_DUAL_PORT 0
#define MEMORY_GUI_RAM_BLOCK_TYPE "AUTO"
#define MEMORY_INIT_CONTENTS_FILE "sopc4_memory"
#define MEMORY_INIT_MEM_CONTENT 1
#define MEMORY_INSTANCE_ID "NONE"
#define MEMORY_IRQ -1
#define MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MEMORY_NAME "/dev/memory"
#define MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define MEMORY_RAM_BLOCK_TYPE "AUTO"
#define MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define MEMORY_SINGLE_CLOCK_OP 0
#define MEMORY_SIZE_MULTIPLE 1
#define MEMORY_SIZE_VALUE 204800
#define MEMORY_SPAN 204800
#define MEMORY_TYPE "altera_avalon_onchip_memory2"
#define MEMORY_WRITABLE 1


/*
 * out0 configuration
 *
 */

#define ALT_MODULE_CLASS_out0 altera_avalon_pio
#define OUT0_BASE 0x81100
#define OUT0_BIT_CLEARING_EDGE_REGISTER 0
#define OUT0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT0_CAPTURE 0
#define OUT0_DATA_WIDTH 8
#define OUT0_DO_TEST_BENCH_WIRING 0
#define OUT0_DRIVEN_SIM_VALUE 0
#define OUT0_EDGE_TYPE "NONE"
#define OUT0_FREQ 50000000
#define OUT0_HAS_IN 0
#define OUT0_HAS_OUT 1
#define OUT0_HAS_TRI 0
#define OUT0_IRQ -1
#define OUT0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT0_IRQ_TYPE "NONE"
#define OUT0_NAME "/dev/out0"
#define OUT0_RESET_VALUE 0
#define OUT0_SPAN 16
#define OUT0_TYPE "altera_avalon_pio"


/*
 * out1 configuration
 *
 */

#define ALT_MODULE_CLASS_out1 altera_avalon_pio
#define OUT1_BASE 0x81110
#define OUT1_BIT_CLEARING_EDGE_REGISTER 0
#define OUT1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT1_CAPTURE 0
#define OUT1_DATA_WIDTH 8
#define OUT1_DO_TEST_BENCH_WIRING 0
#define OUT1_DRIVEN_SIM_VALUE 0
#define OUT1_EDGE_TYPE "NONE"
#define OUT1_FREQ 50000000
#define OUT1_HAS_IN 0
#define OUT1_HAS_OUT 1
#define OUT1_HAS_TRI 0
#define OUT1_IRQ -1
#define OUT1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT1_IRQ_TYPE "NONE"
#define OUT1_NAME "/dev/out1"
#define OUT1_RESET_VALUE 0
#define OUT1_SPAN 16
#define OUT1_TYPE "altera_avalon_pio"


/*
 * out2 configuration
 *
 */

#define ALT_MODULE_CLASS_out2 altera_avalon_pio
#define OUT2_BASE 0x81120
#define OUT2_BIT_CLEARING_EDGE_REGISTER 0
#define OUT2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT2_CAPTURE 0
#define OUT2_DATA_WIDTH 8
#define OUT2_DO_TEST_BENCH_WIRING 0
#define OUT2_DRIVEN_SIM_VALUE 0
#define OUT2_EDGE_TYPE "NONE"
#define OUT2_FREQ 50000000
#define OUT2_HAS_IN 0
#define OUT2_HAS_OUT 1
#define OUT2_HAS_TRI 0
#define OUT2_IRQ -1
#define OUT2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT2_IRQ_TYPE "NONE"
#define OUT2_NAME "/dev/out2"
#define OUT2_RESET_VALUE 0
#define OUT2_SPAN 16
#define OUT2_TYPE "altera_avalon_pio"


/*
 * out3 configuration
 *
 */

#define ALT_MODULE_CLASS_out3 altera_avalon_pio
#define OUT3_BASE 0x81130
#define OUT3_BIT_CLEARING_EDGE_REGISTER 0
#define OUT3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT3_CAPTURE 0
#define OUT3_DATA_WIDTH 8
#define OUT3_DO_TEST_BENCH_WIRING 0
#define OUT3_DRIVEN_SIM_VALUE 0
#define OUT3_EDGE_TYPE "NONE"
#define OUT3_FREQ 50000000
#define OUT3_HAS_IN 0
#define OUT3_HAS_OUT 1
#define OUT3_HAS_TRI 0
#define OUT3_IRQ -1
#define OUT3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT3_IRQ_TYPE "NONE"
#define OUT3_NAME "/dev/out3"
#define OUT3_RESET_VALUE 0
#define OUT3_SPAN 16
#define OUT3_TYPE "altera_avalon_pio"


/*
 * out4 configuration
 *
 */

#define ALT_MODULE_CLASS_out4 altera_avalon_pio
#define OUT4_BASE 0x81140
#define OUT4_BIT_CLEARING_EDGE_REGISTER 0
#define OUT4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT4_CAPTURE 0
#define OUT4_DATA_WIDTH 8
#define OUT4_DO_TEST_BENCH_WIRING 0
#define OUT4_DRIVEN_SIM_VALUE 0
#define OUT4_EDGE_TYPE "NONE"
#define OUT4_FREQ 50000000
#define OUT4_HAS_IN 0
#define OUT4_HAS_OUT 1
#define OUT4_HAS_TRI 0
#define OUT4_IRQ -1
#define OUT4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT4_IRQ_TYPE "NONE"
#define OUT4_NAME "/dev/out4"
#define OUT4_RESET_VALUE 0
#define OUT4_SPAN 16
#define OUT4_TYPE "altera_avalon_pio"


/*
 * out5 configuration
 *
 */

#define ALT_MODULE_CLASS_out5 altera_avalon_pio
#define OUT5_BASE 0x81150
#define OUT5_BIT_CLEARING_EDGE_REGISTER 0
#define OUT5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT5_CAPTURE 0
#define OUT5_DATA_WIDTH 8
#define OUT5_DO_TEST_BENCH_WIRING 0
#define OUT5_DRIVEN_SIM_VALUE 0
#define OUT5_EDGE_TYPE "NONE"
#define OUT5_FREQ 50000000
#define OUT5_HAS_IN 0
#define OUT5_HAS_OUT 1
#define OUT5_HAS_TRI 0
#define OUT5_IRQ -1
#define OUT5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT5_IRQ_TYPE "NONE"
#define OUT5_NAME "/dev/out5"
#define OUT5_RESET_VALUE 0
#define OUT5_SPAN 16
#define OUT5_TYPE "altera_avalon_pio"


/*
 * out6 configuration
 *
 */

#define ALT_MODULE_CLASS_out6 altera_avalon_pio
#define OUT6_BASE 0x81160
#define OUT6_BIT_CLEARING_EDGE_REGISTER 0
#define OUT6_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT6_CAPTURE 0
#define OUT6_DATA_WIDTH 8
#define OUT6_DO_TEST_BENCH_WIRING 0
#define OUT6_DRIVEN_SIM_VALUE 0
#define OUT6_EDGE_TYPE "NONE"
#define OUT6_FREQ 50000000
#define OUT6_HAS_IN 0
#define OUT6_HAS_OUT 1
#define OUT6_HAS_TRI 0
#define OUT6_IRQ -1
#define OUT6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT6_IRQ_TYPE "NONE"
#define OUT6_NAME "/dev/out6"
#define OUT6_RESET_VALUE 0
#define OUT6_SPAN 16
#define OUT6_TYPE "altera_avalon_pio"


/*
 * out7 configuration
 *
 */

#define ALT_MODULE_CLASS_out7 altera_avalon_pio
#define OUT7_BASE 0x81170
#define OUT7_BIT_CLEARING_EDGE_REGISTER 0
#define OUT7_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT7_CAPTURE 0
#define OUT7_DATA_WIDTH 8
#define OUT7_DO_TEST_BENCH_WIRING 0
#define OUT7_DRIVEN_SIM_VALUE 0
#define OUT7_EDGE_TYPE "NONE"
#define OUT7_FREQ 50000000
#define OUT7_HAS_IN 0
#define OUT7_HAS_OUT 1
#define OUT7_HAS_TRI 0
#define OUT7_IRQ -1
#define OUT7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT7_IRQ_TYPE "NONE"
#define OUT7_NAME "/dev/out7"
#define OUT7_RESET_VALUE 0
#define OUT7_SPAN 16
#define OUT7_TYPE "altera_avalon_pio"


/*
 * out_aux configuration
 *
 */

#define ALT_MODULE_CLASS_out_aux altera_avalon_pio
#define OUT_AUX_BASE 0x81190
#define OUT_AUX_BIT_CLEARING_EDGE_REGISTER 0
#define OUT_AUX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT_AUX_CAPTURE 0
#define OUT_AUX_DATA_WIDTH 8
#define OUT_AUX_DO_TEST_BENCH_WIRING 0
#define OUT_AUX_DRIVEN_SIM_VALUE 0
#define OUT_AUX_EDGE_TYPE "NONE"
#define OUT_AUX_FREQ 50000000
#define OUT_AUX_HAS_IN 0
#define OUT_AUX_HAS_OUT 1
#define OUT_AUX_HAS_TRI 0
#define OUT_AUX_IRQ -1
#define OUT_AUX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OUT_AUX_IRQ_TYPE "NONE"
#define OUT_AUX_NAME "/dev/out_aux"
#define OUT_AUX_RESET_VALUE 0
#define OUT_AUX_SPAN 16
#define OUT_AUX_TYPE "altera_avalon_pio"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x81208
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1572383346
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x81000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000
#define TIMER_IRQ 1
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999999
#define TIMER_MULT 1.0
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "s"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
