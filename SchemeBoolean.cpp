#include "SchemeBoolean.h"
#include <iostream>

SchemeBoolean::SchemeBoolean(bool v): boolean(v){}

string SchemeBoolean::value() const {
	return boolean ? "#t" : "#f";
}

bool SchemeBoolean::getBoolean() {
	return boolean;
}
