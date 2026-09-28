//
// Created by Anh Huynh on 30.8.2026.
//

#ifndef LAB2_BUTTON_H
#define LAB2_BUTTON_H
#include "GPIOPin.h"


class Button
{
	public:
		Button(const int btn_pin) : btn(btn_pin, true, true, true){};
		bool is_pressed();
	private:
		GPIOPin btn;
		bool last_btn_state = false;
		uint32_t last_press_time = 0;

};


#endif //LAB2_BUTTON_H