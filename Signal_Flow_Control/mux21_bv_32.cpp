#include"mux21_bv_32.h"
#include<iostream>

void mux21_bv_32::chooseOutput() {
	if (sfcEnable_in.read() == 0) {
		//mux_bv_out.write(normal_bv_in);	//normal operation
		mux_f_out.write(bv_to_float(normal_bv_in.read()));
		std::cout << "normal operation" << std::endl;
	}
	else if (sfcEnable_in == 1) {
		//mux_bv_out.write(bist_bv_in.read());		//bist mode, isolating the array inputs 
		mux_f_out.write(bv_to_float(bist_bv_in.read()));
		std::cout << "bist mode" << std::endl;
	}
}

float mux21_bv_32::bv_to_float(sc_bv<32> bit_vector) {
	unsigned int sign = (bit_vector.range(31,31)).to_uint();
	int exp = (bit_vector.range(30,23)).to_int() - 127;
	unsigned int mant = (bit_vector.range(22, 0)).to_uint();
	sc_dt::scfx_ieee_float bv_value;
	bv_value.negative(sign);
	bv_value.exponent(exp);
	bv_value.mantissa(mant);

	float result = bv_value;

	return result;
}