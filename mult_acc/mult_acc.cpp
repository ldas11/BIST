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
            o_data_reg = float_to_bv(accumulation);
            std::cout << a_data_local << "*" << b_data_local << " = " << a_data_local * b_data_local << " will be added" << std::endl;
        }

        if (finish_acc.read()) {
            acc_reg.write(accumulation);
            o_data.write(o_data_reg);       //to use as input for the ORAs
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

//convert floats to uint, can then be stored as bit vector
sc_bv<32> mult_acc::float_to_bv(float value) {
    sc_dt::scfx_ieee_float float_number(value);
    bool sgn = float_number.negative();
    sc_int<8> exp= float_number.exponent();   //exponent() delivers the exponent without bias
    exp += 127;                     //add bias to meet IEEE 754 standard
    /**
    for (int i = 7; i >= 0; i--) {   //this reverses the bit order 
        exp |= (exp_temp & 1) << i;  //unnecessary! bits are in the correct order
        exp_temp >>= 1;
    }
    **/
    sc_uint<23> mnts = float_number.mantissa(); //delivers the correct mantissa
    sc_uint<32> converted_value = (sgn, exp, mnts); //concatenate
    return converted_value;
}