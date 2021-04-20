#include"mux21_b.h"
#include<iostream>

void mux21_b::chooseOutput() {
	if (sfcEnable_in.read() == 0) {
		mux_b_out.write(normal_b_in.read());	//normal operation
		std::cout << "normal operation" << std::endl;
	}
	else if (sfcEnable_in == 1) {
		mux_b_out.write(bist_b_in.read());		//bist mode, isolating the array inputs 
		std::cout << "bist mode" << std::endl;
	}
}