#include"systemc.h"
#include<iostream>

SC_MODULE(lfsr_32bit) {
	static const int patternWidth = 32;			//for the pattern width in bits
	// ports
	sc_in<bool> clk, lfsrEnable_in;				//clock input, enable input
	sc_out<sc_bv<patternWidth>> testPattern;	//pattern output
	sc_bv<patternWidth> currentPattern;	
	sc_bv<patternWidth> newPattern;

	void shiftBits() {
		if (lfsrEnable_in.read() == 1) {
			//shift bits
			for (int i = 31; i > 0; i--) {
				newPattern[i] = currentPattern[i - 1];
			}
			//primitive polynomial of 32nd degree: x^32 + x^28 + x^27 + x + 1
			newPattern[0] = currentPattern[31] ^ currentPattern[27] ^ currentPattern[26] ^ currentPattern[0];
			//update the current pattern after the shift
			currentPattern = newPattern;
			std::cout << "current pattern: " << currentPattern << std::endl;
			//write current pattern on the output
			testPattern.write(currentPattern);
			std::cout << "test pattern: " << testPattern << std::endl;
		}
	}

	SC_CTOR(lfsr_32bit) {
		SC_METHOD(shiftBits);
			sensitive << clk.pos();	//method shiftBits is sensible to positive clock edges and changes in the enable input
	}
};