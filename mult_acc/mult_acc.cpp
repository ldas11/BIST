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
            o_data.write(accumulation);
            //accumulation = 0;
        }

    }
    else {
        accumulation = 0;
        a_data_local = 0;
        b_data_local = 0;
        o_data.write(accumulation);
    }
}