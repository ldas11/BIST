#include"comparator.h"

void comparator::compare() {
	if (enable.read() == 1) {
		
		if (mac_data_ready_in.read() == 1) {
			mac_data.nb_write(mac_data_in.read());
		}

		ref_data.nb_write(ref_data_in.read());
		ref_data_b.nb_write(ref_data_b_in.read());

		if (mac_data.num_available() && ref_data.num_available()) {
			 mac_data.nb_read(mac_data_local);
			 ref_data.nb_read(ref_data_local);
			 ref_data_b.nb_read(ref_data_b_local);

			comp_res_rest = 0;
			comp_res_sign = 0;

			for (int i = 0; i < 31; i++) {
				comp_res_rest[i] = ~(mac_data_local[i] ^ ref_data_local[i]);
			}

			ref_data_local[31] = ref_data_local[31] ^ ref_data_b_local[0];
			comp_res_sign[0] = ~(mac_data_local[31] ^ ref_data_local[31]);

			//comp_res = ~(mac_data_local ^ ref_data_local);
			result_rest_out.write(comp_res_rest);
			
			if (comp_res_sign[0] == 0b0) {
				result_sign_out.write(0);
			}
			else if (comp_res_sign[0] == 0b1) {
				result_sign_out.write(1);
			}
			comp_ready_out.write(1);
		}
		else {
			comp_ready_out.write(0);
		}
	}
}