#include"shift_reg.h"
#include<iostream>

void shift_reg::stateMachine() {
	switch (state) {
	case idle:
		testPattern.write(0);
		std::cout << "idle" << std::endl;
		state = lfsrEnable_in.read() ? test1 : idle;
		break;
	case paused:
		testPattern.write(currentPattern);
		state = lfsrEnable_in.read() ? test2 : paused;
		break;
	case test1:
		currentPattern = 0;
		currentPattern |= 0b11 << 31; // float: -2
		testPattern.write(currentPattern);
		std::cout << "test1, test pattern: " << testPattern << std::endl;
		state = lfsrEnable_in.read() ? paused : idle;
		break;
	case test2:

		break;
	case test3:
		break;
	case test4:
		break;
	case run:
		break;
	default:
		break;
	}
}



void shift_reg::shiftBits(sc_signal<directions> left_right) {
	switch (left_right) {
	case left:
		std::cout << "shifting to the left left" << std::endl;
		for (int i = 31; i > 0; i--) {
			newPattern[i] = currentPattern[i - 1];
		}
		newPattern[0] = 0;
		break;
	case right:
		std::cout << "shifting to the right" << std::endl;
		for (int i = 31; i > 0; i--) {
			newPattern[i-1] = currentPattern[i];
		}
		newPattern[31] = 0;
		break;
	}
	currentPattern = newPattern;
	testPattern.write(currentPattern);
}