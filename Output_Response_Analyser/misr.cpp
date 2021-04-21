#include"misr.h"

void misr::stateMachine() {
	switch (state) {
	case idle:
		misr_current_value = 0;
		beginShifting = false;
		output1.write(0);
		oraFinished_out.write(0);
		oraStatus_out.write(0b00);
		state = oraEnable_in.read() ? init : idle;
		if (mac_data_ready_in.read() == 0) {
			state = idle;
		}
		break;
	case init:
		o_data = o_data_in.read();
		beginShifting = true;
		misr_current_value = 0;
		o_data_index = 31;
		oraStatus_out.write(0b10);
		state = oraEnable_in.read() ? run : idle;
		break;
	case run:
		misr::shiftBits();
		o_data_index -= 1;
		oraStatus_out.write(0b00);
		state = oraEnable_in.read() ? run : idle;
		if (o_data_index == -1) {
			state = check_result;
		}
		break;
	case check_result:
		oraFinished_out.write(1);
		if (misr_current_value == 0b11000100001110100100000000000001) {
			oraStatus_out.write(0b11);
		}
		else {
			oraStatus_out.write(0b01);
		}
		state = idle;
		break;
	default:
		oraFinished_out.write(0);
		beginShifting = false;
		oraStatus_out.write(0b00);
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