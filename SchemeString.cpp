#include "SchemeString.h"

SchemeString::SchemeString(string& s) {
	str = s;
}

string SchemeString::value() const {
	return str;
}
