#include<iostream>
#include"bist_controller_lfsr.h"
#include"lfsr_32bit.h"
#include"mult_acc.h"
#include"mult_acc_faulty.h"
#include"mux21_b.h"
#include"mux21_bv_32.h"
#include"shift_reg.h"
#include"misr.h"

int sc_main(int argc, char* argv[]) {
	//system level signals
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> enable;
	sc_signal<sc_bv<2>> testReport;
	sc_signal<bool> a_valid_sys;
	sc_signal<bool> b_valid_sys;
	sc_signal<bool> finish_acc_sys;
	sc_signal<sc_bv<32>> pattern_a_sys;
	sc_signal<sc_bv<32>> pattern_b_sys;
	//controller related signals
	sc_signal<bool> lfsrEnable;
	sc_signal<bool> sfcEnable;
	sc_signal<bool> oraEnable;
	sc_signal<sc_bv<2>> oraStatus;
	sc_signal<bool> oraFinished;
	sc_signal<bool> testEnded;
	//TPG related signals
	sc_signal<sc_bv<32>> testPattern_a;
	sc_signal<sc_bv<32>> testPattern_b;
	sc_signal<bool> a_valid_bist;
	sc_signal<bool> b_valid_bist;
	sc_signal<bool> finish_acc_bist;
	//CUT related signals
	sc_signal<bool> reset;
	sc_signal<float> data_a;
	sc_signal<bool> data_a_valid;
	sc_signal<float> data_b;
	sc_signal<bool> data_b_valid;
	sc_signal<bool> acc_finish;
	sc_signal<float> acc_reg;
	sc_signal<sc_bv<32>> o_data;
	sc_signal<bool> mac_data_ready;
	//ora signals already declared

	//faulty
	sc_signal<int> faultybit;

	bist_controller_lfsr main_control("CTRL");
	mult_acc mac("MAC");
	//mult_acc_f mac("MAC_F");
	mux21_b mux_a_valid("MUX_A_VALID");
	mux21_b mux_b_valid("MUX_B_VALID");
	mux21_b mux_finish_acc("MUX_FINISH_ACC");
	mux21_bv_32 mux_a_data("MUX_A_DATA");
	mux21_bv_32 mux_b_data("MUX_B_DATA");
	misr sar("SAR");
	lfsr_32bit shifter("TPG");

	//connections system-controller
	main_control.clk(clk);
	main_control.enable_in(enable);
	main_control.testReport_out(testReport);
	//connections controller-TPG
	main_control.lfsrEnable_out(lfsrEnable);
	main_control.finish_acc_in(finish_acc_bist);
	//connections controller-mux
	main_control.sfcEnable_out(sfcEnable);
	//connections controller-ora	
	main_control.oraEnable_out(oraEnable);
	main_control.oraFinished_in(oraFinished);
	main_control.oraStatus_in(oraStatus);

	//connections TPG
	shifter.clk(clk);
	shifter.lfsrEnable_in(lfsrEnable);
	shifter.testPattern_a_out(testPattern_a);
	shifter.testPattern_b_out(testPattern_b);
	shifter.a_valid_out(a_valid_bist);
	shifter.b_valid_out(b_valid_bist);
	shifter.finish_acc_out(finish_acc_bist);
	//connections mux_a_valid
	mux_a_valid.sfcEnable_in(sfcEnable);
	mux_a_valid.bist_b_in(a_valid_bist);
	mux_a_valid.normal_b_in(a_valid_sys);
	mux_a_valid.mux_b_out(data_a_valid);
	//connections mux_b_valid
	mux_b_valid.sfcEnable_in(sfcEnable);
	mux_b_valid.bist_b_in(b_valid_bist);
	mux_b_valid.normal_b_in(b_valid_sys);
	mux_b_valid.mux_b_out(data_b_valid);
	//connections mux_finish_acc
	mux_finish_acc.sfcEnable_in(sfcEnable);
	mux_finish_acc.bist_b_in(finish_acc_bist);
	mux_finish_acc.normal_b_in(finish_acc_sys);
	mux_finish_acc.mux_b_out(acc_finish);
	//connections mux_a_data
	mux_a_data.sfcEnable_in(sfcEnable);
	mux_a_data.bist_bv_in(testPattern_a);
	mux_a_data.normal_bv_in(pattern_a_sys);
	mux_a_data.mux_f_out(data_a); //check transformation to float
	//connections mux_b_data
	mux_b_data.sfcEnable_in(sfcEnable);
	mux_b_data.bist_bv_in(testPattern_b);
	mux_b_data.normal_bv_in(pattern_b_sys);
	mux_b_data.mux_f_out(data_b); //check transformation to float
	//connections CUT
	mac.clk(clk);
	mac.reset(reset);
	mac.a_valid_in(data_a_valid);
	mac.b_valid_in(data_b_valid);
	mac.finish_acc_in(acc_finish);
	mac.a_data_in(data_a);
	mac.b_data_in(data_b);
	mac.acc_reg_out(acc_reg);
	mac.o_data_out(o_data);
	mac.mac_data_ready_out(mac_data_ready);
	//mac.faultPosition_in(faultybit);
	//ora control connections
	sar.clk(clk);
	sar.oraEnable_in(oraEnable);
	sar.oraFinished_out(oraFinished);
	sar.oraStatus_out(oraStatus);
	sar.mac_data_ready_in(mac_data_ready);
	sar.o_data_in(o_data);
	
	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("bist_lfsr_a");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, enable, "enable");
	sc_trace(wf, testReport, "testReport");
	sc_trace(wf, a_valid_sys, "a_valid_sys");
	sc_trace(wf, b_valid_sys, "b_valid_sys");
	sc_trace(wf, finish_acc_sys, "finish_acc_sys");
	sc_trace(wf, pattern_a_sys, "pattern_a_sys");
	sc_trace(wf, pattern_b_sys, "pattern_b_sys");
	sc_trace(wf, lfsrEnable, "lfsrEnable");
	sc_trace(wf, sfcEnable, "sfcEnable");
	sc_trace(wf, oraEnable, "oraEnable");
	sc_trace(wf, oraStatus, "oraStatus");
	sc_trace(wf, oraFinished, "oraFinished");
	sc_trace(wf, testEnded, "testEnded");
	sc_trace(wf, a_valid_bist, "a_valid_bist");
	sc_trace(wf, b_valid_bist, "b_valid_bist");
	sc_trace(wf, finish_acc_bist, "finish_acc_bist");
	sc_trace(wf, testPattern_a, "testPattern_a");
	sc_trace(wf, testPattern_b, "testPattern_b");
	sc_trace(wf, reset, "reset");
	sc_trace(wf, data_a, "data_a");
	sc_trace(wf, data_a_valid, "data_a_valid");
	sc_trace(wf, data_b, "data_b");
	sc_trace(wf, data_b_valid, "data_b_valid");
	sc_trace(wf, acc_finish, "acc_finish");
	sc_trace(wf, acc_reg, "acc_reg");
	sc_trace(wf, o_data, "o_data");
	sc_trace(wf, mac_data_ready, "mac_data_ready");

	enable = 0;
	testReport = 0;
	a_valid_sys = 0;
	b_valid_sys = 0;
	finish_acc_sys = 0;
	pattern_a_sys = 0;
	pattern_b_sys = 0;
	reset = 1;
	faultybit = 0;

	sc_start(1, SC_NS);
	/*
	for(int i = 0; i<32; i++){
		enable = 1;
		reset = 0;
		faultybit = i;
		sc_start(40, SC_NS);
		enable = 0;
		reset = 1;
		sc_start(5, SC_NS);
	}
	*/
	enable = 1;
	reset = 0;
	sc_start(250, SC_NS);
	enable = 0;
	reset = 1;
	sc_start(5, SC_NS);

	sc_stop();
	std::cout << "exiting simulation" << std::endl;
	sc_close_vcd_trace_file(wf);

	int a;
	std::cin >> a;

	return 0;
}