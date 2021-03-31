#include"shift_reg.h"
#include<iostream>

void shift_reg::stateMachine() {
	if (lfsrEnable_in.read()) {
		switch (current_state) {
			/**
			'idle' state keeps the output at all 0s
			when run=1 --> switch to 'test1'
			when run=0 --> stay 'idle'
			**/
		case idle:
			testPattern_a.write(0);
			testPattern_b.write(0);
			data_enable.write(0);

			std::cout << "idle" << std::endl;
			previous_state = idle;
			current_state = idle;
			next_state = test1;
			count = 0;

			if (run_pause.read()) {
				current_state = next_state;
			}
			else {
				current_state = idle;
			}
			break;

			/**
			while in 'paused' the pattern doesn't change
			when run=1 --> switch to the previous state
			when run=0 --> stay 'paused'
			**/
		case paused:
			testPattern_a.write(currentPattern);
			testPattern_b.write(currentPattern);
			data_enable.write(0);

			if (previous_state != paused) {
				next_state = previous_state;
				previous_state = paused;
			}
			
			std::cout << "paused " << std::endl;
			current_state = run_pause.read() ? next_state : paused;
			break;

			/**
			'test1' is meant to test the sign (bit 31)
			4 variations of the starting pattern are needed
			when run=1&count>=4 --> switch to test2
			when run=0 --> go to 'paused'
			**/
		case test1:
			if (previous_state != test1) {
				if (previous_state != paused) {
					currentPattern = 0;
					currentPattern |= 0b11 << 30; // float: -2
					count = 0;
					std::cout << "count in loop: " << count << std::endl;					
				}
				current_state = test1;
				next_state = test2;
				test1_Pattern = currentPattern;
			}
			else if (previous_state == test1 && count == 1) {
				test1_Pattern[31] = ~test1_Pattern[31];
			}
			else if (previous_state == test1 && count == 2) {
				currentPattern[31] = ~currentPattern[31];
				test1_Pattern[31] = ~test1_Pattern[31];
			}
			else if (previous_state == test1 && count == 3) {
				test1_Pattern[31] = ~test1_Pattern[31];
			}
			
			testPattern_a.write(currentPattern);
			testPattern_b.write(test1_Pattern);
			data_enable.write(1);
			//increase the pattern count by 1
			count += 1;
			std::cout << "test1, test pattern_a: " << testPattern_a << std::endl;
			std::cout << "test1, test pattern_b: " << testPattern_b << std::endl;
			std::cout << "count: " << count << std::endl;
			decide_next_state(count, 4, current_state, next_state);
			
			break;
			/**
			'test2' generates the 8 bits that correspond to the exponent (bits 30-23)
			total of 8 values needed
			when run=1&count>=8 --> switch to test3
			when run=0 --> go to 'paused'
			only shift bits to the right while count<8
			**/
		case test2:
			if (previous_state != test2) {
				if (previous_state != paused) {
					currentPattern = 0;
					currentPattern |= 0b01 << 30;
					count = 0;
					std::cout << "count in loop: " << count << std::endl;
				}
				current_state = test2;
				next_state = test3;
			}
			
			testPattern_a.write(currentPattern);
			testPattern_b.write(currentPattern);
			data_enable.write(1);
			//increase the pattern count by 1
			count += 1;
			std::cout << "test2, test pattern: " << testPattern_a << std::endl;
			std::cout << "count: " << count << std::endl;
			decide_next_state(count, 8, current_state, next_state);

			if (count < 9) {
				shift_reg::shiftBits(true);
			}
			break;

			/**
			'test3' generates the 23 bits that correspond to the mantissa (bits 22-0)
			total of 23 values needed
			when run=1&count>=23 --> switch to test4
			when run=0 --> go to 'paused'
			only shift bits to the right while count<23
			**/
		case test3:
			if (previous_state != test3) {
				if (previous_state != paused) {
					currentPattern = 0;
					currentPattern |= 0b01 << 22;
					count = 0;
					std::cout << "count in loop: " << count << std::endl;
					
				}
				current_state = test3;
				next_state = test4;
			}
			

			testPattern_a.write(currentPattern);
			testPattern_b.write(currentPattern);
			data_enable.write(1);
			//increase the pattern count by 1
			count += 1;
			std::cout << "test3, test pattern: " << testPattern_a << std::endl;
			std::cout << "count: " << count << std::endl;
			decide_next_state(count, 23, current_state, next_state);

			if (count < 24) {
				shift_reg::shiftBits(true);
			}
			break;

			/**
			'test4' generates bits that correspond to the mantissa (bits 22-0)
			total of 23 values needed
			when run=1&count>=23 --> switch to test3
			when run=0 --> go to 'paused'
			only shift bits to the left while count<23
			**/
		case test4:
			if (previous_state != test4) {
				if (previous_state != paused) {
					currentPattern = 0;
					currentPattern |= 0b01;
					count = 0;
					std::cout << "count in loop: " << count << std::endl;					
				}
				current_state = test4;
				next_state = idle;
			}
			
			testPattern_a.write(currentPattern);
			testPattern_b.write(currentPattern);
			data_enable.write(1);
			//increase the pattern count by 1
			count += 1;
			std::cout << "test4, test pattern: " << testPattern_a << std::endl;
			std::cout << "count: " << count << std::endl;
			decide_next_state(count, 23, current_state, next_state);

			if (count < 24) {
				shift_reg::shiftBits(false);	//shift to the left
			}
			break;

			//'dafault' is the same as 'idle'
		default:
			testPattern_a.write(0);
			testPattern_b.write(0);
			data_enable.write(0);
			std::cout << "idle/default" << std::endl;
			previous_state = idle;
			current_state = idle;
			next_state = test1;

			if (run_pause.read()) {
				current_state = lfsrEnable_in.read() ? next_state : idle;
				count = 0;
			}
			else {
				current_state = idle;
			}
			break;
		}
	}
	else {
		testPattern_a.write(0);
		testPattern_b.write(0);
		data_enable.write(0);
		std::cout << "disabled" << std::endl;
		previous_state = idle;
		current_state = idle;
		next_state = test1;
	}
}




void shift_reg::shiftBits(bool left_right) {
	switch (left_right) {
	case false:
		std::cout << "shifting to the left" << std::endl;
		for (int i = 31; i > 0; i--) {
			newPattern[i] = currentPattern[i - 1];
		}
		newPattern[0] = 0;
		break;
	case true:
		std::cout << "shifting to the right" << std::endl;
		for (int i = 31; i > 0; i--) {
			newPattern[i-1] = currentPattern[i];
		}
		newPattern[31] = 0;
		break;
	}
	currentPattern = newPattern;
	//testPattern.write(currentPattern);
}

void shift_reg::decide_next_state(int current_count, int max_count, state_names current, state_names next) {
	if (current_count >= max_count) {
		current_state = run_pause.read() ? next : paused;
		previous_state = current;
	}
	else {
		//shift_reg::shiftBits(direction);
		current_state = run_pause.read() ? current : paused;
		previous_state = current;
	}
}