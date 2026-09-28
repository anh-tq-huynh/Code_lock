//
// Created by Anh Huynh on 30.8.2026.
//

#include "TaskPressProcess.h"

#include <string>

#include "vPrintString.h"

void TaskPressProcess::task_check_passcode()
{
	while (true)
	{
		BaseType_t xStatus = xQueueReceive(queue, &receive_input, ticks_timeout);

		if (xStatus != pdPASS)
		{
			//Failed to get a value, like a timeout is reached
			vPrintString("TIMEOUT - RESET THE VERIFICATION PROCESS\n");
			reset();
		}
		else
		{
			//SUCCESSFUL RECEIVE
			verify_in_progress = true;
			verify_passcode();
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}

}

void TaskPressProcess::verify_passcode()
{
	if (receive_input == correct_code[digit_no])
	{
		if (digit_no < code_length - 1)
		{
			digit_no++;
		}
		else
		{
			//SUCCESS
			xEventGroupSetBits(event_grp,ACCESS_GRANTED_BIT);
			vPrintString("CORRECT - ACCESS ALLOWED\n");

			//Lock door countdown
			int countdown = 5000;
			while (countdown >= 0 && uxQueueMessagesWaiting(queue) == 0)
			{
				std::string message = std::string("Locking the door in ")
					+ std::to_string(countdown / 1000)
					+ " second(s)\n";
				vPrintString(message.c_str());
				countdown -= 1000;
				if (countdown < 0)
				{
					vPrintString("DOOR IS LOCKED\n");
				}
				vTaskDelay(pdMS_TO_TICKS(1000));
			}
			xEventGroupClearBits(event_grp, ACCESS_GRANTED_BIT);
			xQueueReset(queue);
			reset();
		}
	}
	else
	{
		vPrintString("WRONG CODE - TRY AGAIN\n");
		reset();
	}
}

void TaskPressProcess::reset()
{
	digit_no = 0;
	verify_in_progress = false;
}
