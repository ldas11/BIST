#include "ora_control_comp.h"

void ora_control_comp::fetchResult() {
	if (oraEnable_in.read() == 1) {
		
		if (testEnded.read() == 1) {
			oraFinished_out.write(1);
		}
		
		if (compEnable_in.read() == 1) {
			
			comp_rest_temp = comp_res_rest.read();
			comp_sign_temp = comp_res_sign.read();

			if (comp_rest_temp == 0 || comp_sign_temp == 0) {
				oraFinished_out.write(1);
				oraStatus_out.write(0b01);
			}
			else if (comp_rest_temp == 1 && comp_sign_temp ==1) {
				oraStatus_out.write(0b11);
			}
			else {
				oraFinished_out.write(1);
				oraStatus_out.write(0b10);
			}

		}
	}
	else if(oraEnable_in.read() == 0) {
		oraFinished_out.write(0);
		oraStatus_out.write(0b00);
	}
}