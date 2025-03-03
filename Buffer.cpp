#include "Buffer.h"
#include "SchemeReader.h"

Buffer::Buffer(InputReader* input) : index(0), input(input), currentLine({}) {
	loadNextLine();
}

string Buffer::popFirst() {
	string current_token = current();
	index += 1;
	return current_token;
}

string Buffer::current() {
	while (!moreOnLine()) {
		index = 0;
		loadNextLine();
	}
	return currentLine[index];
}

/* Check if reach the end of current line. */
const bool Buffer::moreOnLine() {
	return index < currentLine.size();
}

void Buffer::loadNextLine() {
    currentLine = input->getInput();

    /* Abandoned implements
    if (lineIndex < lines.size()) {
        currentLine = lines[lineIndex];
        lineIndex += 1;
    }
    else {
        currentLine.clear();
    }
    */

    /* Abandoned Implement.
    string line;
    if (getline(input, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        currentLine = tokens;
        lines.push_back(tokens);
    }
    else {
        currentLine.clear();
    }
    */
}


/* Print out a buffer for debugging */
std::string Buffer::to_string() const {
    std::ostringstream oss;
    oss << "Current line: ";
    for (int i = 0; i < currentLine.size(); i++) {
        if (i == index) {
            oss << ">> ";
        }
        oss << currentLine[i] << " ";
    }

    if (index == currentLine.size()) {
        oss << ">> ";
    }
    return oss.str();
}

/* This function is to test whether Buffer works well. */
void bufferTest() {
    std::istringstream input("( +\n15\n12 )\n");
    /**
    * Input: ( +
    *        15
    *        12 )
    */
    Buffer* buf = bufferInput("buffer> ", input, false);
    std::cout << "Initial state:\n" << buf->to_string() << "\n";
    std::cout << "First token: " << buf->popFirst() << "\n\n";

    std::cout << "State after first token:\n" << buf->to_string() << "\n";
    std::cout << "Second token: " << buf->popFirst() << "\n\n";

    std::cout << "State after second token:\n" << buf->to_string() << "\n";
    std::cout << "Third token: " << buf->popFirst() << "\n";

    std::cout << "State after third token:\n" << buf->to_string() << "\n";
    std::cout << "Fourth token: " << buf->popFirst() << "\n\n";

    std::cout << "State after fourth token:\n" << buf->to_string() << "\n\n";
    std::cout << "Fifth token: " << buf->popFirst() << "\n\n";

    std::cout << "State after fifth token:\n" << buf->to_string() << "\n\n";
}