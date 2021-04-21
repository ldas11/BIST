//#pragma once
#ifndef BIST_CONTROLLER_H
#define BIST_CONTROLLER_H

#include"systemc.h"

SC_MODULE(bist_controller) {
	//ports
	sc_in<bool> enable_in, clk;
	sc_in<bool> oraFinished_in;
	sc_in<sc_bv<2>> oraStatus_in;
	sc_out<bool> lfsrEnable_out, sfcEnable_out, oraEnable_out; //enable LFSR(pattern generator), enable signal flow control, enable output response analyser
	sc_out<sc_bv<2>> testReport_out; //type and bitwidth subject to change
	sc_in<bool> data_en_in;
	//sc_out<bool> a_valid_out, b_valid_out, finish_acc_out;
	sc_out<bool> run_pause_out;
	sc_out<bool> testEnded_out;
	
	int count;
	bool isTestRunning;

	void enableBist();
	void controlBist();
	void reportBist();

	SC_CTOR(bist_controller) {
		SC_METHOD(enableBist);		//method controlBist is in charge of enabling/disabling the other modules
		sensitive << clk.pos();		//respond to changes in enable and on positive clock edges

		SC_METHOD(controlBist);
		sensitive << clk.pos();

		SC_METHOD(reportBist);	//method reportBist transmits the result delivered by the ORA
		sensitive << clk.pos();	//respond to changes in oraStatus_in and on positive clock edges
	}
};

#endif // !BIST_CONTROLLER_H