#ifndef SCHEMEPAIR_H
#define SCHEMEPAIR_H
#include <string>
#include "Nil.h"
#include "SchemeSymbol.h"
using namespace std;

class SchemePair:public SchemeObj {
public:
	SchemePair();
	SchemePair(SchemeObj* first, SchemeObj* rest);
	string value() const;
	friend ostream& operator<< (ostream& o, const SchemePair& sp);
	int len();
	SchemeObj* getFirst();
	SchemeObj* getRest();
	void setFirst(SchemeObj* first);
	void setRest(SchemePair* rest);
	void setRest(Nil& nil);
	//TODO: SchemePair map(void (*funcptr));
private:
	SchemeObj *first;
	SchemeObj *rest;
};

#endif // !_SCHEMEPAIR_H
