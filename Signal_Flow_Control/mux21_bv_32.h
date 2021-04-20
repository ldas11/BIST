#ifndef MUX21_BV_32_H
#define MUX21_BV_32_H

#include"systemc.h"

SC_MODULE(mux21_bv_32) {
	//ports
	sc_in<bool> sfcEnable_in;		// output depends on the value of sfcEnable_in
	sc_in<sc_bv<32>> normal_bv_in, bist_bv_in;	// normal mode, bist mode
	sc_out<float> mux_f_out;
	//sc_out<sc_bv<32>> mux_bv_out;				// either normalInput or bistInput

	void chooseOutput();
	float bv_to_float(sc_bv<32> bit_vector);

	SC_CTOR(mux21_bv_32) {
		SC_METHOD(chooseOutput);		//method chooseOutput selects the value from either normalImput or bistInput and writes it on muxOutput
		sensitive << bist_bv_in;
	}
};

#endif // !MUX21_BV_32_H