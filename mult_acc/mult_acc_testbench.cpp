#include"systemc.h"
#include"mult_acc.h"
#include<iostream>

int sc_main(int argc, char* argv[]) {
	//signals
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> reset, a_valid, b_valid, finish_acc;
	sc_signal<float> a_data, b_data, acc_reg;
	sc_signal<sc_bv<32>> o_data;

	//instantiation
	mult_acc mac("MAC");

	//connections
	mac.clk(clk);
	mac.reset(reset);
	mac.a_valid(a_valid);
	mac.b_valid(b_valid);
	mac.finish_acc(finish_acc);
	mac.a_data(a_data);
	mac.b_data(b_data);
	mac.o_data(o_data);
	mac.acc_reg(acc_reg);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("mult_acc");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, reset, "reset");
	sc_trace(wf, a_valid, "a_valid");
	sc_trace(wf, b_valid, "b_valid");
	sc_trace(wf, finish_acc, "finish_acc");
	sc_trace(wf, a_data, "a_data");
	sc_trace(wf, b_data, "b_data");
	sc_trace(wf, o_data, "o_data");
	sc_trace(wf, acc_reg, "acc_reg");

	reset = 1;
	a_valid = 0;
	b_valid = 0;
	finish_acc = 0;
	a_data = 0.0;
	b_data = 0.0;
	o_data = 0;
	acc_reg = 0.0;
	sc_start(0, SC_NS);
	std::cout << "starting test" << std::endl;
	sc_start(5, SC_NS);
	reset = 0;
	a_valid = 1;
	b_valid = 1;
	a_data = 3.5;
	b_data = 1;
	sc_start(0.5, SC_NS);
	a_valid = 0;
	b_valid = 0;
	sc_start(10, SC_NS);
	//a_valid = 1;
	//b_valid = 1;
	//a_data = -3.5;
	//b_data = 1;
	sc_start(10, SC_NS);
	a_valid = 0;
	b_valid = 0;
	sc_start(10, SC_NS);
	finish_acc = 1;
	sc_start(10, SC_NS);
	finish_acc = 0;
	sc_start(10, SC_NS);
	reset = 1;
	sc_start(10, SC_NS);
	sc_stop();
	
	std::cout << "exiting simulation" << std::endl;
	
	sc_close_vcd_trace_file(wf);
	
	int a;
	std::cin >> a;

	return 0;
}