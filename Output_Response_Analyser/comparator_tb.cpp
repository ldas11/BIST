#include"systemc.h"
#include"comparator.h"
#include<iostream>

int sc_main(int argc, char* argv[]) {
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> enable;
	sc_signal<sc_bv<32>> mac_data, ref_data;
	sc_signal<sc_bv<1>> ref_data_b;
	sc_signal<sc_bv<1>> result_sign;
	sc_signal<sc_bv<31>> result_rest;

	comparator comp("COMP");

	comp.clk(clk);
	comp.enable(enable);
	comp.mac_data(mac_data);
	comp.ref_data(ref_data);
	comp.ref_data_b(ref_data_b);
	comp.result_sign(result_sign);
	comp.result_rest(result_rest);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("comparator");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, enable, "enable");
	sc_trace(wf, mac_data, "mac_data");
	sc_trace(wf, ref_data, "ref_data");
	sc_trace(wf, ref_data_b, "ref_data_b");
	sc_trace(wf, result_sign, "result_sign");
	sc_trace(wf, result_rest, "result_rest");

	enable = 0;
	mac_data = 0;
	ref_data = 0;
	ref_data_b = 0;
	result_sign = 0;
	result_rest = 0;

	sc_start(0, SC_NS);
	std::cout << "starting test" << std::endl;
	sc_start(5, SC_NS);
	enable = 1;
	mac_data = 14;
	ref_data = 8;
	ref_data_b = 0;
	sc_start(5, SC_NS);
	enable = 0;
	sc_start(5, SC_NS);


	sc_stop();

	std::cout << "exiting simulation" << std::endl;

	sc_close_vcd_trace_file(wf);

	int a;
	std::cin >> a;

	return 0;
}