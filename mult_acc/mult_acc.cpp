#include"mult_acc.h"
#include<iostream>

void mult_acc::process() {
	if (reset.read() == 0) {
        if (a_valid.read())
            a_fifo.nb_write(a_data.read());

        if (b_valid.read())
            b_fifo.nb_write(b_data.read());

        if (a_fifo.num_available() && b_fifo.num_available()) {
            a_fifo.nb_read(a_data_local);
            b_fifo.nb_read(b_data_local);
            accumulation += a_data_local * b_data_local;
            std::cout << a_data_local << "*" << b_data_local << " = " << a_data_local * b_data_local << " will be added" << std::endl;
        }

        if (finish_acc.read()) {
            acc_reg.write(accumulation);
            o_data_reg = float_to_sc_uint(accumulation);
            o_data.write(o_data_reg);
            //accumulation = 0;
        }

    }
    else {
        accumulation = 0;
        o_data_reg = 0;
        a_data_local = 0;
        b_data_local = 0;
        acc_reg.write(accumulation);
        o_data.write(o_data_reg);
    }
}

sc_bv<32> mult_acc::float_to_sc_uint(float value) {
    sc_dt::scfx_ieee_float id(value);
    bool sgn = id.negative();
    sc_uint<8> exp_temp= id.exponent(); //exponent() delivers the esxponent bits in reverse order
    sc_uint<8> exp = 0; 
    for (int i = 7; i >= 0; i--) {      //this loop places the exponent bits in the correct order 
        exp |= exp_temp << i;
        exp_temp >>= 1;
    }
    sc_uint<23> mnts = id.mantissa();
    sc_uint<32> converted_value = (sgn, exp, mnts);
    return converted_value;
}