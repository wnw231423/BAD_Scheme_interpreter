#include "SchemeBuiltin.h"
#include "SchemeNum.h"
#include "SchemeString.h"
#include "SchemeBoolean.h"
#include "SchemeSymbol.h"
#include "Procedure.h"
#include "LambdaProcedure.h"
#include <sstream>
#include <typeinfo>
#include "Scheme.h"

unordered_map<string, BuiltinFunction> builtin;
unordered_map<string, SpecialForm> special_forms;

BuiltinRegistrar::BuiltinRegistrar(const string& name, BuiltinFunction func) {
	builtin[name] = func;
}

SchemeObj* scheme_add(const vector<SchemeObj*>& args) {
	float res = 0;
	bool isFloat = false;
	for (auto arg : args) {
		if (SchemeNum* p = dynamic_cast<SchemeNum*> (arg)) {
			res += p->getNum();
			if (p->isF()) {
				isFloat = true;
			}
		}
		else {
			throw runtime_error("Incorrect type of arguments.");
		}
	}
	SchemeNum* resp = new SchemeNum(res, isFloat);
	return resp;
}
static BuiltinRegistrar add_reistrar("+", scheme_add);

SchemeObj* scheme_sub(const vector<SchemeObj*>& args) {
	bool isFloat = false;
	auto argsp = args.begin();
	SchemeNum* p = nullptr;
	if (p = dynamic_cast<SchemeNum*>(*argsp)) {
		argsp += 1;
		float res = p->getNum();
		if (p->isF()) {
			isFloat = true;
		}
		if (argsp == args.end()) {
			res = 0 - res;
		}
		for (argsp; argsp != args.end(); argsp++) {
			if (p = dynamic_cast<SchemeNum*>(*argsp)) {
				res -= p->getNum();
				if (p->isF()) {
					isFloat = true;
				}
			}
			else {
				throw runtime_error("Incorrect type of arguments.");
			}
		}
		SchemeNum* resp = new SchemeNum(res, isFloat);
		return resp;
	}
	else {
		throw runtime_error("Incorrect type of arguments.");
	}
}
static BuiltinRegistrar sub_reistrar("-", scheme_sub);

SchemeObj* scheme_mul(const vector<SchemeObj*>& args) {
	float res = 1;
	bool isFloat = false;
	for (auto arg : args) {
		if (SchemeNum* p = dynamic_cast<SchemeNum*> (arg)) {
			res *= p->getNum();
			if (p->isF()) {
				isFloat = true;
			}
		}
		else {
			throw runtime_error("Incorrect type of arguments.");
		}
	}
	SchemeNum* resp = new SchemeNum(res, isFloat);
	return resp;
}
static BuiltinRegistrar mul_reistrar("*", scheme_mul);

SchemeObj* scheme_div(const vector<SchemeObj*>& args) {
	bool isFloat = true;  // Probably the result of div would be float.
	auto argsp = args.begin();
	SchemeNum* p = nullptr;
	if (p = dynamic_cast<SchemeNum*>(*argsp)) {
		argsp += 1;
		float res = p->getNum();
		if (p->isF()) {
			isFloat = true;
		}
		if (argsp == args.end()) {
			res = 1 / res;
		}
		for (argsp; argsp != args.end(); argsp++) {
			if (p = dynamic_cast<SchemeNum*>(*argsp)) {
				float temp = p->getNum();
				if (temp == 0) {
					throw runtime_error("Divided by 0 error.");
				}
				else {
					res /= temp;
				}
			}
			else {
				throw runtime_error("Incorrect type of arguments.");
			}
		}
		SchemeNum* resp = new SchemeNum(res, isFloat);
		return resp;
	}
	else {
		throw runtime_error("Incorrect type of arguments.");
	}
}
static BuiltinRegistrar div_reistrar("/", scheme_div);

SchemeObj* scheme_more(const vector<SchemeObj*>& args) {
	if (args.size() != 2) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemeNum* first = dynamic_cast<SchemeNum*>(args[0])) {
			if (SchemeNum* second = dynamic_cast<SchemeNum*>(args[1])) {
				bool more = (first->getNum()) > (second->getNum());
				SchemeBoolean* res = new SchemeBoolean(more);
				return res;
			}
		}
		throw runtime_error("Incorrect type of arguments.");
	}
}
static BuiltinRegistrar more_registrar(">", scheme_more);

SchemeObj* scheme_less(const vector<SchemeObj*>& args) {
	if (args.size() != 2) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemeNum* first = dynamic_cast<SchemeNum*>(args[0])) {
			if (SchemeNum* second = dynamic_cast<SchemeNum*>(args[1])) {
				bool more = (first->getNum()) < (second->getNum());
				SchemeBoolean* res = new SchemeBoolean(more);
				return res;
			}
		}
		throw runtime_error("Incorrect type of arguments.");
	}
}
static BuiltinRegistrar less_registrar("<", scheme_less);

SchemeObj* scheme_moreeq(const vector<SchemeObj*>& args) {
	if (args.size() != 2) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemeNum* first = dynamic_cast<SchemeNum*>(args[0])) {
			if (SchemeNum* second = dynamic_cast<SchemeNum*>(args[1])) {
				bool more = (first->getNum()) >= (second->getNum());
				SchemeBoolean* res = new SchemeBoolean(more);
				return res;
			}
		}
		throw runtime_error("Incorrect type of arguments.");
	}
}
static BuiltinRegistrar moreeq_registrar(">=", scheme_moreeq);

SchemeObj* scheme_lesseq(const vector<SchemeObj*>& args) {
	if (args.size() != 2) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemeNum* first = dynamic_cast<SchemeNum*>(args[0])) {
			if (SchemeNum* second = dynamic_cast<SchemeNum*>(args[1])) {
				bool more = (first->getNum()) <= (second->getNum());
				SchemeBoolean* res = new SchemeBoolean(more);
				return res;
			}
		}
		throw runtime_error("Incorrect type of arguments.");
	}
}
static BuiltinRegistrar lesseq_registrar("<=", scheme_lesseq);

SchemeObj* is_boolean(const vector<SchemeObj*>& args) {
	if (SchemeBoolean* p = dynamic_cast<SchemeBoolean*>(args[0])) {
		SchemeBoolean* res = new SchemeBoolean(true);
		return res;
	}
	else {
		SchemeBoolean* res = new SchemeBoolean(false);
		return res;
	}
}
static BuiltinRegistrar is_boolean_registrar("boolean?", is_boolean);

SchemePair* cons(const vector<SchemeObj*>& args) {
	if (args.size() != 2) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemePair* p = dynamic_cast<SchemePair*> (args[1])) {
			SchemePair* res = new SchemePair(args[0], p);
			return res;
		}
		else if (args[1] == &nil) {
			SchemePair* res = new SchemePair(args[0], args[1]);
			return res;
		}
		else {
			throw runtime_error("Rest can be only nil or a pair.");
		}
	}
}
static BuiltinRegistrar cons_registrar("cons", cons);

SchemeObj* car(const vector<SchemeObj*>& args) {
	if (args.size() != 1) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else if (SchemePair* p = dynamic_cast<SchemePair*> (args[0])) {
		return p->getFirst();
	}
	else {
		throw runtime_error("Incorrect type of argument.");
	}
}
static BuiltinRegistrar car_registrar("car", car);

SchemeObj* cdr(const vector<SchemeObj*>& args) {
	if (args.size() != 1) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else if (SchemePair* p = dynamic_cast<SchemePair*> (args[0])) {
		return p->getRest();
	}
	else {
		throw runtime_error("Incorrect type of argument.");
	}
}
static BuiltinRegistrar cdr_registrar("cdr", cdr);

SchemeObj* eq(const vector<SchemeObj*>& args) {
	if (args.size() != 2) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (args[0]->value() == args[1]->value()) {
			SchemeBoolean* res = new SchemeBoolean(true);
			return res;
		}
		else {
			SchemeBoolean* res = new SchemeBoolean(false);
			return res;
		}
	}
}
static BuiltinRegistrar eq_registrar("equal?", eq);

/**************************/
/*** Special Forms Part ***/
/**************************/
SpecialRegistrar::SpecialRegistrar(const string& name, SpecialForm func) {
	special_forms[name] = func;
}

/* In scheme, everything is true except false. */
SchemeObj* do_and_form(const vector<SchemeObj*>& args, Frame* env) {
	for (SchemeObj* p : args) {
		p = scheme_eval(p, env);
		if (p->value() == "#f") {
			SchemeBoolean* res = new SchemeBoolean(false);
			return res;
		}
	}
	SchemeBoolean* res = new SchemeBoolean(true);
	return res;
}
static SpecialRegistrar and_registrar("and", do_and_form);

SchemeObj* do_or_form(const vector<SchemeObj*>& args, Frame* env) {
	for (SchemeObj* p : args) {
		p = scheme_eval(p, env);
		if (p->value() != "#f") {
			SchemeBoolean* res = new SchemeBoolean(true);
			return res;
		}
	}
	SchemeBoolean* res = new SchemeBoolean(false);
	return res;
}
static SpecialRegistrar or_registrar("or", do_or_form);

SchemeObj* do_not_form(const vector<SchemeObj*>& args, Frame* env) {
	if (args.size() != 1) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemeBoolean* a = dynamic_cast<SchemeBoolean*> (scheme_eval(args[0], env))) {
			if (is_true(a)) {
				SchemeBoolean* res = new SchemeBoolean(false);
				return res;
			}
			else {
				SchemeBoolean* res = new SchemeBoolean(true);
				return res;
			}
		}
		else {
			throw runtime_error("Incorrect type of argument.");
		}
	}
}
static SpecialRegistrar not_registrar("not", do_not_form);

SchemeObj* do_lambda_form(const vector<SchemeObj*>& args, Frame* env) {
	SchemeObj* formals = args[0];
	vector<SchemeObj*> body = vector<SchemeObj*>(args.begin()+1, args.end());
	LambdaProcedure* res = new LambdaProcedure(formals, body, env);
	return res;
}
static SpecialRegistrar lambda_registrar("lambda", do_lambda_form);

SchemeObj* do_define_form(const vector<SchemeObj*>& args, Frame* env) {
	SchemeObj* first = args[0];

	if (SchemeSymbol* fsp = dynamic_cast<SchemeSymbol*>(first)) {
		if (args.size() != 2) {
			ostringstream oss;
			oss << "'define' a variable need only one value but more are found.";
			throw runtime_error(oss.str());
		}
		else {
			SchemeObj* v = args[1];
			v = scheme_eval(v, env);
			string name = fsp->value();
			env->define(name, v);
			return fsp;
		}
	}
	else if (SchemePair* fp = dynamic_cast<SchemePair*>(first)) {
		if (SchemeSymbol* namep = dynamic_cast<SchemeSymbol*>(fp->getFirst())) {
			string name = namep->value();
			SchemeObj* formals = fp->getRest();
			vector<SchemeObj*> body = vector<SchemeObj*>(args.begin() + 1, args.end());
			LambdaProcedure* res = new LambdaProcedure(formals, body, env);
			env->define(name, res);
			return namep;
		}
		else {
			throw runtime_error("Invalid symbol.");
		}
	}
	else {
		throw runtime_error("define error.");
	}
}
static SpecialRegistrar define_registrar("define", do_define_form);

SchemeObj* do_if_form(const vector<SchemeObj*>& args, Frame* env) {
	if (args.size() <= 1) {
		throw runtime_error("Invalid if statement.");
	}
	else {
		SchemeObj* condition = scheme_eval(args[0], env);
		if (is_true(condition)) {
			return scheme_eval(args[1], env);
			
		}
		else {
			if (args.size() == 2) {
				return &nil;
			}
			else if (args.size() == 3){
				return scheme_eval(args[2], env);
				
			}
			else {
				throw runtime_error("Invalid if statement.");
			}
		}
	}
}
static SpecialRegistrar if_registrar("if", do_if_form);

SchemeObj* do_quote_form(const vector<SchemeObj*>& args, Frame* env) {
	if (args.size() != 1) {
		throw runtime_error("error occurs during do_quote_form");  //Should never happen.
	}
	else {
		return args[0];
	}
}
static SpecialRegistrar quote_registrar("quote", do_quote_form);

SchemeObj* do_begin_form(const vector<SchemeObj*>& args, Frame* env) {
	vector<SchemeObj*> block(args);
	SchemeObj* res = eval_all(block, env);
	return res;
}
static SpecialRegistrar begin_registrar("begin", do_begin_form);

SchemeObj* do_display_form(const vector<SchemeObj*>& args, Frame* env) {
	if (args.size() != 1) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		SchemeObj* res = scheme_eval(args[0], env);
		cout << *res;
	}
	return nullptr;
}
static SpecialRegistrar disp_registrar("display", do_display_form);

SchemeObj* do_load_form(const vector<SchemeObj*>& args, Frame* env) {
	if (args.size() != 1) {
		throw runtime_error("Incorrect number of arguments.");
	}
	else {
		if (SchemeString* s = dynamic_cast<SchemeString*> (scheme_eval(args[0], env))) {
			string fileName = s->value();
			Frame* e = create_global_frame();
			read_eval_print_loop(e, false, fileName);
			return nullptr;
		}
		else {
			throw runtime_error("Incorrect type of argument.");
		}
	}
}
static SpecialRegistrar load_registrar("load", do_load_form);

bool is_false(SchemeObj* x) {
	return x->value() == "#f";
}

bool is_true(SchemeObj* x) {
	return !is_false(x);
}

vector<SchemeObj*> pair_to_vector(SchemeObj* x) {
	vector<SchemeObj*> res = {};
	if (SchemePair* p = dynamic_cast<SchemePair*> (x)) {
		SchemePair* current = p;
		while (current->getRest() != &nil) {
			res.push_back(current->getFirst());
			current = dynamic_cast<SchemePair*>(current->getRest());
		}
		res.push_back(current->getFirst());
		return res;
	}
	else {
		res.push_back(x);
		return res;
	}
}
