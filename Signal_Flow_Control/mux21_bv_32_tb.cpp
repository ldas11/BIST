#include"systemc.h"
#include"mux21_bv_32.h"
#include<iostream>

int sc_main(int argc, char* argv[]) {
	//signals
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> sfcEnable_in;					//output depends on the value of sfcEnable_in
	sc_signal<sc_bv<32>> normal_bv, bist_bv;
	sc_signal<float> mux_f_out;
	sc_signal<sc_bv<32>> muxOutput;						//either normalInput or bistInput

	//instantiate a MUX
	mux21_bv_32 mux("Mux");

	//connect signals with ports
	mux.clk(clk);
	mux.sfcEnable_in(sfcEnable_in);
	mux.normal_bv_in(normal_bv);
	mux.bist_bv_in(bist_bv);
	mux.mux_bv_out(muxOutput);
	mux.mux_f_out(mux_f_out);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("mux21_bv_32");
	//signals to trace
	sc_trace(wf, clk, "clk");
	sc_trace(wf, sfcEnable_in, "sfcEnable_in");
	sc_trace(wf, bist_bv, "bist_bv");
	sc_trace(wf, normal_bv, "normal_bv");
	sc_trace(wf, muxOutput, "muxOutput");
	sc_trace(wf, mux_f_out, "mux_f_out");

	//initialize signals
	sfcEnable_in = 0;
	normal_bv = 0;
	bist_bv = 0;
	muxOutput = 0;
	mux_f_out = 0.0;

	sc_bv<32> normal_bv_temp = 0;
	sc_bv<32> bist_bv_temp = 0;
	//start the simulation
	sc_start(0, SC_NS);
	normal_bv_temp = 0b1u;
	normal_bv = normal_bv_temp;
	sc_start(1, SC_NS);
	normal_bv = 0b00111100000000010010101000010000;
	sc_start(1, SC_NS);
	sfcEnable_in = 1;
	bist_bv = 0b00111111001000000000000000000000;
	sc_start(1, SC_NS);
	//exit simulation
	sc_stop();
	std::cout << "exiting simulation" << std::endl;
	sc_close_vcd_trace_file(wf);

	int a = 0;
	std::cin >> a;
	return 0;
}