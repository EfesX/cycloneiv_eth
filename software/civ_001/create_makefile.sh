nios2-app-generate-makefile --bsp-dir ../civ_001_bsp/ \
--app-dir . \
--elf-name civ_001.elf \
\
--inc-dir FreeRTOS/FreeRTOS-Kernel/include/ \
--inc-dir FreeRTOS/FreeRTOS-Kernel/portable/GCC/NiosII/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-TCP/include/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-TCP/portable/NetworkInterface/include/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-TCP/portable/Compiler/GCC/ \
--inc-dir FreeRTOS/FreeRTOS-Plus-CLI/ \
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


