#include "Nil.h"
#include <iostream>

string Nil::value() const{
	return "nil";
}

ostream& operator<<(ostream& o, const Nil& n) {
	o << "nil";
	return o;
}

Nil nil;
