#include "SchemeObj.h"

std::ostream& operator<<(std::ostream& os, const SchemeObj& obj) {
	os << obj.value();
	return os;
}