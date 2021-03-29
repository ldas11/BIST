#ifndef SHIFT_REG_H
#define SHIFT_REG_H

#include"systemc.h"

SC_MODULE(shift_reg) {
	static const int patternWidth = 32;			//for the pattern width in bits
	// ports
	sc_in<bool> clk, lfsrEnable_in, run_pause;	//clock input, enable input, run/pause input
	sc_out<sc_bv<patternWidth>> testPattern;	//pattern output
	sc_bv<patternWidth> currentPattern;
	sc_bv<patternWidth> newPattern;
	

	enum state_names { idle, paused, test1, test2, test3, test4};
	sc_signal<state_names> current_state;
	sc_signal<state_names> previous_state;
	sc_signal<state_names> next_state;
	void stateMachine();

	int count;

	void shiftBits(bool left_right);

	void decide_next_state(int current_count, int max_count, state_names current, state_names next);

	SC_CTOR(shift_reg) {
		SC_METHOD(stateMachine);
		sensitive << clk.pos();	//method stateMachine is sensible to positive clock edges
	}
};

#endif // !SHIFT_REG_H