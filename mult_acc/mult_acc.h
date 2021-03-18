#ifndef MULT_ACC_H
#define MULT_ACC_H

#include"systemc.h"

SC_MODULE(mult_acc) {
	sc_in<bool> clk, reset, a_valid, b_valid, finish_acc;
	sc_in<float> a_data, b_data;
	sc_out<float> o_data;

	float accumulation;
	float a_data_local, b_data_local;

	sc_fifo<float> a_fifo;
	sc_fifo<float> b_fifo;

	void process();
	
	SC_CTOR(mult_acc) {
		SC_METHOD(process);
		sensitive << clk.pos();
	}
};

#endif // !MULT_ACC_H