rm -r drivers
rm -r HAL
rm -r obj
rm -r alt_sys_init.c
rm -r libhal_bsp.a
rm -r linker.h
rm -r linker.x
rm -r Makefile
rm -r mem_init.mk
rm -r memory.gdb
rm -r public.mk
rm -r setting.bsp
rm -r summary.html
rm -r system.h

nios2-bsp hal . ../../qsys/qsys.sopcinfo \
#--default_stdio JTAG_UART \
--default_sys_timer SYS_TIMER \
--default_memory_regions RAM

