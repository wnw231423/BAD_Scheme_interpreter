#include "InputReader.h"
#include "Tokenizer.h"
#include <sstream>

InputReader::InputReader(string prompt, istream& in, bool show_prompt):prompt(prompt), in(in), show_prompt(show_prompt) {}

vector<string> InputReader::getInput() {
	string input = "";
	if (show_prompt) {
		cout << prompt;
	}
	while (getline(in, input)) {
		prompt = string(prompt.size(), ' ');
		return tokenize_line(input);
	}
	return { "exit" };
	
	/*Abandoned implements
	vector<string> res;
	string input;
	cout << prompt;
	getline(cin, input);
	res.push_back(input);
	prompt = ' ' + prompt;
	return res;
	*/
}
