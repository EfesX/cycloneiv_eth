#include "lm75.h"
#include "altera_avalon_pio_regs.h"


TaskHandle_t xTaskTempHandle;
ALT_AVALON_I2C_STATUS_CODE status;
ALT_AVALON_I2C_DEV_t *i2c_temp;
uint8_t temperature;
uint16_t poll_period = TEMP_POLL_PERIOD_DEFAULT;
alt_u8 txbuffer[8]  = {0};
alt_u8 rxbuffer[32] = {0};

void set_poll_period(uint16_t period){
    poll_period = period;
}
uint16_t get_temp(void){
    return temperature;
}
int8_t temp_getI2CStatus(void){
    /*
    #define ALT_AVALON_I2C_TRUE         (1)
    #define ALT_AVALON_I2C_FALSE        (0)
    #define ALT_AVALON_I2C_SUCCESS      (0)
    #define ALT_AVALON_I2C_ERROR        (-1)
    #define ALT_AVALON_I2C_TIMEOUT      (-2)
    #define ALT_AVALON_I2C_BAD_ARG      (-3)
    #define ALT_AVALON_I2C_RANGE        (-4)
    #define ALT_AVALON_I2C_NACK_ERR     (-5)
    #define ALT_AVALON_I2C_ARB_LOST_ERR (-6)
    #define ALT_AVALON_I2C_BUSY         (-7)
    */
    return ((int8_t) status);
}
	  
void prvTempTask(void *p){
  	i2c_temp = alt_avalon_i2c_open(I2C_TEMP_NAME);
    if (NULL==i2c_temp){
      printf("Error: Cannot find %s\n", I2C_TEMP_NAME);
  	}
    alt_avalon_i2c_master_target_set(i2c_temp,LM75_ADDR);

    while(1){
        txbuffer[0] = 0x00;
        //taskENTER_CRITICAL();
        status = alt_avalon_i2c_master_tx_rx(i2c_temp, txbuffer, 1, rxbuffer, 2, ALT_AVALON_I2C_NO_INTERRUPTS);
        //taskEXIT_CRITICAL();
        temperature = rxbuffer[0];
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_D7SEG_BASE, temperature);

        vTaskDelay(pdMS_TO_TICKS(poll_period));
    }
}

void vStartTempChecking(uint16_t usStackSize, UBaseType_t uxPriority){
    xTaskCreate(prvTempTask, "temp", usStackSize, NULL, uxPriority, &xTaskTempHandle);
}

