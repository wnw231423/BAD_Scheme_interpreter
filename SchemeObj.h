#ifndef SCHEMEOBJ_H
#define SCHEMEOBJ_H
#include <string>
#include <iostream>

class SchemeObj {
	// Abstract top class for all the obj in Scheme.
public:
	virtual std::string value() const = 0;
	friend std::ostream& operator<<(std::ostream& os, const SchemeObj& obj);
};

#endif // !SCHEMEOBJ_H
