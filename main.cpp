#include <iostream>
#include "FreeRTOS.h"
#include "task.h"
#include  "TaskButtonRead.h"
#include  "TaskPressProcess.h"
#include "vPrintString.h"
#include "pico/stdio.h"

#define D1 22
#define D2 21
#define D3 20

#define SW2 7
#define SW1 8
#define SW0 9


// stack overflow check
extern "C" {
	void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName ) {
		if (pcTaskName != NULL) panic("Stack overflow: %s",pcTaskName);
		else panic("Stack overflow of unnamed task");
	}
	}

#include "hardware/timer.h"
extern "C" {
	uint32_t read_runtime_ctr(void) {
		return timer_hw->timerawl;
	}
}

int main()
{
	stdio_init_all();
	vPrintString("Program starts\n");
	QueueHandle_t queue = xQueueCreate(10,sizeof(int));
	EventGroupHandle_t event_grp = xEventGroupCreate();
	if (queue == nullptr || event_grp == nullptr)
	{
		panic("Failed to create FreeRTOS queue or event group");
	}
	static TaskButtonRead btn0(SW0, D3, 0, queue, event_grp);
	static TaskButtonRead btn1(SW1, D2, 1, queue, event_grp);
	static TaskButtonRead btn2(SW2, D1, 2, queue, event_grp);

	static TaskPressProcess processor(queue, event_grp);
	vTaskStartScheduler();
	while (true){};
}