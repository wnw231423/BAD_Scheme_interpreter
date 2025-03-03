#include "SchemePair.h"
#include <iostream>
#include <sstream>

SchemePair::SchemePair(SchemeObj* first, SchemeObj* rest) {
	this->first = first;
	this->rest = rest;
}

string SchemePair::value() const{
	ostringstream oss;
	oss << "(" << first->value() << ", " << rest->value() << ')';
	return oss.str();
}

ostream& operator<<(ostream& o, const SchemePair& sp) {
	o << '(' << sp.first->value() << ", " << sp.rest->value() << ')';
	return o;
}

int SchemePair::len() {
	int res = 1;
	SchemePair* p = this;
	while (SchemePair* pp = dynamic_cast<SchemePair*> (p->rest)) {
		res += 1;
		p = pp;
	}
	return res;
}

SchemeObj* SchemePair::getFirst() {
	return first;
}

SchemeObj* SchemePair::getRest() {
	return rest;
}

void SchemePair::setFirst(SchemeObj* first) {
	this->first = first;
}

void SchemePair::setRest(SchemePair* rest) {
	this->rest = rest;
}

void SchemePair::setRest(Nil& nil) {
	this->rest = &nil;
}
