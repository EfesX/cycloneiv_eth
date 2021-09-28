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


uint8_t my_ip[4] = {192, 168, 1, 70};
uint8_t mymask[4] = {255, 255, 255, 0};
uint8_t mygate[4] = {192, 168, 1, 1};
volatile uint8_t mymac[6] = {0x54, 0x55, 0x58, 0x11, 0x00, 0x24};

#define mainQUEUE_SEND_FREQUENCY_MS			( 250 / portTICK_RATE_MS )

void vApplicationStackOverflowHook(TaskHandle_t  pxCurrentTCB, char *pcTaskName ){
	printf("vApplicationStackOverflowHook\n");
}


alt_u8 rxbuffer[0x200]; 

int main(void)
{
	eeprom_init();

	eeprom_buffer_tx_t tx_buf;
	tx_buf.addr = 0x0101;
	tx_buf.data[0] = 0xde;
	tx_buf.data[1] = 0xad;
	tx_buf.data[2] = 0xbe;
	tx_buf.data[3] = 0xaf;



	eeprom_write_32(0x0000, 0x01020304);
	eeprom_read(0x0000, rxbuffer, 4);

	vRegisterCLICommands();

	FreeRTOS_IPInit(my_ip, mymask, mygate, NULL, mymac);

	vTaskStartScheduler();

	return 0;
}


void vApplicationIPNetworkEventHook(eIPCallbackEvent_t ev){
	printf("vApplicationIPNetworkEventHook\n");
	vStartTelnetServer(configMINIMAL_STACK_SIZE * 2, 6);
	vStartHTTPServer(configMINIMAL_STACK_SIZE*2, 8);
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
