#ifndef MISR_H
#define MISR_H
#include<iostream>
#include"systemc.h"

SC_MODULE(misr) {
	//ports
	sc_in<bool> clk, oraEnable_in, mac_data_ready_in; //testEnded_in;
	sc_in<sc_bv<32>> o_data_in;
	sc_out<bool> oraFinished_out;
	sc_out<sc_bv<2>> oraStatus_out;
	
	sc_out<sc_bv<64>> output1;

	enum state_names { idle, init, run, check_result};
	sc_signal<state_names> state;

	
	bool beginShifting;
	bool initializeCount;
	int o_data_index;
	sc_bv<32> o_data;
	sc_fifo<sc_bv<1>> input_serial;
	sc_bv<64> misr_current_value;
	sc_bv<64> misr_new_value;

	//functions
	void serialize();
	void shiftBits();
	void stateMachine();

	SC_CTOR(misr) {
		//SC_METHOD(serialize);
		//sensitive << clk.pos();

		SC_METHOD(stateMachine);
		sensitive << clk.pos();


		sc_fifo<sc_bv<1>> input_serial (32);
	}
};

#endif // !MISR_H