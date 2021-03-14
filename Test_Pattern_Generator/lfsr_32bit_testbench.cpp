#include"systemc.h"
#include"lfsr_32bit.h"
#include<iostream>

int sc_main(int argc, char* argv[]) {
	//signals
	sc_clock clk("clk", 1, SC_NS);							//clock input
	sc_signal<bool> lfsrEnable_in;							//enable input
	sc_signal<sc_bv<lfsr_32bit::patternWidth>> testPattern;	//pattern output
	
	//instantiation
	lfsr_32bit TPG("TPG");

	//connections
	TPG.clk(clk);
	TPG.lfsrEnable_in(lfsrEnable_in);
	TPG.testPattern(testPattern);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("TPG");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, lfsrEnable_in, "lfsrEnable_in");
	sc_trace(wf, testPattern, "testPattern");

	//initiate signals
	lfsrEnable_in = 0;
	testPattern = 0;

	//start simulation
	sc_start(0, SC_NS);
	std::cout << "starting test" << std::endl;
	sc_start(10, SC_NS);
	std::cout << "enabling the lfsr" << std::endl;
	lfsrEnable_in = 1;
	sc_start(100, SC_US);
	std::cout << "disabling the lfsr" << std::endl;
	lfsrEnable_in = 0;
	sc_start(50, SC_NS);
	sc_stop();
	std::cout << "exiting simulation" << std::endl;
	sc_close_vcd_trace_file(wf);
	int a;
	std::cin >> a;
	return 0;
}