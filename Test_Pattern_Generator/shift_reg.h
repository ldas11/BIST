#ifndef SHIFT_REG_H
#define SHIFT_REG_H

#include"systemc.h"

SC_MODULE(shift_reg) {
	static const int patternWidth = 32;			//for the pattern width in bits
	// ports
	sc_in<bool> clk, lfsrEnable_in;				//clock input, enable input
	sc_out<sc_bv<patternWidth>> testPattern;	//pattern output
	sc_bv<patternWidth> currentPattern;
	sc_bv<patternWidth> newPattern;
	sc_bit forBruijn;

	enum state_names { idle, paused, test1, test2, test3, test4, run};
	sc_signal<state_names> state;
	void stateMachine();

	enum directions{left, right};
	sc_signal<directions> shift_direction;
	void shiftBits(sc_signal<directions> left_right);

	SC_CTOR(shift_reg) {
		SC_METHOD(stateMachine);
		sensitive << clk.pos();	//method stateMachine is sensible to positive clock edges
	}
};

#endif // !SHIFT_REG_H