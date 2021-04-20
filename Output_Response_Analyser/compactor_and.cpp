#include"compactor_and.h"

void compactor_nand::compact() {
	
	toCompact_temp = toCompact_in.read();
	compacted_temp = 1;
	
	for (int i = 0; i < 29; i++) {
		compacted_temp[0] &= (toCompact_temp[i] & toCompact_temp[i + 1]);
	}
	
	if (compacted_temp[0] == 1) {
		compacted_out.write(1);
	}
	else if(compacted_temp[0] == 0)
	{
		compacted_out.write(0);
	}
	
}