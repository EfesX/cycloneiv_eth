/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */


#include "system.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "FreeRTOS_IP.h"
#include "stack_macros.h"

#include "altera_avalon_timer.h"
#include "altera_avalon_timer_regs.h"

#include "altera_avalon_i2c.h"
#include "altera_avalon_i2c_regs.h"

#include "lm75.h"
#include "at24c08.h"

#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"

//#include "altera_epcq_controller.h"



uint8_t my_ip[4] = {192, 168, 1, 70};
uint8_t mymask[4] = {255, 255, 255, 0};
uint8_t mygate[4] = {192, 168, 1, 1};
volatile uint8_t mymac[6] = {0x54, 0x55, 0x58, 0x11, 0x00, 0x24};

#define mainQUEUE_SEND_FREQUENCY_MS			( 250 / portTICK_RATE_MS )

void vApplicationStackOverflowHook(TaskHandle_t  pxCurrentTCB, char *pcTaskName ){
	printf("vApplicationStackOverflowHook\n");
}


alt_u8 rxbuffer[0x200];
uint32_t len;

//alt_epcq_controller_dev fd;

int main(void)
{
	eeprom_init();

	uint8_t t[128];
	
	
	//alt_avalon_spi_command(EPCS_BASE, 1, t, 2, &t[5], 5, 0);
	//altera_epcq_controller_init(&fd);


	uint16_t addr = 1792;
	uint8_t dev_addr = (uint8_t)((uint8_t) EEPROM_I2C_ADDR_DEV | ((addr >> 8) & 0x03));

	len = eeprom_read_32(0);

	rxbuffer[0] = eeprom_read_8(16);
	rxbuffer[1] = eeprom_read_8(17);
	rxbuffer[2] = eeprom_read_8(18);
	rxbuffer[3] = eeprom_read_8(19);

	vRegisterCLICommands();

	FreeRTOS_IPInit(my_ip, mymask, mygate, NULL, mymac);

	vTaskStartScheduler();

	return 0;
}


void vApplicationIPNetworkEventHook(eIPCallbackEvent_t ev){
	printf("vApplicationIPNetworkEventHook\n");
	vStartTelnetServer(configMINIMAL_STACK_SIZE * 2, 6);
	vStartHTTPServer(configMINIMAL_STACK_SIZE*3, 8);
	vStartTempChecking(configMINIMAL_STACK_SIZE, 5);
}

void vApplicationMallocFailedHook(){
	printf("vApplicationMallocFailedHook\n");
	printf("free_heap: %d", xPortGetFreeHeapSize());
}

void vLoggingPrintf( const char *pcFormatString, ... ){
	printf(pcFormatString);
}
BaseType_t xApplicationGetRandomNumber( uint32_t * pulNumber ){
	return rand();
}

uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress, uint16_t usSourcePort, uint32_t ulDestinationAddress, uint16_t usDestinationPort ){
	return 0xdeadbaba;
}

uint32_t ulDNSHandlePacket( const NetworkBufferDescriptor_t * pxNetworkBuffer ){
	return 0;
}

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize ){
   static StaticTask_t xIdleTaskTCB;
   static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

   *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
