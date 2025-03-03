#include "Tokenizer.h"
#include <iostream>
#include <sstream>
#include "ConstValues.h"
using namespace std;
/* Check if a string is a valid symbol */
bool valid_symbol(const string& s) {
    if (s.empty()) {
        return false;
    }
    for (char i : s) {
        if (SYMBOL_CHARS.find(i) == SYMBOL_CHARS.end()) {
            return false;
        }
    }
    return true;
}

pair<string, int> next_candidate_token(const string& line, int k) {
    while (k < line.size()) {
        char c = line[k];
        if (c == ';') {
            return { "", line.size() };
        }
        else if (WHITESPACE.find(c) != WHITESPACE.end()) {
            k += 1;
        }
        else if (SINGLE_CHAR_TOKENS.find(c) != SINGLE_CHAR_TOKENS.end()) {
            //change [] to ().
            if (c == ']') {
                c = ')';
            }
            else if (c == '[') {
                c = '(';
            }
            return { string(1, c), k + 1};
        }
        else if (c == '#') {
            //#t or #f
            //return {line.substr(k, 2), min(k + 2, (int)line.size())};
            return { line.substr(k, 2), k+2};
        }
        else if (c == ',') {
            // ,@ situation. I dont know this scheme grammar. Just keep here.
            if (k + 1 < line.size() && line[k + 1] == '@') {
                return { ",@", k + 2 };
            }
            else {
                string s;
                s = c;
                return { s, k + 1 };
            }
        }
        // handle string situation. e.g. scm>> "Hello, world!"
        else if (STRING_DELIMS.find(c) != STRING_DELIMS.end()) {
            string s = "\"";
            k += 1;
            while (k < line.size()) {
                c = line[k];
                if (c == '"') {
                    check_token_length_warning(s, s.size() - 1);
                    return { s + "\"", k + 1 };
                }
                else if (c == '\\') {
                    //E.g. scm>> "Hello, world\n
                    if (k + 1 == line.size()) {
                        throw runtime_error("String ended abruptly");
                    }
                    char next = line[k + 1];
                    s += (next == 'n') ? '\n' : next;
                    k = k + 2;
                }
                else {
                    s += c;
                    k += 1;
                }
            }
            throw runtime_error("String ended abruptly");
        }
        else {
            int j = k;
            while (j < line.size() && TOKEN_END.find(line[j]) == TOKEN_END.end()) {
                j += 1;
            }
            string token = line.substr(k, j - k);
            check_token_length_warning(token, token.size());
            return { token, j };
        }
    }
    return { "", line.size() };
}

vector<string> tokenize_line(const string& line) {
    vector<string> result;
    int i = 0;
    string text;
    tie(text, i) = next_candidate_token(line, 0);
    while (!text.empty()) {
        if (DELIMITERS.find(text) != DELIMITERS.end()) {
            result.push_back(text);
        }
        else if (text == "#t" || text == "true") {
            result.push_back("true");
        }
        else if (text == "#f" || text == "false") {
            result.push_back("false");
        }
        else if (text == "nil") {
            result.push_back(text);
        }
        else if (SYMBOL_CHARS.find(text[0]) != SYMBOL_CHARS.end()) {
            if (NUMERAL_STARTS.find(text[0]) != NUMERAL_STARTS.end()) {
                try {
                    if (text.find('.') != string::npos) {
                        float x = stof(text);
                        result.push_back("$f" + text);
                    }
                    else {
                        int x = stoi(text);
                        result.push_back("$i" + text);
                    }
                } 
                catch (...) {
                    if (valid_symbol(text)) {
                        result.push_back(text);
                    }
                    else {
                        throw runtime_error("Invalid numeral or symbol: " + text);
                    }
                }
            } 
            else {
                if (valid_symbol(text)) {
                    result.push_back(text);
                }
                else {
                    throw runtime_error("Invalid numeral or symbol: " + text);
                }
            }
        }
        else if (STRING_DELIMS.find(text[0]) != STRING_DELIMS.end()) {
            result.push_back(text);
        }
        else {
            throw runtime_error("Invalid token: " + text);
        }
        tie(text, i) = next_candidate_token(line, i);
    }
    return result;
}

/* Warning users not to use symbols of too big length. */
void check_token_length_warning(const string& token, int length) {
    if (length > MAX_TOKEN_LENGTH) {
        cerr << "Warning: Token " << token << " has exceeded the maximum token length " << MAX_TOKEN_LENGTH << "\n";
    }
}
