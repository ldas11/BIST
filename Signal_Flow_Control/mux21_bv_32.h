#ifndef MUX21_BV_32_H
#define MUX21_BV_32_H

#include"systemc.h"

SC_MODULE(mux21_bv_32) {
	//ports
	sc_in<bool> sfcEnable_in, clk;		// output depends on the value of sfcEnable_in
	sc_in<sc_bv<32>> normalInput, bistInput;	// normal mode, bist mode
	sc_out<sc_bv<32>> muxOutput;				// either normalInput or bistInput

	void chooseOutput();

	SC_CTOR(mux21_bv_32) {
		SC_METHOD(chooseOutput);		//method chooseOutput selects the value from either normalImput or bistInput and writes it on muxOutput
		sensitive << clk.pos();
	}
};

#endif // !MUX21_BV_32_H