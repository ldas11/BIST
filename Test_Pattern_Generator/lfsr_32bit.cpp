#include"lfsr_32bit.h"
#include<iostream>

void lfsr_32bit::stateMachine() {
	switch (state) {
		case idle: 
			count = 0;
			testPattern_a_out.write(0);
			testPattern_b_out.write(0);
			a_valid_out.write(0);
			b_valid_out.write(0);
			finish_acc_out.write(0);
			std::cout << "idle" << std::endl;
			state = lfsrEnable_in.read() ? init : idle; 
			break;
		case init: 
			currentPattern = 2147483648; 
			testPattern_a_out.write(currentPattern); 
			testPattern_b_out.write(currentPattern);
			std::cout << "init, test pattern: " << testPattern_a_out << std::endl;
			state = lfsrEnable_in.read() ? run : idle; 
			break;
		case run: 
			a_valid_out.write(1);
			b_valid_out.write(1);
			lfsr_32bit::shiftBits(); 
			count += 1;
			state = lfsrEnable_in.read() ? run : idle; 
			if (count > 150) {
				state = request_result;
			}
			break;
		case request_result:
			a_valid_out.write(0);
			b_valid_out.write(0);
			finish_acc_out.write(1);
			state = idle;
			break;
		default:
			count = 0;
			testPattern_a_out.write(0);
			testPattern_b_out.write(0);
			a_valid_out.write(0);
			b_valid_out.write(0);
			finish_acc_out.write(0);
			std::cout << "idle" << std::endl;
			state = lfsrEnable_in.read() ? init : idle;
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
		testPattern_a_out.write(currentPattern);
		testPattern_b_out.write(currentPattern);
		std::cout << "run, test pattern: " << testPattern_a_out << std::endl;
	}
}
	