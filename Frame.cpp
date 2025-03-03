#include "Frame.h"
#include "sstream"
#include "Procedure.h"
#include "Scheme.h"

#include <iostream>

Frame::Frame(Frame* parent) {
	this->parent = parent;
}

string Frame::value() {
	if (parent == nullptr) {
		return "<Global Frame>";
	}
	else {
		ostringstream oss;
		oss << "<{";
		bool isFirst = true;
		for (auto p = bindings.begin(); p != bindings.end(); p++) {
			if (!isFirst) {
				oss << ", ";
			}
			oss << (p->first) << ": " << *(p->second);
		}
		oss << "} -> " << parent->value() << ">";
		return oss.str();
	}
}

void Frame::define(string& s, SchemeObj* v) {
	bindings[s] = v;
}

SchemeObj* Frame::lookup(SchemeSymbol* s) {
	string name = s->value();
	if (bindings.find(name) != bindings.end()) {
		return bindings[name];
	}
	else {
		if (parent != nullptr) {
			return parent->lookup(s);
		}
		else {
			throw runtime_error("Unknown identifier: " + name);
		}
	}
}

Frame* Frame::makeChildFrame(SchemeObj* formals, SchemeObj* vals) {
	Frame* res = new Frame(this);
	res -> doBindings(formals, vals);
	return res;
}

void Frame::doBindings(SchemeObj* formals, SchemeObj* vals) {
	if (formals == &nil) {
		if (vals != &nil) {
			throw runtime_error("Redundant argument.");
		}
		else {
			return;
		}
	}
	else if (SchemePair* fp = dynamic_cast<SchemePair*>(formals)) {
		if (SchemePair* vp = dynamic_cast<SchemePair*>(vals)) {
			if (fp->len() != vp->len()) {
				throw runtime_error("Incorrect arguments.");
			}
			else {
				if (SchemeSymbol* carp = dynamic_cast<SchemeSymbol*> (fp->getFirst()) ) {
					string n = carp->value();
					define(n, scheme_eval(vp->getFirst(), parent));
					doBindings(fp->getRest(), vp->getRest());
				}
				else {
					throw runtime_error("Function's formal argument should be symbol but value found.");
				}
			}
		} 
		else {
			throw runtime_error("Need arguments.");
		}
	}
	else {
		throw runtime_error("This error should never happen during <doBindings>.");
	}
}

unordered_map<string, SchemeObj*> Frame::getBindings() {
	return bindings;
}

void Frame::merge(Frame* f) {
	for (auto p : f->getBindings()) {
		this->bindings.insert(p);
	}
}
