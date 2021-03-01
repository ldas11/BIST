#include"systemc.h"
#include"mux21_b.h"
#include<iostream>

int sc_main(int argc, char* argv[]) {
	//signals
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> sfcEnable_in;					//output depends on the value of sfcEnable_in
	sc_clock normalInput("normalInput",7, SC_NS);	//normal mode input 
	sc_clock bistInput("bistInput", 3, SC_NS);		//bist mode input
	sc_signal<bool> muxOutput;						//either normalInput or bistInput

	//instantiate a MUX
	mux21_b mux("Mux");

	//connect signals with ports
	mux.clk(clk);
	mux.sfcEnable_in(sfcEnable_in);
	mux.normalInput(normalInput);
	mux.bistInput(bistInput);
	mux.muxOutput(muxOutput);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("mux21_b");
	//signals to trace
	sc_trace(wf, clk, "clk");
	sc_trace(wf, sfcEnable_in, "sfcEnable_in");
	sc_trace(wf, normalInput, "normalInput");
	sc_trace(wf, bistInput, "bistInput");
	sc_trace(wf, muxOutput, "muxOutput");

	//initialize signals
	sfcEnable_in = 0;
	muxOutput = 0;

	//start the simulation
	sc_start(0, SC_NS);
	//check initial values, output should be =normalInput
	std::cout << "starting test" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	sc_start(10, SC_NS);
	//assert sfcEnable_in, outputshould now be =bistInput
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	sc_start(10, SC_NS);
	//deassert sfcEnable_in, outputshould now be =normalInput again
	sfcEnable_in = 1;
	std::cout << "deasserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	//test again with arbitrary time values
	sc_start(9, SC_NS);
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(500, SC_PS);																			// interesting case(?)
	sfcEnable_in = 0;
	std::cout << "deasserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(500, SC_PS);
	sfcEnable_in = 0;
	std::cout << "deasserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(2, SC_NS);
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(6, SC_NS);
	sfcEnable_in = 0;
	std::cout << "deasserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(15, SC_NS);
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(7, SC_NS);
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(4, SC_NS);
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(16, SC_NS);
	sfcEnable_in = 0;
	std::cout << "deasserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;
	
	sc_start(5, SC_NS);
	sfcEnable_in = 1;
	std::cout << "asserting sfcEnable" << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_in -> " << sfcEnable_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " normalInput -> " << normalInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " bistInput -> " << bistInput << std::endl;
	std::cout << "@" << sc_time_stamp() << " muxOutput -> " << muxOutput << std::endl;

	//exit simulation
	sc_stop();
	std::cout << "exiting simulation" << std::endl;
	sc_close_vcd_trace_file(wf);
	
	int a = 0;
	std::cin >> a;
	return 0;
}