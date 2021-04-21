#include"misr.h"

int sc_main(int argc, char* argv[]) {
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> oraEnable_in, mac_data_ready_in, testEnded_in;
	sc_signal<sc_bv<32>> o_data_in;
	sc_signal<bool> oraFinished_out;
	sc_signal<sc_bv<2>> oraStatus_out;
	sc_signal<sc_bv<64>> output1;

	misr misr("MISR");

	misr.clk(clk);
	misr.oraEnable_in(oraEnable_in);
	misr.mac_data_ready_in(mac_data_ready_in);
	//misr.testEnded_in(testEnded_in);
	misr.o_data_in(o_data_in);
	misr.oraFinished_out(oraFinished_out);
	misr.oraStatus_out(oraStatus_out);
	misr.output1(output1);


	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("misr");
	//signals to trace
	sc_trace(wf, clk, "clock");
	sc_trace(wf, oraEnable_in, "oraEnable_in");
	sc_trace(wf, mac_data_ready_in, "mac_data_ready_in");
	sc_trace(wf, testEnded_in, "testEnded_in");
	sc_trace(wf, o_data_in, "o_data_in");
	sc_trace(wf, oraFinished_out, "oraFinished_out");
	sc_trace(wf, oraStatus_out, "oraStatus_out");
	sc_trace(wf, output1, "output1");

	oraEnable_in = 0;
	mac_data_ready_in = 0;
	o_data_in = 0b11000100001110100100000000000001;
	oraFinished_out = 0;
	oraStatus_out = 0;
	output1 = 0;

	sc_start(0, SC_NS);
	sc_start(1, SC_NS);
	oraEnable_in = 1;
	sc_start(1, SC_NS);
	mac_data_ready_in = 1;
	sc_start(1, SC_NS);
	mac_data_ready_in = 0;
	sc_start(37, SC_NS);
	
	//exit sim
	sc_stop();

	std::cout << "exiting simulation" << std::endl;

	sc_close_vcd_trace_file(wf);

	int a;
	std::cin >> a;
	return 0;
}