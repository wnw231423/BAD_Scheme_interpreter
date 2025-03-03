#ifndef LAMBDAPROCEDURE_H
#define LAMBDAPROCEDURE_H

#include "Procedure.h"

class LambdaProcedure : public Procedure {
public:
	LambdaProcedure(SchemeObj* formals, vector<SchemeObj*>& body, Frame* env);
	Frame* make_call_frame(SchemeObj* args);
	string value() const;
	SchemeObj* apply(SchemeObj* args, Frame* env) ;
private:
	SchemePair* formals;
	vector<SchemeObj*> body;
	Frame* env;
};

#endif // !LAMBDAPROCEDURE_H

