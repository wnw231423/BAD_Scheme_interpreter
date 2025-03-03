#ifndef SCHEMESTRING_H
#define SCHEMESTRING_H

#include "SchemeObj.h"
using namespace std;

class SchemeString :public SchemeObj {
public:
	SchemeString(string& s);
	string value() const;
private:
	string str;
};

#endif // !SCHEMESTRING_H

