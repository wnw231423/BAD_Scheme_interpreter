#ifndef SPECIALPROCEDURE_H
#define SPECIALPROCEDURE_H

#include "Procedure.h"
#include <string>
#include "SchemeBuiltin.h"
#include "Frame.h"
#include "SchemeObj.h"
using namespace std;

class SpecialProcedure :public Procedure {
public:
	string value() const;
	SpecialProcedure(SpecialForm* fn, bool use_env = false, string name = "builtin");
	SchemeObj* apply(SchemeObj* args, Frame* env);
private:
	string name;
	SpecialForm* fn;
	bool use_env;
};

#endif // !SPECIALPROCEDURE_H

