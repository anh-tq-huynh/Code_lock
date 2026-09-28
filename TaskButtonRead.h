//
// Created by Anh Huynh on 30.8.2026.
//

#ifndef LAB2_TASKBUTTONPRESS_H
#define LAB2_TASKBUTTONPRESS_H
#include "FreeRTOS.h"
#include <string>

#include "Button.h"
#include "event_groups.h"
#include "LED.h"
#include "Queue.h"
#define ACCESS_GRANTED_BIT (1 << 0)


class TaskButtonRead
{
	public:
		TaskButtonRead(int btn_pin, int led_pin, int lock_code, QueueHandle_t queue, EventGroupHandle_t event_grp)
		:
		btn(btn_pin),
		led(led_pin),
		queue(queue),
		lock_code(lock_code),
		name("Code: " + std::to_string(lock_code)),
		handle(),
		event_grp(event_grp)
		{
			xTaskCreate(TaskButtonRead::button_reader,
				name.c_str(),
				512,
				(void *) this,
				tskIDLE_PRIORITY + 1, &handle);
		};
		void task_read_button();

	private:
		static void button_reader(void *params)
		{
			auto *instance = static_cast<TaskButtonRead *> (params);
			instance -> task_read_button();
		}
		EventGroupHandle_t event_grp;
		std::string name;
		int lock_code;
		Button btn;
		LED led;
		QueueHandle_t queue;
		TaskHandle_t handle;
};


#endif //LAB2_TASKBUTTONPRESS_H