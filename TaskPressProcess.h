//
// Created by Anh Huynh on 30.8.2026.
//

#ifndef LAB2_TASKPRESSPROCESS_H
#define LAB2_TASKPRESSPROCESS_H


#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"
#define ACCESS_GRANTED_BIT (1 << 0)

class Queue;

class TaskPressProcess
{
	public:
		explicit TaskPressProcess(QueueHandle_t queue, EventGroupHandle_t event_grp)
		: queue(queue), receive_input(), handle(), event_grp(event_grp)
		{
			xTaskCreate(TaskPressProcess::runner, "Button press process", 512, (void *) this,
				tskIDLE_PRIORITY + 1, &handle);
		};
		void task_check_passcode();
		void verify_passcode();
		void reset();

	private:
		static void runner(void *params)
		{
			auto *instance = static_cast<TaskPressProcess *> (params);
			instance -> task_check_passcode();
		}
		int receive_input;
		QueueHandle_t queue;
		EventGroupHandle_t event_grp;
		TickType_t ticks_timeout = pdMS_TO_TICKS(5000);
		bool verify_in_progress = false;
		int digit_no = 0;
		int correct_code[5] = {0,2,1,0,2};
		int code_length = sizeof(correct_code) / sizeof(correct_code[0]);
		TaskHandle_t handle;
};


#endif //LAB2_TASKPRESSPROCESS_H