#ifndef COMPARATOR_H
#define COMPARATOR_H

#include"systemc.h"

SC_MODULE(comparator) {
	sc_in<bool> clk, enable;
	//sc_in<sc_bv<2>> currentTest_in;
	sc_in<sc_bv<32>> mac_data_in, ref_data_in;
	sc_in<sc_bv<1>> ref_data_b_in;
	sc_out<sc_bv<1>> result_sign_out;
	sc_out<sc_bv<31>> result_rest_out;

	sc_bv<32> mac_data_local;
	sc_bv<32> ref_data_local;
	sc_bv<1> ref_data_b_local;

	sc_bv<1> comp_res_sign;
	sc_bv<32> comp_res_rest;
	

	void compare();

	SC_CTOR(comparator) {
		SC_METHOD(compare);
		sensitive << clk.pos();
	}
};


#endif // !COMPARATOR_H