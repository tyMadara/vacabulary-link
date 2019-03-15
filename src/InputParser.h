#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <exception>

class InputParser {
private:
	std::vector<std::string> args;	// end with ""
	std::string filename;
	bool charmost = false;
	char firstchar = '\0';
	char lastchar = '\0';
	int wordnum = -1;

	void checkfilename() {
		if (filename.size()) {
			throw std::runtime_error("too much output file");
		}
	}

	void checkcharacter(const std::string &s) {
		if (s.size() != 1 || !isalpha(s[0])) {
			throw std::runtime_error("'" + s + "' not a valid character");
		}
	}

	void checknumber(int num) {
		if (num <= 0) {
			throw std::runtime_error("word number should be a positive integer");
		}
	}

	void checkarg(const std::string &s) {
		if (s.size()) {
			throw std::runtime_error("unknown arg '" + s + "'");
		}
	}

public:
	InputParser(char *args[]);
	void parse();
};

#endif