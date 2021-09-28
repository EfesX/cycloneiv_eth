#ifndef __LM75_H__
#define __LM75_H__

#include "system.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "altera_avalon_i2c.h"
#include "altera_avalon_i2c_regs.h"



#define LM75_ADDR 0x48
#define TEMP_POLL_PERIOD_DEFAULT 1000


void set_poll_period(uint16_t period);
uint16_t get_temp(void);
int8_t temp_getI2CStatus(void);
void vStartTempChecking(uint16_t usStackSize, UBaseType_t uxPriority);


#endif