#ifndef SCHEMESYMBOL_H
#define SCHEMESYMBOL_H
#include "SchemeObj.h"
#include <string>
#include <iostream>
using namespace std;

class SchemeSymbol : public SchemeObj {
private:
	string symbolName;
public:
	SchemeSymbol(string s);
	string value() const;
};
#endif // !SCHEMESYMBOL_H

