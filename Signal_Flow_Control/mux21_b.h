#ifndef MUX21_B_H
#define MUX21_B_H

#include"systemc.h"

SC_MODULE(mux21_b) {
	//ports
	sc_in<bool> sfcEnable_in;		// output depends on the value of sfcEnable_in
	sc_in<bool> normal_b_in, bist_b_in;	// normal mode, bist mode
	sc_out<bool> mux_b_out;				// either normalInput or bistInput

	void chooseOutput();

	SC_CTOR(mux21_b) {
		SC_METHOD(chooseOutput);		//method chooseOutput selects the value from either normalImput or bistInput and writes it on muxOutput
		sensitive << bist_b_in;
	}
};

#endif // !MUX21_B_H