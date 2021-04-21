#include"misr.h"
void misr::serialize() {
	if (oraEnable_in.read() == 1 && mac_data_ready_in.read() == 1) {
		o_data = o_data_in.read();
		beginShifting = true;
		for (int i = 31; i >= 0; i--) {
			
		}		
	}
	else {
		beginShifting = false;
		initializeCount = false;
	}
}

void misr::stateMachine() {
	switch (state) {
	case idle:
		misr_current_value = 0;
		output1.write(0);
		oraFinished_out.write(0);
		state = oraEnable_in.read() ? init : idle;
		break;
	case init:
		o_data = o_data_in.read();
		misr_current_value = 0;
		o_data_index = 31;
		state = oraEnable_in.read() ? run : idle;
		break;
	case run:
		misr::shiftBits();
		o_data_index -= 1;
		state = oraEnable_in.read() ? run : idle;
		if (o_data_index == -1) {
			state = check_result;
		}
		break;
	case check_result:
		oraFinished_out.write(1);
		if (misr_current_value == 0b0000010000011010101000010101010101010100000000000000000000000000) {
			
		}
		break;
	default:
		oraFinished_out.write(1);
		state = oraEnable_in.read() ? init : idle;
		break;
	}
}

void misr::shiftBits() {
	if (beginShifting) {
		//characteristic polynomial for n=64: x^n+x^4+x^3+x+1
		misr_new_value[0] = o_data[o_data_index] ^ misr_current_value[63];
		for (int i = 1; i < 64; i++) {
			if (i < 5 && i != 2) {
				misr_new_value[i] = misr_current_value[i - 1] ^ misr_current_value[63];
			}
			else {
				misr_new_value[i] = misr_current_value[i - 1];
			}
		}
	}
	
	misr_current_value = misr_new_value;
	output1.write(misr_current_value);
}