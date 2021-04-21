#include "bist_controller_lfsr.h"
#include<iostream>

void bist_controller_lfsr::enableBist() {
	//if the enable input is active, then the other components will be enabled too
	if (enable_in.read() == 1) {
		if (!lfsr_waitForRestart) {
			std::cout << "enabling pattern generator" << std::endl;
			lfsrEnable_out.write(1);												//enable pattern generator
			std::cout << "lfsrEnable_out is: " << lfsrEnable_out.read() << std::endl;
		}
		
		std::cout << "enabling signal control" << std::endl;
		sfcEnable_out.write(1);													//enable signal flow control
		std::cout << "sfcEnable_out is: " << sfcEnable_out.read() << std::endl;
		
		if (!misr_waitForRestart) {
			std::cout << "enabling ORA" << std::endl;
			oraEnable_out.write(1);													//enable ORA
			std::cout << "oraEnable_out is: " << oraEnable_out.read() << std::endl;
		}
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
		lfsr_waitForRestart = false;
		misr_waitForRestart = false;
	}
	if (finish_acc_in.read() == 1) {
		lfsr_waitForRestart = true;
		lfsrEnable_out.write(0);
	}
	if (oraFinished_in.read() == 1) {
		misr_waitForRestart = true;
		oraEnable_out.write(0);
	}
}

void bist_controller_lfsr::reportBist() {
	if (enable_in.read() == 0) {
		testReport_out.write(0);
	}
	else if (enable_in.read() == 1 && oraFinished_in.read() == 1) {
		testReport_out.write(oraStatus_in.read());	//subject to change depending on final output format
	}
}
