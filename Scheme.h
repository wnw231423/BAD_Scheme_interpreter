// Scheme -- evaluating expressions.
#ifndef SCHEME_H
#define SCHEME_H

#include "Frame.h"
#include "SchemeObj.h"

// Evaluate one expression represented by schemepair.
SchemeObj* scheme_eval(SchemeObj* expr, Frame* env);

// Evaluate a sequence of expressions and return the value of last one.
SchemeObj* eval_all(vector<SchemeObj*>& expr, Frame* env);

Frame* create_global_frame();

// The interactive environment.
int read_eval_print_loop(Frame* env, bool interactive = true, string fileName = "");

/* Other useful function */
bool self_evaluating(SchemeObj* expr);

#endif // !SCHEME_H
