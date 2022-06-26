/*
 * http_server.c
 *
 *  Created on: Sep 15, 2021
 *      Author: root
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

#include "FreeRTOSIPConfig.h"

#include "at24c08.h"


#define tcpechoSHUTDOWN_DELAY	( pdMS_TO_TICKS( 5000 ) )


static uint16_t usUsedStackSize = 0;

static const TickType_t xReceiveTimeOut = pdMS_TO_TICKS( 5000 );
static const TickType_t xSendTimeOut = pdMS_TO_TICKS( 5000 );

static alt_u8 tx_buf[ipconfigTCP_MSS];
static alt_u8 rx_buf[ipconfigTCP_MSS];

const alt_u8 http_header[] = "HTTP/1.1 200 OK"
		"Date: Mon, 27 Jul 2009 12:28:53 GMT"
		"Server: Apache/2.2.14 (Win32)"
		"Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT"
		"Content-Type: text/html"
		"Connection: Closed"
		"\r\n\r\n";



xTaskHandle fwInstTaskHandle;




static void prvHTTPServer(void *p);
void prvFirmwareRXInstanceTask(void *p);
static void prvFirmwareRXListeninigTask(void *p);

void vStartHTTPServer( uint16_t usStackSize, UBaseType_t uxPriority){
	/* Create the TCP echo server. */
	xTaskCreate( prvHTTPServer, "http", usStackSize, NULL, uxPriority + 1, NULL );
	xTaskCreate(prvFirmwareRXListeninigTask, "fw_listen", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

	/* Remember the requested stack size so it can be re-used by the server
	listening task when it creates tasks to handle connections. */
	usUsedStackSize = usStackSize;
}

static void prvHTTPServer(void *p){
	struct freertos_sockaddr xClient, xBindAddress;
	Socket_t xListeningSocket, xConnectedSocket;
	socklen_t xSize = sizeof( xClient );
	static const TickType_t xReceiveTimeOut = portMAX_DELAY;
	const BaseType_t xBacklog = 20;
	int32_t lBytes, totalBytes = 0;
	TickType_t xTimeOnShutdown;
	portBASE_TYPE xMoreDataToFollow;

	/* Just to prevent compiler warnings. */
	( void ) p;

	/* Attempt to open the socket. */
	xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP );
	configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

	/* Set a time out so accept() will just wait for a connection. */
	FreeRTOS_setsockopt( xListeningSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );

	/* Bind the socket to the port that the client task will send to, then
	listen for incoming connections. */
	xBindAddress.sin_port = 80;
	xBindAddress.sin_port = FreeRTOS_htons( xBindAddress.sin_port );
	FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );
	FreeRTOS_listen( xListeningSocket, xBacklog );

	uint32_t len = 0;
	uint8_t *fw;

	while(1){
		/* Wait for a client to connect. */
		xConnectedSocket = FreeRTOS_accept( xListeningSocket, &xClient, &xSize );
		configASSERT( xConnectedSocket != FREERTOS_INVALID_SOCKET );
		/* Spawn a task to handle the connection. */
		if(xConnectedSocket != FREERTOS_INVALID_SOCKET){
			FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );
			FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_SNDTIMEO, &xSendTimeOut, sizeof( xReceiveTimeOut ) );

			FreeRTOS_send(xConnectedSocket, http_header, strlen(http_header), NULL);
			len = eeprom_read_32(0);
			fw = (uint8_t *) pvPortMalloc(ipconfigTCP_MSS);

			for(uint32_t i = 0; i < len; i++){
				fw[i] = eeprom_read_8(16 + i);
			}
			uint32_t lentx = len;
			while (totalBytes < len){
				lBytes = FreeRTOS_send(xConnectedSocket, &fw[totalBytes], lentx, NULL);
				totalBytes += lBytes;
			}
			
			FreeRTOS_shutdown( xConnectedSocket, FREERTOS_SHUT_RDWR );
			xTimeOnShutdown = xTaskGetTickCount();
			do{
				if( FreeRTOS_recv( xConnectedSocket, rx_buf, ipconfigTCP_MSS, 0 ) < 0 )break;
			} while( ( xTaskGetTickCount() - xTimeOnShutdown ) < tcpechoSHUTDOWN_DELAY );
			FreeRTOS_closesocket( xConnectedSocket );
		}
	}
}


static void prvFirmwareRXListeninigTask(void *p){
	struct freertos_sockaddr xClient, xBindAddress;
	Socket_t xListeningSocket, xConnectedSocket;
	socklen_t xSize = sizeof( xClient );
	static const TickType_t xReceiveTimeOut = portMAX_DELAY;
	const BaseType_t xBacklog = 20;
	int32_t lBytes;
	TickType_t xTimeOnShutdown;
	portBASE_TYPE xMoreDataToFollow;

	/* Just to prevent compiler warnings. */
	( void ) p;

	/* Attempt to open the socket. */
	xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP );
	configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

	/* Set a time out so accept() will just wait for a connection. */
	FreeRTOS_setsockopt( xListeningSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );

	/* Bind the socket to the port that the client task will send to, then
	listen for incoming connections. */
	xBindAddress.sin_port = 5900;
	xBindAddress.sin_port = FreeRTOS_htons( xBindAddress.sin_port );
	FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );
	FreeRTOS_listen( xListeningSocket, xBacklog );

	while(1){
		/* Wait for a client to connect. */
		xConnectedSocket = FreeRTOS_accept( xListeningSocket, &xClient, &xSize );
		configASSERT( xConnectedSocket != FREERTOS_INVALID_SOCKET );
		/* Spawn a task to handle the connection. */
		if(xConnectedSocket != FREERTOS_INVALID_SOCKET){
 			xTaskCreate(prvFirmwareRXInstanceTask, "fw_inst", configMINIMAL_STACK_SIZE * 3, (void *) xConnectedSocket, 5, &fwInstTaskHandle);
		}
	}
}

char test[3413];

void prvFirmwareRXInstanceTask(void *p){
	int32_t lBytes = 0, totalBytes = 0;
	Socket_t xConnectedSocket;
	static const TickType_t xReceiveTimeOut = pdMS_TO_TICKS( 5000 );
	static const TickType_t xSendTimeOut = pdMS_TO_TICKS( 5000 );
	TickType_t xTimeOnShutdown;
	uint8_t *pucRxBuffer;
	uint8_t *fw;

	xConnectedSocket = ( Socket_t ) p;

	pucRxBuffer = ( uint8_t * ) pvPortMalloc( ipconfigTCP_MSS );

	uint32_t content_length = 0;
	char *pLen = NULL;

	eeprom_buffer_tx_t eeprom_buf;

	if (pucRxBuffer != NULL){
		FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );
		FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_SNDTIMEO, &xSendTimeOut, sizeof( xReceiveTimeOut ) );

		while(1){
			lBytes = FreeRTOS_recv( xConnectedSocket, pucRxBuffer, ipconfigTCP_MSS, 0 );
			pLen = strstr(pucRxBuffer, "Content-Length:");
			content_length = strtol(pLen + sizeof("Content-Length:"), NULL, 10);
			fw = (uint8_t *) pvPortMalloc(content_length);
			lBytes = 0;
			while (totalBytes < content_length){
				lBytes = FreeRTOS_recv( xConnectedSocket, &fw[totalBytes], content_length, 0 );
				totalBytes += lBytes;	
			}
			for(uint16_t i = 0; i < content_length; i++){
				eeprom_write_8(16 + i, fw[i]);
			}
			
			for(uint16_t i = 0; i < 3413; i++){
				test[i] = eeprom_read_8(i);
			}

			eeprom_write_32(0, content_length);

			break;
		}
	}
	/* Initiate a shutdown in case it has not already been initiated. */
	FreeRTOS_shutdown( xConnectedSocket, FREERTOS_SHUT_RDWR );

	/* Wait for the shutdown to take effect, indicated by FreeRTOS_recv()
	returning an error. */
	xTimeOnShutdown = xTaskGetTickCount();
	do{
		if( FreeRTOS_recv( xConnectedSocket, pucRxBuffer, ipconfigTCP_MSS, 0 ) < 0 ) break;
	} while( ( xTaskGetTickCount() - xTimeOnShutdown ) < tcpechoSHUTDOWN_DELAY );

	/* Finished with the socket, buffer, the task. */
	vPortFree(pucRxBuffer);
	FreeRTOS_closesocket(xConnectedSocket);
	vTaskDelete(NULL);
}