//
// Created by Anh Huynh on 30.8.2026.
//

#ifndef LAB2_TASKBUTTONPRESS_H
#define LAB2_TASKBUTTONPRESS_H
#include "Button.h"
#include "LED.h"


class taskButtonPress
{
	public:
		taskButtonPress(int btn_pin, int led_pin) : btn(btn_pin), led(led_pin){};

	private:
		Button btn;
		LED led;
};


#endif //LAB2_TASKBUTTONPRESS_H