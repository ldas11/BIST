#include"bist_controller.h"
#include"compactor_and.h"
#include"comparator.h"
#include"lfsr_32bit.h"
#include"mult_acc.h"
#include"mux21_b.h"
#include"mux21_bv_32.h"
#include"ora_control_comp.h"
#include"shift_reg.h"

int sc_main(int argc, char* argv[]) {
	sc_clock clk("clk", 1, SC_NS);
	sc_signal<bool> enable;

	bist_controller main_control("CTRL");
	compactor_nand compactor("CMPCTR");
	comparator comparator("CMPRTR");
	mult_acc mac("MAC");
	mux21_b mux_b("MUXB");
	mux21_bv_32 muX_bv("MUXBV");
	ora_control_comp ora_ctrl("ORACTRL");
	shift_reg shifter("TPG");


	
	return 0;
}