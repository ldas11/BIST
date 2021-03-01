#ifndef MUX21b_H
#define MUX21b_H

#include"systemc.h"

SC_MODULE(mux21_b) {
	//ports
	sc_in<bool> sfcEnable_in, clk;		// output depends on the value of sfcEnable_in
	sc_in<bool> normalInput, bistInput;	// normal mode, bist mode
	sc_out<bool> muxOutput;				// either normalInput or bistInput

	void chooseOutput();

	SC_CTOR(mux21_b) {
		SC_METHOD(chooseOutput);		//method chooseOutput selects the value from either normalImput or bistInput and writes it on muxOutput
		sensitive << clk.pos();
	}
};

#endif // !MUX21_H