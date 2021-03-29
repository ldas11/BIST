#include"comparator.h"

void comparator::compare() {
	mac_data_local = mac_data.read();
	ref_data_local = ref_data.read();
	comp_res = 0;
	/**
	for (int i = 0; i < 32; i++) {
		comp_res[i] = ~(mac_data_local[i] ^ ref_data_local[i]);
	}
	**/
	comp_res = (mac_data_local ^ ref_data_local);
	result.write(comp_res);
}