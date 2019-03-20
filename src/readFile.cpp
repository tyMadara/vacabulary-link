#include "readFile.h"
#include <iostream>
void readFile(std::vector <std::string> &words, const std::string &path) {
	std::ifstream in(path.c_str());
	if (!in.is_open()) throw std::runtime_error("Open " + path + " failed");
	int c;
	bool flag = true;
	std::string buffer;
	while ((c = in.get()) != EOF) {
		if (isalpha(c)) {
			buffer += tolower(c);
			flag = true;
		} else if (flag) {
			words.push_back(buffer);
			buffer = "";
			flag = false;
		}
	}
	if (words.size() == 0) throw std::runtime_error("No words!");
}
