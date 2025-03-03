#ifndef SCHEMENUM_H
#define SCHEMENUM_H
#include "SchemeObj.h"

class SchemeNum: public SchemeObj{
private:
	float num;
	bool isFloat;

public:
	SchemeNum(std::string& v);
	SchemeNum(float x, bool isFloat);
	std::string value() const;
	float getNum();
	bool isF();
};

#endif
