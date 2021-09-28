#ifndef __AT24C08_H__
#define __AT24C08_H__

#include "system.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "altera_avalon_i2c.h"
#include "altera_avalon_i2c_regs.h"


#define EEPROM_I2C_ADDR_DEV 0x50

struct eeprom_buffer_tx{
    uint16_t addr;
    uint8_t data[16];
} __attribute__( ( packed ) );
typedef struct eeprom_buffer_tx eeprom_buffer_tx_t;


uint8_t eeprom_init(void);
ALT_AVALON_I2C_STATUS_CODE eeprom_write(eeprom_buffer_tx_t *buf, uint8_t len);
ALT_AVALON_I2C_STATUS_CODE eeprom_write_8(uint16_t addr, uint8_t data);
ALT_AVALON_I2C_STATUS_CODE eeprom_write_16(uint16_t addr, uint16_t data);
ALT_AVALON_I2C_STATUS_CODE eeprom_write_32(uint16_t addr, uint32_t data);
ALT_AVALON_I2C_STATUS_CODE eeprom_read(uint16_t addr, uint8_t *data, int8_t len);



#endif