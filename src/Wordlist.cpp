//#define NDEBUG

#include "InputParser.h"
#include "WordGraph.h"
#include "readFile.h"

using namespace std;

#define USAGE " {-w|-c} <input_file> [-h <first_character>] [-t <last_character>] [-n <word_num>]"

int main(int argc, char *argv[]) {

	// parse input
	InputParser inputParser(argv);
	try {
		inputParser.parse();
	} catch (runtime_error err) {
		cerr << err.what() << endl << "Usage: " << argv[0] << USAGE << endl;
		return -1;
	}
#ifndef NDEBUG
	cout << endl << "------args information-------" << endl;
	inputParser.print(cout) << endl;
#endif

	// read file
	vector<string> words;
	try {
		readFile(words, inputParser.getInputFileName());
	} catch (runtime_error err) {
		cerr << err.what() << endl;
		return -1;
	}

	// create graph
	WordGraph graph;
	for (const auto &s : words) graph.createArc(s);
#ifndef NDEBUG
	cout << endl << "------graph information------" << endl;
	graph.print(cout) << endl;
#endif

	// calculate
	

	return 0;
}