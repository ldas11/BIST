#include"systemc.h"
//#include"bist_controller.h"
//#include"bist_controller_defs.cpp"
#include"bist_controller.cpp"

int sc_main(int argc, char* argv[]) {
	//signals
	sc_signal<bool> enable, clk;
	sc_signal<sc_bv<2>> oraStatus_in;
	sc_signal<bool> lfsrEnable_out, sfcEnable_out, oraEnable_out; //enable LFSR(pattern generator), enable signal flow control, enable output response analyser
	sc_signal<sc_bv<2>> testReport_out;

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
	
	return 0;
}