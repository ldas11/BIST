#include "bist_controller.h"
#include<iostream>

void bist_controller::enableBist() {
	//if the enable input is active, then the other components will be enabled too
	if (enable_in.read() == 1) {
		std::cout << "enabling pattern generator" << std::endl;
		lfsrEnable_out.write(1);												//enable pattern generator
		std::cout << "lfsrEnable_out is: " << lfsrEnable_out.read() << std::endl;

		std::cout << "enabling signal control" << std::endl;
		sfcEnable_out.write(1);													//enable signal flow control
		std::cout << "sfcEnable_out is: " << sfcEnable_out.read() << std::endl;

		std::cout << "enabling ORA" << std::endl;
		oraEnable_out.write(1);													//enable ORA
		std::cout << "oraEnable_out is: " << oraEnable_out.read() << std::endl;
	}//otherwise disable the other modules
	else if (enable_in.read() == 0) {
		std::cout << "disabling pattern generator" << std::endl;
		lfsrEnable_out.write(0);												//disable pattern generator												
		std::cout << "lfsrEnable_out is: " << lfsrEnable_out.read() << std::endl;

		std::cout << "disabling signal control" << std::endl;
		sfcEnable_out.write(0);													//disable signal flow control
		std::cout << "sfcEnable_out is: " << sfcEnable_out.read() << std::endl;

		std::cout << "disabling ORA" << std::endl;
		oraEnable_out.write(0);													//disable ORA
		std::cout << "oraEnable_out is: " << oraEnable_out.read() << std::endl;
	}
}

void bist_controller::controlBist() {
	if (enable_in.read() == 0) {
		
		a_valid_out.write(0);
		b_valid_out.write(0);
		run_pause_out.write(0);
		finish_acc_out.write(0);
		testEnded_out.write(0);
		count = 0;
	}
	else if (enable_in.read() == 1 && oraFinished_in.read() == 0) {
		
		run_pause_out.write(1);
		
		if (data_en_in.read() == 1) {
			a_valid_out.write(1);
			b_valid_out.write(1);
			finish_acc_out.write(1);
			count += 1;
		}
		else {
			a_valid_out.write(0);
			b_valid_out.write(0);
			finish_acc_out.write(0);
		}
	}

	if (count >= 58 || oraFinished_in.read() == 1) {
		run_pause_out.write(0);
		finish_acc_out.write(0);
		testEnded_out.write(1);
		count = 0;
	}
	
}

void bist_controller::reportBist() {
	if (enable_in.read() == 0) {
		testReport_out.write(0);
	}
	else if (enable_in.read() == 1 && oraFinished_in.read() == 1) {
		testReport_out.write(oraStatus_in.read());	//subject to change depending on final output format
	}
}
	