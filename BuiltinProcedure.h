#ifndef BUILTINPROCEDURE_H
#define BUILTINPROCEDURE_H

#include "Procedure.h"
#include <string>
#include "SchemeBuiltin.h"
#include "Frame.h"
#include "SchemeObj.h"
using namespace std;

class BuiltinProcedure:public Procedure{
public:
	string value() const;
	BuiltinProcedure(BuiltinFunction* fn, bool use_env = false, string name = "builtin");
	SchemeObj* apply (SchemeObj* args, Frame* env);
private:
	string name;
	BuiltinFunction* fn;
	bool use_env;
};

#endif // !BUILTINPROCEDURE_H

