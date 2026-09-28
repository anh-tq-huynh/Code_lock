//
// Created by Anh Huynh on 30.8.2026.
//

#ifndef LAB2_GPIOPIN_H
#define LAB2_GPIOPIN_H
#include <cstdint>


class GPIOPin
{
	public:
		explicit GPIOPin(int pin, bool input = true, bool pullup = true, bool invert = false);
		GPIOPin(const GPIOPin &) = delete;
		~GPIOPin();
		bool read() const;
		void write(bool value) const;
		explicit operator bool() const;
	private:
		bool is_dormant;
		bool is_input;
		int pin;
		static uint32_t pins_in_use;
};


#endif //LAB2_GPIOPIN_H