//
// Created by Anh Huynh on 30.8.2026.
//

#ifndef LAB2_LED_H
#define LAB2_LED_H
#include "GPIOPin.h"


class LED
{
	public:
		explicit LED(int led_pin) : led(led_pin,false, false, false){};
		void toggle_led();

		void led_off() const;

		void led_on() const;

	private:
		GPIOPin led;
		bool last_state = false;
};


#endif //LAB2_LED_H