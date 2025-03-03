//Tokenlizer -- for lexical analysis

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
using namespace std;

/** 
* tokenize_line aims to tokenlize a line of input, for example:
* user input: (define a (+ 1 2))
* should get: "(", "define", "a", "(", "+", "1", "2", ")".
*/
vector<string> tokenize_line(const string& line);

/**
* next_candidate_token returns a pair (tok, k'), where tok is the next substring of line at or
* after position k that could be a token (assuming it passes a validity check), and k' is the 
* position in line following that token. returns ("", line.size()) when there are no more tokens.
*/
pair<string, int> next_candidate_token(const string& line, int k);

// to check if one symbol is valid.
bool valid_symbol(const string& s);

// to check if one token is too long.
void check_token_length_warning(const string& token, int length);

#endif // !TOKENIZER_H
