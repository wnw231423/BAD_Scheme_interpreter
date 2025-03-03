#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "SchemeObj.h"
#include "Frame.h"
/* The super class of all Scheme procudures. */
class Procedure:public SchemeObj{
public:
	virtual std::string value() const = 0;
	virtual SchemeObj* apply(SchemeObj* args, Frame* env) = 0;
};

#endif // !PROCEDURE_H
