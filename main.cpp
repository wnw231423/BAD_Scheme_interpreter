#include "Buffer.h"
#include "SchemeReader.h"
#include <iostream>
#include <sstream>
#include "Scheme.h"

int main() {
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