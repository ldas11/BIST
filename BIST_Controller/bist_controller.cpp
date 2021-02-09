//#include "bist_controller.h"
#include<iostream>
#include"systemc.h"

SC_MODULE(bist_controller) {
	//ports
	sc_in<bool> enable, clk;
	sc_in<sc_bv<2>> oraStatus_in;
	sc_out<bool> lfsrEnable_out, sfcEnable_out, oraEnable_out; //enable LFSR(pattern generator), enable signal flow control, enable output response analyser
	sc_out<sc_bv<2>> testReport_out; //type and bitwidth subject to change

	void controlBist() {
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

	void reportBist() {
		testReport_out.write(oraStatus_in);	//subject to change depending on final output format
	}

	SC_CTOR(bist_controller) {
		SC_METHOD(controlBist);					//method controlBist is in charge of enabling/disabling the other modules
			sensitive << enable << clk.pos();		//respond to changes in enable and on positive clock edges
		
		SC_METHOD(reportBist);					//method reportBist transmits the result delivered by the ORA
			sensitive << oraStatus_in << clk.pos();	//respond to changes in oraStatus_in and on positive clock edges
	}
};