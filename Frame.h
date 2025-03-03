// An environment frame binds Scheme symbols to Scheme values.
#ifndef FRAME_H
#define FRAME_H

#include <string>
#include "SchemeObj.h"
#include "SchemeSymbol.h"
#include "SchemePair.h"
#include <unordered_map>
using namespace std;

class Frame {
public:
	Frame(Frame* parent);
	string value();
	void define(string& s, SchemeObj* v);  // bind symbol "s" to Scheme value v.
	SchemeObj* lookup(SchemeSymbol* s);    // look up one symbol to find its value.
	Frame* makeChildFrame(SchemeObj* formals, SchemeObj* vals);
	unordered_map<string, SchemeObj*> getBindings();
	void merge(Frame* f);
private:
	Frame* parent;
	unordered_map<string, SchemeObj*> bindings;
	void doBindings(SchemeObj* formals, SchemeObj* vals);
};

#endif // !FRAME_H
