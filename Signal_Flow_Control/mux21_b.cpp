#include"mux21_b.h"
#include<iostream>

void mux21_b::chooseOutput() {
	if (sfcEnable_in.read() == 0) {
		muxOutput.write(normalInput.read());	//normal operation
		std::cout << "normal operation" << std::endl;
	}
	else if (sfcEnable_in == 1) {
		muxOutput.write(bistInput.read());		//bist mode, isolating the array inputs 
		std::cout << "bist mode" << std::endl;
	}
}