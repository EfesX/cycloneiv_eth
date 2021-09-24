/*
    FreeRTOS V202107.00
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*
 * FreeRTOS tasks are used with FreeRTOS+TCP to create a TCP echo server on the
 * standard echo port number (7).
 *
 * See the following web page for essential demo usage and configuration
 * details:
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Server.html
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

#include "FreeRTOSIPConfig.h"

/* Remove the whole file if FreeRTOSIPConfig.h is set to exclude TCP. */
#if( ipconfigUSE_TCP == 1 )

/* The maximum time to wait for a closing socket to close. */
#define tcpechoSHUTDOWN_DELAY	( pdMS_TO_TICKS( 5000 ) )

/* The standard echo port number. */
#define tcpechoPORT_NUMBER		23

/* If ipconfigUSE_TCP_WIN is 1 then the Tx sockets will use a buffer size set by
ipconfigTCP_TX_BUFFER_LENGTH, and the Tx window size will be
configECHO_SERVER_TX_WINDOW_SIZE times the buffer size.  Note
ipconfigTCP_TX_BUFFER_LENGTH is set in FreeRTOSIPConfig.h as it is a standard TCP/IP
stack constant, whereas configECHO_SERVER_TX_WINDOW_SIZE is set in
FreeRTOSConfig.h as it is a demo application constant. */
#ifndef configECHO_SERVER_TX_WINDOW_SIZE
	#define configECHO_SERVER_TX_WINDOW_SIZE	2
#endif

/* If ipconfigUSE_TCP_WIN is 1 then the Rx sockets will use a buffer size set by
ipconfigTCP_RX_BUFFER_LENGTH, and the Rx window size will be
configECHO_SERVER_RX_WINDOW_SIZE times the buffer size.  Note
ipconfigTCP_RX_BUFFER_LENGTH is set in FreeRTOSIPConfig.h as it is a standard TCP/IP
stack constant, whereas configECHO_SERVER_RX_WINDOW_SIZE is set in
FreeRTOSConfig.h as it is a demo application constant. */
#ifndef configECHO_SERVER_RX_WINDOW_SIZE
	#define configECHO_SERVER_RX_WINDOW_SIZE	2
#endif

/*-----------------------------------------------------------*/
uint8_t close_flag = 0;
/*
 * Uses FreeRTOS+TCP to listen for incoming echo connections, creating a task
 * to handle each connection.
 */
static void prvConnectionListeningTask( void *pvParameters );

/*
 * Created by the connection listening task to handle a single connection.
 */
static void prvServerConnectionInstance( void *pvParameters );

/*-----------------------------------------------------------*/

/* Stores the stack size passed into vStartSimpleTCPServerTasks() so it can be
reused when the server listening task creates tasks to handle connections. */
static uint16_t usUsedStackSize = 0;

/*-----------------------------------------------------------*/

void vStartTelnetServer( uint16_t usStackSize, UBaseType_t uxPriority )
{
	/* Create the TCP echo server. */
	xTaskCreate( prvConnectionListeningTask, "Telnet", usStackSize, NULL, uxPriority + 1, NULL );

	/* Remember the requested stack size so it can be re-used by the server
	listening task when it creates tasks to handle connections. */
	usUsedStackSize = usStackSize;
}
/*-----------------------------------------------------------*/

char rx_buf[ipconfigTCP_MSS];
char tx_buf[ipconfigTCP_MSS];
static const TickType_t xReceiveTimeOut = pdMS_TO_TICKS( 5000 );
static const TickType_t xSendTimeOut = pdMS_TO_TICKS( 5000 );

static void prvConnectionListeningTask( void *pvParameters )
{
struct freertos_sockaddr xClient, xBindAddress;
Socket_t xListeningSocket, xConnectedSocket;
socklen_t xSize = sizeof( xClient );
static const TickType_t xReceiveTimeOut = portMAX_DELAY;
const BaseType_t xBacklog = 20;
int32_t lBytes;
TickType_t xTimeOnShutdown;
portBASE_TYPE xMoreDataToFollow;

const char *const tHeader = "************************************************\r\n"
		"TELNET SERVER ON eFPGA + NIOSII + ENC28J60\r\n"
		"************************************************\r\n"
		">> \0";
int32_t lSent = strlen(tHeader);

#if( ipconfigUSE_TCP_WIN == 1 )
	WinProperties_t xWinProps;

	/* Fill in the buffer and window sizes that will be used by the socket. */
	xWinProps.lTxBufSize = ipconfigTCP_TX_BUFFER_LENGTH;
	xWinProps.lTxWinSize = configECHO_SERVER_TX_WINDOW_SIZE;
	xWinProps.lRxBufSize = ipconfigTCP_RX_BUFFER_LENGTH;
	xWinProps.lRxWinSize = configECHO_SERVER_RX_WINDOW_SIZE;
#endif /* ipconfigUSE_TCP_WIN */

	/* Just to prevent compiler warnings. */
	( void ) pvParameters;

	/* Attempt to open the socket. */
	xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP );
	configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

	/* Set a time out so accept() will just wait for a connection. */
	FreeRTOS_setsockopt( xListeningSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );

	/* Set the window and buffer sizes. */
	#if( ipconfigUSE_TCP_WIN == 1 )
	{
		FreeRTOS_setsockopt( xListeningSocket, 0, FREERTOS_SO_WIN_PROPERTIES, ( void * ) &xWinProps, sizeof( xWinProps ) );
	}
	#endif /* ipconfigUSE_TCP_WIN */

	/* Bind the socket to the port that the client task will send to, then
	listen for incoming connections. */
	xBindAddress.sin_port = tcpechoPORT_NUMBER;
	xBindAddress.sin_port = FreeRTOS_htons( xBindAddress.sin_port );
	FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );
	FreeRTOS_listen( xListeningSocket, xBacklog );

	while(1){
		/* Wait for a client to connect. */
		xConnectedSocket = FreeRTOS_accept( xListeningSocket, &xClient, &xSize );
		configASSERT( xConnectedSocket != FREERTOS_INVALID_SOCKET );
		/* Spawn a task to handle the connection. */
		if(xConnectedSocket != FREERTOS_INVALID_SOCKET){
			FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );
			FreeRTOS_setsockopt( xConnectedSocket, 0, FREERTOS_SO_SNDTIMEO, &xSendTimeOut, sizeof( xReceiveTimeOut ) );
			lSent = FreeRTOS_send(xConnectedSocket, tHeader, strlen(tHeader), NULL);
			if(lSent == strlen(tHeader)){
				while(1){
					memset( rx_buf, 0x00, ipconfigTCP_MSS );
					lBytes = FreeRTOS_recv( xConnectedSocket, rx_buf, ipconfigTCP_MSS, 0 );
					if( lBytes >= 0 ){
						if((uint8_t)rx_buf[0] == 0xff){
							printf("negotiation\n");
						}else{
							rx_buf[lBytes-2] = 0x00;
							do{
								xMoreDataToFollow = FreeRTOS_CLIProcessCommand(rx_buf, tx_buf, ipconfigTCP_MSS);
								lSent = FreeRTOS_send(xConnectedSocket, tx_buf, strlen(tx_buf),NULL);
							}while(xMoreDataToFollow != pdFALSE);

							if (close_flag == 1) {
								close_flag = 0;
								break;
							}

							if(lSent < 0) break;
							lSent = FreeRTOS_send(xConnectedSocket, ">> \0", strlen(">> \0"), NULL);
							if(lSent < 0) break;
						}
					}else break;
				}
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
/* The whole file is excluded if TCP is not compiled in. */
#endif /* ipconfigUSE_TCP */

