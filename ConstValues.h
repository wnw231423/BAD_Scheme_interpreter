// This part offers some constant sets of chars which are used in tokenlizing and scheme_reader process.
#ifndef CONSTVALUES_H
#define CONSTVALUES_H
#include <unordered_set>

const std::unordered_set<char> NUMERAL_STARTS = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '.' };

const std::unordered_set<char> SYMBOL_CHARS = [] {
    std::unordered_set<char> set;
    for (char c = 'a'; c <= 'z'; ++c) set.insert(c);
    for (char c = 'A'; c <= 'Z'; ++c) set.insert(c);
    for (char c : "!$%&*/:<=>?@^_~") set.insert(c);
    set.insert(NUMERAL_STARTS.begin(), NUMERAL_STARTS.end());
    return set;
    }(); //Lambda function used to initialize a set.

    const std::unordered_set<char> STRING_DELIMS = { '"' };

    const std::unordered_set<char> WHITESPACE = { ' ', '\t', '\n', '\r' };

    const std::unordered_set<char> SINGLE_CHAR_TOKENS = { '(', ')', '[', ']', '\'', '`' };

    const std::unordered_set<char> TOKEN_END = [] {
        std::unordered_set<char> set = WHITESPACE;
        set.insert(SINGLE_CHAR_TOKENS.begin(), SINGLE_CHAR_TOKENS.end());
        set.insert(STRING_DELIMS.begin(), STRING_DELIMS.end());
        set.insert({',', '@' });
        return set;
        }();

const std::unordered_set<std::string> DELIMITERS = { "(", ")", "[", "]", "'", "`", ",", ",@" };  // Update in 6/12, delete "."

const int MAX_TOKEN_LENGTH = 50;

#endif // !CONSTVALE_H
