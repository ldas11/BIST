#include"comparator.h"

void comparator::compare() {
	if (enable.read() == 1) {


		mac_data_local = mac_data_in.read();
		ref_data_local = ref_data_in.read();
		ref_data_b_local = ref_data_b_in.read();

		comp_res_rest = 0;
		comp_res_sign = 0;

		for (int i = 0; i < 31; i++) {
			comp_res_rest[i] = ~(mac_data_local[i] ^ ref_data_local[i]);
		}

		ref_data_local[31] = ref_data_local[31] ^ ref_data_b_local[0];
		comp_res_sign[0] = ~(mac_data_local[31] ^ ref_data_local[31]);

		//comp_res = ~(mac_data_local ^ ref_data_local);
		result_rest_out.write(comp_res_rest);
		result_sign_out.write(comp_res_sign);
	}
}