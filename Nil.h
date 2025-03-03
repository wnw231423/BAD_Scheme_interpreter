#ifndef NIL_H
#define NIL_H
#include <string>
#include "SchemeObj.h"
using namespace std;

class Nil:public SchemeObj{
public:
	string value() const;
	friend ostream& operator<<(ostream& o, const Nil& n);
};

extern Nil nil; // Only one instance of nil.

#endif