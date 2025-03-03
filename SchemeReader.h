// SchemeReader -- for lexical analysis

#ifndef SCHEMEREADER_H
#define SCHEMEREADER_H

#include "SchemePair.h"
#include "Buffer.h"

/**
* schemeRead parse one block of input and turn it into schemePairs, which
* is the only data structure in scheme and is used to build a expression tree.
* 
* For example:
* user input tokens: "(", "define", "a", "(", "+", "1", "2", ")".
* should return pair("define", pair("a", pair("+", pair("1", pair("2", nil))))).
* Notice that the pair above is schemePair but not pair in C++.
*/
SchemeObj* schemeRead(Buffer& src);

/**
* Everytime a left bracket "(" is read, readTail is called to read the input within
* this pair of bracket and return the result as schemepair.
*/
SchemeObj* readTail(Buffer& src);

//Offers one buffer with specific input (default cin) for schemeReader to use it.
Buffer* bufferInput(string prompt = "scm> ", istream& in = cin, bool show_prompt = true);

// read input -> print what reader has read loop. Only for test.
void read_print_loop();
#endif // !SCHEMEREADER_H
