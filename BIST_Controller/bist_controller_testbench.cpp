#include"systemc.h"
#include"bist_controller.h"
#include<iostream>
//#include"bist_controller_defs.cpp"
//#include"bist_controller.cpp"

int sc_main(int argc, char* argv[]) {
	//signals
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> enable;
	sc_signal<sc_bv<2>> oraStatus_in;
	sc_signal<bool> lfsrEnable_out, sfcEnable_out, oraEnable_out; //enable LFSR(pattern generator), enable signal flow control, enable output response analyser
	sc_signal<sc_bv<2>> testReport_out;
	sc_signal<bool>  oraFinished, data_en_in, a_valid_out, b_valid_out, finish_acc_out,
		run_pause_out;
	//instantiate a controller for the testbench
	bist_controller controller("Controller");

	//connect the controller to the testbench
	controller.enable(enable);
	controller.clk(clk);
	controller.oraStatus_in(oraStatus_in);
	controller.lfsrEnable_out(lfsrEnable_out);
	controller.sfcEnable_out(sfcEnable_out);
	controller.oraEnable_out(oraEnable_out);
	controller.testReport_out(testReport_out);
	controller.oraFinished(oraFinished);
	controller.data_en_in(data_en_in);
	controller.a_valid_out(a_valid_out);
	controller.b_valid_out(b_valid_out);
	controller.finish_acc_out(finish_acc_out);
	controller.run_pause_out(run_pause_out);
	
	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("bist_controller");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, enable, "enable");
	sc_trace(wf, lfsrEnable_out, "lfsrEnable_out");
	sc_trace(wf, sfcEnable_out, "sfcEnable_out");
	sc_trace(wf, oraEnable_out, "oraEnable_out");
	sc_trace(wf, oraStatus_in, "oraStatus_in");
	sc_trace(wf, testReport_out, "testReport_out");
	sc_trace(wf, oraFinished, "oraFinished");
	sc_trace(wf, data_en_in, "data_en_in");
	sc_trace(wf, a_valid_out, "a_valid_out");
	sc_trace(wf, b_valid_out, "b_valid_out");
	sc_trace(wf, finish_acc_out, "finish_acc_out");
	sc_trace(wf, run_pause_out, "run_pause_out");

	//initialize signals
	enable = 0;
	oraStatus_in = 0;
	lfsrEnable_out = 0;
	sfcEnable_out = 0;
	oraEnable_out = 0;
	testReport_out = 0;
	oraFinished = 0;
	data_en_in = 0;
	a_valid_out = 0;
	b_valid_out = 0;
	finish_acc_out = 0;
	run_pause_out = 0;

	//start the simulation
	sc_start(0, SC_NS);
	//check the values are all 0 at the start
	std::cout << "starting test" << std::endl;
	std::cout << "@" << sc_time_stamp() << " enable -> " << enable << std::endl;
	std::cout << "@" << sc_time_stamp() << " lfsrEnable_out -> " << lfsrEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_out -> " << sfcEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraEnable_out -> " << oraEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraStatus_in -> " << oraStatus_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " testReport_out -> " << testReport_out << std::endl;
	sc_start(10, SC_NS);
	//checking if the sub module enables are triggeredafter the main enable is activated
	enable = 1;		
	data_en_in = 1;
	std::cout << "enabling the controller" << std::endl;
	std::cout << "@" << sc_time_stamp() << " enable -> " << enable << std::endl;
	std::cout << "@" << sc_time_stamp() << " lfsrEnable_out -> " << lfsrEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_out -> " << sfcEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraEnable_out -> " << oraEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraStatus_in -> " << oraStatus_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " testReport_out -> " << testReport_out << std::endl;
	sc_start(100, SC_NS);
	//checking the test report output works as intended (testReport_out=oraStatus_in)
	oraStatus_in = 3;
	oraFinished = 1;
	std::cout << "@" << sc_time_stamp() << " enable -> " << enable << std::endl;
	std::cout << "@" << sc_time_stamp() << " lfsrEnable_out -> " << lfsrEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_out -> " << sfcEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraEnable_out -> " << oraEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraStatus_in -> " << oraStatus_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " testReport_out -> " << testReport_out << std::endl;
	sc_start(10, SC_NS);
	//disable the controller, all outputs should be 0
	enable = 0;
	std::cout << "@" << sc_time_stamp() << " enable -> " << enable << std::endl;
	std::cout << "@" << sc_time_stamp() << " lfsrEnable_out -> " << lfsrEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " sfcEnable_out -> " << sfcEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraEnable_out -> " << oraEnable_out << std::endl;
	std::cout << "@" << sc_time_stamp() << " oraStatus_in -> " << oraStatus_in << std::endl;
	std::cout << "@" << sc_time_stamp() << " testReport_out -> " << testReport_out << std::endl;
	sc_start(10, SC_NS);
	sc_stop();
	std::cout << "exiting simulation" << std::endl;
	sc_close_vcd_trace_file(wf);
	return 0;
}