#ifndef BIST_CONTROLLER_LFSR_H
#define BIST_CONTROLLER_LFSR_H

#include"systemc.h"

SC_MODULE(bist_controller_lfsr) {
	//ports
	sc_in<bool> enable_in, clk;
	sc_in<bool> oraFinished_in, finish_acc_in;
	sc_in<sc_bv<2>> oraStatus_in;
	sc_out<bool> lfsrEnable_out, sfcEnable_out, oraEnable_out; //enable LFSR(pattern generator), enable signal flow control, enable output response analyser
	sc_out<sc_bv<2>> testReport_out; //type and bitwidth subject to change

	int count;
	bool isTestRunning;
	bool lfsr_waitForRestart;
	bool misr_waitForRestart;

	void enableBist();
	
	void reportBist();

	SC_CTOR(bist_controller_lfsr) {
		SC_METHOD(enableBist);		//method controlBist is in charge of enabling/disabling the other modules
		sensitive << clk.pos();		//respond to changes in enable and on positive clock edges

		SC_METHOD(reportBist);	//method reportBist transmits the result delivered by the ORA
		sensitive << clk.pos();	//respond to changes in oraStatus_in and on positive clock edges
	}
};

#endif // !BIST_CONTROLLER_LFSR_H