#ifndef COMPARATOR_H
#define COMPARATOR_H

#include"systemc.h"

SC_MODULE(comparator) {
	sc_in<bool> clk, enable;
	sc_in<sc_bv<32>> mac_data, ref_data;
	sc_out<sc_bv<32>> result;

	sc_bv<32> mac_data_local;
	sc_bv<32> ref_data_local;
	sc_bv<32> comp_res;
	

	void compare();

	SC_CTOR(comparator) {
		SC_METHOD(compare);
		sensitive << clk.pos();
	}
};


#endif // !COMPARATOR_H