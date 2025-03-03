#include "Scheme.h"
#include "Procedure.h"
#include "SchemeBuiltin.h"
#include "BuiltinProcedure.h"
#include "SpecialProcedure.h"
#include "Buffer.h"
#include "SchemeReader.h"
#include <fstream>

SchemeObj* scheme_eval(SchemeObj* expr, Frame* env) {
    if (SchemeSymbol* p = dynamic_cast<SchemeSymbol*>(expr)) {
        return env->lookup(p);
    }
    else if (self_evaluating(expr)) {
        return expr;
    }
    //Until here, only SchemePair remains.
    else {
        if (SchemePair* p = dynamic_cast<SchemePair*>(expr)) {
            SchemeObj* first = p->getFirst();
            SchemeObj* rest = p->getRest();
            first = scheme_eval(first, env);
            if (Procedure* p = dynamic_cast<Procedure*>(first)) {
                return p->apply(rest, env);
            }
            else {
                throw runtime_error(first->value()+" is not callable.");
            }
        }
        throw runtime_error("Error occurs during scheme_eval.");
    }
}

SchemeObj* eval_all(vector<SchemeObj*>& expr, Frame* env) {
    SchemeObj* res = nullptr;
    for (SchemeObj* e : expr) {
        res = scheme_eval(e, env);
    }
    return res;
}

Frame* create_global_frame() {
    Frame* res = new Frame(nullptr);
    for (auto p = builtin.begin(); p != builtin.end(); p++) {
        BuiltinProcedure* f = new BuiltinProcedure(&(p->second));
        string n = p->first;
        res->define(n, f);
    }
    for (auto p = special_forms.begin(); p != special_forms.end(); p++) {
        SpecialProcedure* f = new SpecialProcedure(&(p->second), true);
        string n = p->first;
        res->define(n, f);
    }
    return res;
}

int read_eval_print_loop(Frame* env, bool interactive, string fileName) {
    if (interactive) {
        while (Buffer* src = bufferInput()) {
            while (src->moreOnLine()) {
                SchemeObj* expression = schemeRead(*src);
                if (SchemeSymbol* p = dynamic_cast<SchemeSymbol*>(expression)) {
                    if (p->value() == "exit") {
                        delete p;
                        return 1;
                    }
                }
                SchemeObj* res = scheme_eval(expression, env);
                if (res != nullptr) {
                    cout << *res << endl;
                }
                else {
                    cout << endl;
                }
            }
        }
        return 1;
    }
    else {
        ifstream fin(fileName);
        while (Buffer* src = bufferInput("", fin, false)) {
            while (src->moreOnLine()) {
                SchemeObj* expression = schemeRead(*src);
                if (SchemeSymbol* p = dynamic_cast<SchemeSymbol*>(expression)) {
                    if (p->value() == "exit") {
                        delete p;
                        return 1;
                    }
                }
                scheme_eval(expression, env);
            }
        }
        cout << endl;
        return 1;
    }
}

bool self_evaluating(SchemeObj* expr) {
    if (SchemePair* p = dynamic_cast<SchemePair*>(expr)) {
        return false;
    }
    if (SchemeSymbol* p = dynamic_cast<SchemeSymbol*>(expr)) {
        return false;
    }
    return true;
}
