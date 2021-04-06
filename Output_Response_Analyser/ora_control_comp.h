#ifndef ORA_CONTROL_COMP_H
#define ORA_CONTROL_COMP_H

#include"systemc.h"

SC_MODULE(ora_control_comp) {
	sc_in<bool> clk, oraEnable_in, compEnable_in, testEnded;
	sc_in<bool> comp_res_sign, comp_res_rest;
	sc_in<sc_bv<2>> testNumber;
	sc_out<bool> oraFinished_out;
	sc_out<sc_bv<2>> oraStatus_out;
	
	bool comp_rest_temp;
	bool comp_sign_temp;
	int currentTest;

	void fetchResult();

	SC_CTOR(ora_control_comp) {
		SC_METHOD(fetchResult);
		sensitive << clk.pos();
	}
};

#endif // !ORA_CONTROL_COMP_H
