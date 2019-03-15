#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cctype>

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
			std::cerr << "error: too much output file" << std::endl;
			std::exit(-1);
		}
	}

	void checkcharacter(const std::string &s) {
		if (s.size() != 1 || !isalpha(s[0])) {
			std::cerr << "error: character format error" << std::endl;
			std::exit(-1);
		}
	}

	void checknumber(int num) {
		if (num < 0) {
			std::cerr << "error: word number should be positive" << std::endl;
			std::exit(-1);
		}
	}
public:
	InputParser(char *args[]);
	void parse();

};

#endif