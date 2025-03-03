// To run test method from buffer, schemeReader
#include "Buffer.h"
#include "SchemeReader.h"
#include <iostream>
#include <sstream>
#include "Scheme.h"

void do_buffer_test() {
    bufferTest();
}

void do_reader_test() {
    read_print_loop();
}

void do_scheme_test() {
    Frame* global = create_global_frame();
    int t = 0;
    while (t == 0) {
        try {
            t = read_eval_print_loop(global);
        }
        catch (runtime_error e) {
            cout << e.what() << endl;
        }
    }
}
