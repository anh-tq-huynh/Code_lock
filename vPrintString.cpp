//
// Created by Anh Huynh on 30.8.2026.
//

#include "vPrintString.h"

#include <cstdio>

#include "FreeRTOS.h"
#include "task.h"

void vPrintString( const char *pcString )
{
	/* Write the string to stdout, using a critical section as a crude method of
	mutual exclusion. */
	taskENTER_CRITICAL();
	{
		printf( "%s", pcString );
		fflush( stdout );
	}
	taskEXIT_CRITICAL();
}