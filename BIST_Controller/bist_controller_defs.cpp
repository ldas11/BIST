#include "bist_controller.h"
#include<iostream>

void bist_controller::controlBist() {
	//if the enable input is active, then the other components will be enabled too
	if (enable.read() == 1) {
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
	else if (enable.read() == 0) {
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

void bist_controller::reportBist() {
	testReport_out.write(oraStatus_in);	//subject to change depending on final output format
}