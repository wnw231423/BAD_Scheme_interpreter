/**
* InputReader Part.
* 
* InputReader is to give the user input to buffer. If the input cross multiple lines,
* every time user input one line, the scheme_reader(lexical analysis part) will ask 
* the buffer for more lines and the buffer will call getInput to let user input more.
*/

#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class InputReader {
private:
	string prompt;
	istream& in;
	bool show_prompt;
public:
	InputReader(string prompt, istream& in = cin, bool show_prompt = true);
	vector<string> getInput();
	~InputReader() = default;
};
#endif // !INPUTREADER_H
