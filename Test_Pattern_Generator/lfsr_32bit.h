//#pragma once
#ifndef LFSR_32BIT_H
#define LFSR_32BIT_H

#include"systemc.h"
SC_MODULE(lfsr_32bit) {
	static const int patternWidth = 32;			//for the pattern width in bits
	// ports
	sc_in<bool> clk, lfsrEnable_in;				//clock input, enable input
	sc_out<sc_bv<patternWidth>> testPattern;	//pattern output
	sc_bv<patternWidth> currentPattern;
	sc_bv<patternWidth> newPattern;
	sc_bit forBruijn;

	enum state_names{idle, init, run};
	sc_signal<state_names> state;
	void stateMachine();

	void shiftBits();

	SC_CTOR(lfsr_32bit) {
		SC_METHOD(stateMachine);
		sensitive << clk.pos();	//method stateMachine is sensible to positive clock edges
	}
};

#endif // !LFSR_32BIT_H