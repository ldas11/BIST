#include"systemc.h"
#include"comparator.h"
#include<iostream>

int sc_main(int argc, char* argv[]) {
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> enable;
	sc_signal<sc_bv<32>> mac_data, ref_data;
	sc_signal<sc_bv<32>> result;

	comparator comp("COMP");

	comp.clk(clk);
	comp.enable(enable);
	comp.mac_data(mac_data);
	comp.ref_data(ref_data);
	comp.result(result);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("comparator");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, enable, "enable");
	sc_trace(wf, mac_data, "mac_data");
	sc_trace(wf, ref_data, "ref_data");
	sc_trace(wf, result, "result");

	enable = 0;
	mac_data = 0;
	ref_data = 0;
	result = 0;


	sc_start(0, SC_NS);
	std::cout << "starting test" << std::endl;
	sc_start(5, SC_NS);
	enable = 1;
	mac_data = 14;
	ref_data = 8;
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