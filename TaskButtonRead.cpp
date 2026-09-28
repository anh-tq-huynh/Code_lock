//
// Created by Anh Huynh on 30.8.2026.
//



#include "FreeRTOS.h"
#include "task.h"
#include "TaskButtonRead.h"


#include "vPrintString.h"
#include "FreeRTOS-KernelV10.6.2/include/queue.h"


void TaskButtonRead::task_read_button()
{
	while (true)
	{
		EventBits_t check_bits = xEventGroupGetBits(event_grp);
		bool btn_pressed = btn.is_pressed();

		if ((check_bits & ACCESS_GRANTED_BIT) != 0)
		{
			led.led_on();
		}
		else
		{
			led.led_off();
		}
		if (btn_pressed)
		{
			//Handle led
			led.toggle_led();
			vTaskDelay(pdMS_TO_TICKS(200));
			led.toggle_led();

			//Print value of the button pressed
			if ((check_bits & ACCESS_GRANTED_BIT) != 0)
			{
				vPrintString("DOOR LOCKED\n");
			}
			else
			{
				vPrintString((std::to_string(lock_code) + " - ").c_str());
			}

			//Add to queue
			xQueueSendToBack(queue, &lock_code,pdMS_TO_TICKS(100));
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
