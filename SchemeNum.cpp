#include "SchemeNum.h"
#include <iostream>
#include <sstream>
using namespace std;

SchemeNum::SchemeNum(string& v) {
	if (v[1] == 'i') {
		isFloat = false;
	}
	else if (v[1] == 'f') {
		isFloat = true;
	}
	float x;
	istringstream iss(v.substr(2, v.size() - 2));
	iss >> x;
	num = x;
}

SchemeNum::SchemeNum(float x, bool isFloat) {
	this->isFloat = isFloat;
	num = x;
}

string SchemeNum::value() const {
	ostringstream o;
	o << num;
	return o.str();
}

float SchemeNum::getNum() {
	return num;
}

bool SchemeNum::isF() {
	return isFloat;
}
