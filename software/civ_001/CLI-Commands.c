/*
 * CLI-Commands.c
 *
 *  Created on: Sep 11, 2021
 *      Author: root
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* FreeRTOS+CLI includes. */
#include "FreeRTOS_CLI.h"

static HeapStats_t hs;

static BaseType_t prvTaskStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t prvHeapStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t prvTaskTimeStatCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t prvTaskNetbufCount( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

/* Structure that defines the "task-stats" command line command. */
static const CLI_Command_Definition_t xTaskStats =
{
	"task-stats", /* The command string to type. */
	"\r\ntask-stats:\r\n Displays a table showing the state of each FreeRTOS task\r\n\r\n",
	prvTaskStatsCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
static const CLI_Command_Definition_t xHeapStats =
{
	"heap-stats", /* The command string to type. */
	"\r\nheap-stats:\r\n Displays using heap statistic\r\n\r\n",
	prvHeapStatsCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
static const CLI_Command_Definition_t xTaskTimeStats =
{
	"task-timestats", /* The command string to type. */
	"\r\nheap-stats:\r\n Displays time statistic for each task\r\n\r\n",
	prvTaskTimeStatCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
static const CLI_Command_Definition_t xNetBuf =
{
	"netbuf", /* The command string to type. */
	"\r\nheap-stats:\r\n Displays count of network buffers\r\n\r\n",
	prvTaskNetbufCount, /* The function to run. */
	0 /* No parameters are expected. */
};

static BaseType_t prvTaskNetbufCount( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
	const char *const pcHeader = "Network Buffers #\r\n************************************************\r\n";
	strcpy(pcWriteBuffer, pcHeader);

	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "NumberOfFreeNetworkBuffers: %d\r\n", uxGetNumberOfFreeNetworkBuffers());
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "MinimumFreeNetworkBuffers:  %d\r\n", uxGetMinimumFreeNetworkBuffers());

	return pdFALSE;
}

static BaseType_t prvTaskStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
	const char *const pcHeader = "Task State  Priority  Stack #\r\n************************************************\r\n";
	strcpy(pcWriteBuffer, pcHeader);

	vTaskList(pcWriteBuffer + strlen(pcWriteBuffer));

	return pdFALSE;
}

static BaseType_t prvHeapStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
	const char *const pcHeader = "Heap Statistics:\r\n************************************************\r\n";
	strcpy( pcWriteBuffer, pcHeader );

	vPortGetHeapStats(&hs);

	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xAvailableHeapSpaceInBytes:      %d\r\n",   hs.xAvailableHeapSpaceInBytes);
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xNumberOfFreeBlocks:             %d\r\n",   hs.xNumberOfFreeBlocks);
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xMinimumEverFreeBytesRemaining:  %d\r\n",   hs.xMinimumEverFreeBytesRemaining);
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xNumberOfSuccessfulAllocations:  %d\r\n",   hs.xNumberOfSuccessfulAllocations);
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xNumberOfSuccessfulFrees:        %d\r\n",   hs.xNumberOfSuccessfulFrees);
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xSizeOfSmallestFreeBlockInBytes: %d\r\n",   hs.xSizeOfSmallestFreeBlockInBytes);
	sprintf(pcWriteBuffer + strlen(pcWriteBuffer), "xSizeOfLargestFreeBlockInBytes:  %d\r\n\0", hs.xSizeOfLargestFreeBlockInBytes);

	return pdFALSE;
}

static BaseType_t prvTaskTimeStatCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString ){
	const char *const pcHeader = "Tasks Time Statistic:\r\n************************************************\r\n";
	strcpy( pcWriteBuffer, pcHeader );
	vTaskGetRunTimeStats(pcWriteBuffer + strlen(pcWriteBuffer));
	return pdFALSE;
}

void vRegisterCLICommands( void ){
	/* Register all the command line commands defined immediately above. */
	FreeRTOS_CLIRegisterCommand( &xTaskStats );
	FreeRTOS_CLIRegisterCommand( &xHeapStats );
	FreeRTOS_CLIRegisterCommand( &xTaskTimeStats );
	FreeRTOS_CLIRegisterCommand( &xNetBuf );
}


