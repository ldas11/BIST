#include"lfsr_32bit.h"
#include<iostream>

void lfsr_32bit::stateMachine() {
	switch (state) {
		case idle: 
			testPattern.write(0); 
			std::cout << "idle" << std::endl;
			state = lfsrEnable_in.read() ? init : idle; 
			break;
		case init: 
			currentPattern = 2147483648; 
			testPattern.write(currentPattern); 
			std::cout << "init, test pattern: " << testPattern << std::endl;
			state = lfsrEnable_in.read() ? run : idle; 
			break;
		case run: 
			lfsr_32bit::shiftBits(); 
			state = lfsrEnable_in.read() ? run : idle; 
			break;
	}
}


void lfsr_32bit::shiftBits() {
	if (lfsrEnable_in.read() == 1) {
		//shift bits
		for (int i = 31; i > 0; i--) {
			forBruijn = currentPattern[i]|currentPattern[i-1];
			
			newPattern[i] = currentPattern[i - 1];
		}
		//primitive polynomial of 32nd degree: x^32 + x^28 + x^27 + x + 1
		newPattern[0] = currentPattern[31] ^ currentPattern[27] ^ currentPattern[26] ^ currentPattern[0] ^ (~forBruijn);
		//update the current pattern after the shift
		currentPattern = newPattern;
		//std::cout << "current pattern: " << currentPattern << std::endl;
		//write current pattern on the output
		testPattern.write(currentPattern);
		std::cout << "run, test pattern: " << testPattern << std::endl;
	}
}
	