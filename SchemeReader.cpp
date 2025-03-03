#include "SchemeReader.h"
#include "Nil.h"
#include "ConstValues.h"
#include "SchemeSymbol.h"
#include "InputReader.h"
#include <string>
#include "SchemeBoolean.h"
#include "SchemeNum.h"
#include "Tokenizer.h"
#include "SchemeString.h"

SchemeObj* schemeRead(Buffer& src) {
	string val = src.popFirst();
	if (val.empty()) {
		throw runtime_error("Read beyond scope.");
	}
	else if (val == "nil") {
		return &nil;
	}
	else if (val == "(") {
		return readTail(src);
	}
	else if (val == "'") {
		SchemeSymbol* first = new SchemeSymbol("quote");
		SchemeObj* rest = new SchemePair(schemeRead(src), &nil);
		SchemePair* res = new SchemePair(first, rest);
		return res;
	}
	else if (DELIMITERS.find(val) == DELIMITERS.end()) {
		if (val == "true") {
			SchemeBoolean* res = new SchemeBoolean(true);
			return res;
		}
		else if (val == "false") {
			SchemeBoolean* res = new SchemeBoolean(false);
			return res;
		}
		else if (val[0] == '\"') {
			string s = val.substr(1, val.size() - 2);
			SchemeString* res = new SchemeString(s);
			return res;
		}
		else if (val[0] == '$') {
			SchemeNum* res = new SchemeNum(val);
			return res;
		}
		else {
			SchemeObj* res = new SchemeSymbol(val);
			return res;
		}
	}
	else {
		throw runtime_error("unexpected token: " + val);
	}
}

SchemeObj* readTail(Buffer& src) {
	if (src.current().empty()) {
		throw runtime_error("Unexpected end of file.");
	}
	else if (src.current() == ")") {
		src.popFirst();
		return &nil;
	}
	else {
		SchemeObj* first = schemeRead(src);
		SchemeObj* rest = readTail(src);
		SchemePair* res = new SchemePair(first, rest);
		return res;
	}
}

Buffer* bufferInput(string prompt, istream& in, bool show_prompt) {
	InputReader* lr = new InputReader(prompt, in, show_prompt);
	Buffer *res = new Buffer(lr);
	return res;
}

/*
Buffer* bufferLines(vector<string> lines, string prompt, bool showPrompt) {
	Buffer* res = nullptr;
	if (showPrompt) {
		vector<string> inputLines = lines;
		res = new Buffer(tokenize_lines(inputLines));
	}
	else {
		LineReader* lr = new LineReader(lines, prompt);
		vector<string> inputLines = { lr->next() };
		res = new Buffer(tokenize_lines(inputLines));
		delete lr;
	}
	return res;
}
*/

/*
SchemeObj* readLine(string line) {
	vector<string> input;
	input.push_back(line);
	Buffer buf = Buffer(tokenize_lines(input));
	SchemeObj* res = schemeRead(buf);
	if (buf.moreOnLine()) {
		throw runtime_error("readLine's argument can be conly a single element, but received multiple.");
	}
	return res;
}
*/

void read_print_loop() {
	while (Buffer* src = bufferInput("read> ")) {
		while (src->moreOnLine()) {
			SchemeObj* expression = schemeRead(*src);
			if (SchemeSymbol* p = dynamic_cast<SchemeSymbol*>(expression)) {
				if (p->value() == "exit") {
					delete p;
					return;
				}
			}
			cout << expression->value()<<endl;
			delete expression;
		}
	}
}
