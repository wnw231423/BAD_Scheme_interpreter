/**
* Buffer Part:
* 
* A Buffer provides a way of accessing a sequence of tokens across lines.
*
* Its constructor takes an inputReader, called "the source", that returns the
* next line of tokens as a list each time it is queried, or None to indicate
* the end of input.
*
* The Buffer in effect concatenates the sequences returned from its source
* and then supplies the items from them one at a time through its pop_first()
* method, calling the source for more sequences of items only when needed.
*
* In addition, Buffer provides a current method to look at the
* next item to be supplied, without sequencing past it.
*/

#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>
#include <iterator>
#include <list>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "InputReader.h"
using namespace std;

class Buffer {
public:
	Buffer(InputReader* input);
	string popFirst();  // Pop the first token from input.
	string current();   // Get the first token from input.
	string to_string() const;
	const bool moreOnLine();  // Check if a line of input has been going through or not.

private:
	InputReader* input;
	int index;
	vector<string> currentLine;
	void loadNextLine(); // Get next line of input from input.
};

// Print out the current state of a buffer. Only for test.
void bufferTest();

#endif
