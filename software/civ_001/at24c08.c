#include "at24c08.h"

ALT_AVALON_I2C_DEV_t *eeprom_dev;

uint8_t eeprom_init(void){
    eeprom_dev = alt_avalon_i2c_open(I2C_EEPROM_NAME);
    if (eeprom_dev == NULL){
      printf("Error: Cannot find %s\n", I2C_EEPROM_NAME);
      return 1;
  	}
    alt_avalon_i2c_master_target_set(eeprom_dev, EEPROM_I2C_ADDR_DEV);
    return 0;
}

ALT_AVALON_I2C_STATUS_CODE eeprom_write(eeprom_buffer_tx_t *buf, uint8_t len){
    uint8_t dev_addr = EEPROM_I2C_ADDR_DEV;
    uint8_t local_len = len;
    ALT_AVALON_I2C_STATUS_CODE status;

    if (buf->addr & 0x0300)  dev_addr |= ((uint8_t)((buf->addr >> 8) & 0x03));
    if (local_len > 16)     local_len = 16;

    alt_avalon_i2c_master_target_set(eeprom_dev, dev_addr);
    status = alt_avalon_i2c_master_tx(eeprom_dev, &((void *)buf)[1], local_len + 1, ALT_AVALON_I2C_NO_INTERRUPTS);
    return status;
}
ALT_AVALON_I2C_STATUS_CODE eeprom_write_8(uint16_t addr, uint8_t data){
    ALT_AVALON_I2C_STATUS_CODE status;
    uint8_t dev_addr = (uint8_t)((uint8_t) EEPROM_I2C_ADDR_DEV | ((addr >> 8) & 0x03));
    uint8_t local_data[2] = {(uint8_t)addr, data};
    alt_avalon_i2c_master_target_set(eeprom_dev, dev_addr);
    status = alt_avalon_i2c_master_tx(eeprom_dev, local_data, 2, ALT_AVALON_I2C_NO_INTERRUPTS);
    return status;
}
ALT_AVALON_I2C_STATUS_CODE eeprom_write_16(uint16_t addr, uint16_t data){
    ALT_AVALON_I2C_STATUS_CODE status;
    uint8_t dev_addr = (uint8_t)((uint8_t) EEPROM_I2C_ADDR_DEV | ((addr >> 8) & 0x03));
    uint8_t local_data[3] = {(uint8_t)addr, (uint8_t)(data >> 8), (uint8_t)data};
    alt_avalon_i2c_master_target_set(eeprom_dev, dev_addr);
    status = alt_avalon_i2c_master_tx(eeprom_dev, local_data, 3, ALT_AVALON_I2C_NO_INTERRUPTS);
    return status;
}
ALT_AVALON_I2C_STATUS_CODE eeprom_write_32(uint16_t addr, uint32_t data){
    ALT_AVALON_I2C_STATUS_CODE status;
    uint8_t dev_addr = (uint8_t)((uint8_t) EEPROM_I2C_ADDR_DEV | ((addr >> 8) & 0x03));
    uint8_t local_data[5] = {(uint8_t)addr, (uint8_t)(data >> 24), (uint8_t)(data >> 16), (uint8_t)(data >> 8), (uint8_t)data};
    
    alt_avalon_i2c_master_target_set(eeprom_dev, dev_addr);
    status = alt_avalon_i2c_master_tx(eeprom_dev, local_data, 5, ALT_AVALON_I2C_NO_INTERRUPTS);
    return status;
}
ALT_AVALON_I2C_STATUS_CODE eeprom_read(uint16_t addr, uint8_t *data, int8_t len){
    ALT_AVALON_I2C_STATUS_CODE status;
    uint8_t local_addr = (uint8_t) addr;
    uint8_t dev_addr = (uint8_t)((uint8_t) EEPROM_I2C_ADDR_DEV | ((addr >> 8) & 0x03));
    alt_avalon_i2c_master_target_set(eeprom_dev, dev_addr);
    status = alt_avalon_i2c_master_tx_rx(eeprom_dev, &local_addr, 1, data, len, ALT_AVALON_I2C_NO_INTERRUPTS);
    return status;
}
