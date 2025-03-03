#ifndef SCHEMEBOOLEAN_H
#define SCHEMEBOOLEAN_H

#include "SchemeObj.h"
#include <string>
using namespace std;

class SchemeBoolean : public SchemeObj {
private:
	bool boolean;
public:
	SchemeBoolean(bool v);
	string value() const;
	bool getBoolean();
};

#endif // !SCHEMEBOOLEAN_H

