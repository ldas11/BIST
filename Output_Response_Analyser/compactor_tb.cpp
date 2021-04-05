#include"compactor_and.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<iostream>

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_bv<31>> toCompact;
	sc_signal<bool> compacted;
	sc_signal<int> random_pos;

	compactor_nand compactor("compactor");

	compactor.toCompact(toCompact);
	compactor.compacted(compacted);

	//create vcd file to visualize the simulation
	sc_trace_file* wf = sc_create_vcd_trace_file("compactor");
	//signals to trace
	sc_trace(wf, toCompact, "toCompact");
	sc_trace(wf, compacted, "compacted");
	sc_trace(wf, random_pos, "random_pos");


	srand(time(NULL));

	toCompact = 0;
	compacted = 0;
	random_pos = 0;
	int random = 0;
	unsigned int value = 0b1111111111111111111111111111111;

	sc_start(0, SC_NS);
	std::cout << "starting simulation" << std::endl;

	//sc_start(1, SC_NS);
	for (int i = 0; i < 10; i++) {
		toCompact = 0b1111111111111111111111111111111;
		sc_start(1, SC_NS);
		random = rand() % 31;
		random_pos = random;
		value &= ~(0b1 << random);
		toCompact = value;
		sc_start(1, SC_NS);
	}

	sc_stop();

	std::cout << "exiting simulation" << std::endl;

	sc_close_vcd_trace_file(wf);

	int a;
	std::cin >> a;

	return 0;
}