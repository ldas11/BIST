#include"mux21_bv_32.h"
#include<iostream>

void mux21_bv_32::chooseOutput() {
	if (sfcEnable_in.read() == 0) {
		mux_bv_out.write(normal_bv_in.read());	//normal operation
		std::cout << "normal operation" << std::endl;
	}
	else if (sfcEnable_in == 1) {
		mux_bv_out.write(bist_bv_in.read());		//bist mode, isolating the array inputs 
		std::cout << "bist mode" << std::endl;
	}
}