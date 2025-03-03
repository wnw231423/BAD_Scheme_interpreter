#include "SpecialProcedure.h"
#include "SchemeBuiltin.h"
#include "Scheme.h"

string SpecialProcedure::value() const {
	return "<SpecialForm: " + name + ">";
}

SpecialProcedure::SpecialProcedure(SpecialForm* fn, bool use_env, string name) {
	this->name = name;
	this->fn = fn;
	this->use_env = use_env;
}

SchemeObj* SpecialProcedure::apply(SchemeObj* args, Frame* env) {
	if (args == &nil) {
		return (*fn)(vector<SchemeObj*>{&nil}, env);
	}

	vector<SchemeObj*> argsp;
	SchemePair* current = dynamic_cast<SchemePair*>(args);
	while (current->getRest() != &nil) {
		// Unlike builtin procedure, we don't evaluate the args.
		argsp.push_back(current->getFirst());
		current = dynamic_cast<SchemePair*>(current->getRest());
	}
	argsp.push_back(current->getFirst());
	return (*fn)(argsp, env);
}
