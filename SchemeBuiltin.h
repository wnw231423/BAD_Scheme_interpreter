#ifndef SCHEMEBUILTIN_H
#define SCHEMEBUILTIN_H

#include "SchemeObj.h"
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>
#include "Frame.h"

using namespace std;

/*** Builtin Part ***/
using BuiltinFunction = function<SchemeObj* (const vector<SchemeObj*>&)>;
extern unordered_map<string, BuiltinFunction> builtin;

class BuiltinRegistrar {
public:
	BuiltinRegistrar(const string& name, BuiltinFunction func);
};

SchemeObj* scheme_add(const vector<SchemeObj*>& args);
SchemeObj* scheme_sub(const vector<SchemeObj*>& args);
SchemeObj* scheme_mul(const vector<SchemeObj*>& args);
SchemeObj* scheme_div(const vector<SchemeObj*>& args);
SchemeObj* scheme_more(const vector<SchemeObj*>& args);
SchemeObj* scheme_less(const vector<SchemeObj*>& args);
SchemeObj* scheme_moreeq(const vector<SchemeObj*>& args);
SchemeObj* scheme_lesseq(const vector<SchemeObj*>& args);
SchemeObj* is_boolean(const vector<SchemeObj*>& args);
SchemePair* cons(const vector<SchemeObj*>& args);
SchemeObj* car(const vector<SchemeObj*>& args);
SchemeObj* cdr(const vector<SchemeObj*>& args);
SchemeObj* eq(const vector<SchemeObj*>& args);

/*** Special forms Part ***/
using SpecialForm = function<SchemeObj* (const vector<SchemeObj*>&, Frame* env)>;
extern unordered_map<string, SpecialForm> special_forms;

class SpecialRegistrar {
public:
	SpecialRegistrar(const string& name, SpecialForm func);
};

SchemeObj* do_and_form(const vector<SchemeObj*>& args, Frame* env = nullptr);
SchemeObj* do_or_form(const vector<SchemeObj*>& args, Frame* env = nullptr);
SchemeObj* do_not_form(const vector<SchemeObj*>& args, Frame* env = nullptr);
SchemeObj* do_lambda_form(const vector<SchemeObj*>& args, Frame* env);
SchemeObj* do_define_form(const vector<SchemeObj*>& args, Frame* env);
SchemeObj* do_if_form(const vector<SchemeObj*>& args, Frame* env);
SchemeObj* do_quote_form(const vector<SchemeObj*>& args, Frame* env);
SchemeObj* do_begin_form(const vector<SchemeObj*>& args, Frame* env);
SchemeObj* do_display_form(const vector<SchemeObj*>& args, Frame* env);
SchemeObj* do_load_form(const vector<SchemeObj*>& args, Frame* env);

/*** Other useful functions ***/
bool is_false(SchemeObj* x);
bool is_true(SchemeObj* x);
vector<SchemeObj*> pair_to_vector(SchemeObj*);

#endif // !SCHEMEBUILTIN_H
