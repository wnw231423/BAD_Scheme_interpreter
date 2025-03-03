#include "LambdaProcedure.h"
#include "SchemeBuiltin.h"
#include "sstream"
#include "Scheme.h"

LambdaProcedure::LambdaProcedure(SchemeObj* formals, vector<SchemeObj*>& body, Frame* env) {
	if (SchemePair* fp = dynamic_cast<SchemePair*>(formals)) {
		this->formals = fp;
		this->body = body;
		this->env = env;
	}
	else {
		throw runtime_error("LambdaProcedure error."); // Should not occur.
	}
}

Frame* LambdaProcedure::make_call_frame(SchemeObj* args) {
	Frame* res = env->makeChildFrame(formals, args);
	return res;
}

string LambdaProcedure::value() const {
	ostringstream oss;
	oss << "<Lambda function>" << endl;
	oss << "Formals: " << *formals << endl;
	return oss.str();
}

SchemeObj* LambdaProcedure::apply(SchemeObj* args, Frame* env) {
	this->env->merge(env);
	Frame* child = make_call_frame(args); //why this line gets wrong when this method is const
	return eval_all(body, child);
}
