rm -r obj
rm -r civ_002.elf
rm -r civ_002.map
rm -r civ_002.objdump
rm -r Makefile

cd ../civ_002_bsp
source ../civ_002_bsp/nios2-bsp.sh

cd ../civ_002
nios2-app-generate-makefile --bsp-dir ../civ_002_bsp/ \
--app-dir . \
--elf-name civ_002.elf \
\
--inc-dir FreeRTOS/FreeRTOS-Kernel/include/ \
--inc-dir FreeRTOS/FreeRTOS-Kernel/portable/GCC/NiosII/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-TCP/include/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-TCP/portable/NetworkInterface/include/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-TCP/portable/Compiler/GCC/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-CLI/ \
--inc-dir ../civ_002_bsp/HAL/inc/priv/ \
\
--src-dir . \
--src-dir FreeRTOS/FreeRTOS-Kernel/ \
--src-dir FreeRTOS/FreeRTOS-Kernel/portable/ \
--src-dir FreeRTOS/FreeRTOS-Kernel/portable/GCC/NiosII/ \
--src-files FreeRTOS/FreeRTOS-Kernel/portable/MemMang/heap_4.c \
--src-dir FreeRTOS/FreeRTOS-Plus-CLI/ \
--src-dir FreeRTOS/FreeRTOS-Plus-TCP/ \
--src-dir FreeRTOS/FreeRTOS-Plus-TCP/portable/NetworkInterface/ENC28J60/ \
--src-dir FreeRTOS/FreeRTOS-Plus-TCP/ \
--src-files FreeRTOS/FreeRTOS-Plus-TCP/portable/BufferManagement/BufferAllocation_1.c

sed -i 's/#define ALT_ENHANCED_INTERRUPT_API_PRESENT/#define ALT_LEGACY_INTERRUPT_API_PRESENT/' ../civ_002_bsp/system.h
sed -i 's/        alt_ic_isr_register(dev->irq_controller_ID, dev->irq_ID, alt_avalon_i2c_irq, dev, 0x0);/  /' ../civ_002_bsp/drivers/src/altera_avalon_i2c.c
