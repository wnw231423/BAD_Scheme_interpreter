#include "BuiltinProcedure.h"
#include "SchemeBuiltin.h"
#include "Scheme.h"

string BuiltinProcedure::value() const {
	return "<BuiltinFunction: "+name+">";
}

BuiltinProcedure::BuiltinProcedure(BuiltinFunction* fn, bool use_env, string name) {
	this->name = name;
	this->fn = fn;
	this->use_env = use_env;
}

//Apply funciton. f->apply(args).
SchemeObj* BuiltinProcedure::apply (SchemeObj* args, Frame* env) {
	if (args == &nil) {
		return (*fn)(vector<SchemeObj*>{&nil});
	}

	vector<SchemeObj*> argsp;
	SchemePair* current = dynamic_cast<SchemePair*>(args);
	//Here we cut off the formal nil from scheme_read, for example, if we enter "(f 1 2)",
	//the arguments would be (1, (2, nil)), we should cut off the formal nil.
	while (current->getRest() != &nil) {
		argsp.push_back(scheme_eval(current->getFirst(), env));
		current = dynamic_cast<SchemePair*>(current->getRest());
	}
	argsp.push_back(scheme_eval(current->getFirst(), env));
	return (*fn)(argsp);
}
