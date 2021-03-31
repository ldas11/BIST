#include "systemc.h"
#include "shift_reg.h"
#include <iostream>


int sc_main(int argc, char* argv[]) {
	//signals
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> lfsrEnable_in, run_pause, data_enable;	//clock input, enable input, run/pause input
	sc_signal<sc_bv<32>> testPattern;

	//instantiation
	shift_reg tpg("TPG");

	//connections
	tpg.clk(clk);
	tpg.lfsrEnable_in(lfsrEnable_in);
	tpg.run_pause(run_pause);
	tpg.testPattern(testPattern);
	tpg.data_enable(data_enable);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("shift_reg");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, lfsrEnable_in, "enable");
	sc_trace(wf, run_pause, "run_pause");
	sc_trace(wf, testPattern, "testPattern");
	sc_trace(wf, data_enable, "data_enable");

	//init
	lfsrEnable_in = 0;
	run_pause = 0;
	testPattern = 0;
	data_enable = 0;

	//start sim
	sc_start(0, SC_NS);
	std::cout << "starting test" << std::endl;
	sc_start(10, SC_NS);
	lfsrEnable_in = 1;
	sc_start(10, SC_NS);
	run_pause = 1;
	sc_start(25, SC_NS);
	run_pause = 0;
	sc_start(5, SC_NS);
	run_pause = 1;
	sc_start(100, SC_NS);
	
	run_pause = 0;
	sc_start(10, SC_NS);
	run_pause = 1;
	sc_start(10, SC_NS);
	lfsrEnable_in = 0;
	sc_start(10, SC_NS);


	//exit sim
	sc_stop();

	std::cout << "exiting simulation" << std::endl;

	sc_close_vcd_trace_file(wf);

	int a;
	std::cin >> a;
	return 0;
}