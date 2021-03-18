#ifndef MULT_ACC_H
#define MULT_ACC_H

#include"systemc.h"

SC_MODULE(mult_acc) {
	sc_in<bool> clk, reset, a_valid, b_valid, finish_acc;
	sc_in<float> a_data, b_data;
	sc_out<float> acc_reg;
	sc_out<sc_bv<32>> o_data;

	sc_uint<32> o_data_reg;
	float accumulation;
	float a_data_local, b_data_local;

	sc_fifo<float> a_fifo;
	sc_fifo<float> b_fifo;

	void process();
	sc_bv<32> float_to_sc_uint(float value);

	SC_CTOR(mult_acc) {
		SC_METHOD(process);
		sensitive << clk.pos();
	}
};

#endif // !MULT_ACC_H