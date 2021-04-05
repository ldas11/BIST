#ifndef COMPACTOR_AND_H
#define COMPACTOR_AND_H

#include"systemc.h"

SC_MODULE(compactor_nand) {
	sc_in<sc_bv<31>> toCompact;
	sc_out<bool> compacted;
	
	sc_bv<31> toCompact_temp;
	sc_bv<1> compacted_temp;

	void compact();

	SC_CTOR(compactor_nand) {
		SC_METHOD(compact);
		sensitive << toCompact;
	}
};

#endif	// !COMPACTOR_AND_H