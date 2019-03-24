#include "DebugInfo.h"
#include "InputParser.h"
#include "WordGraph.h"
#include "readFile.h"
#include "findAllWordList.h"
#include "findAllCharList.h"
#include "DebugTime.h"

using namespace std;

int doCalc(char *ret, std::vector <std::string> &words, const char *argv[]) {	//words	/////////////////////////////
	DebugTime t;

	// parse input
	InputParser inputParser(argv);
	inputParser.parse();
	t.printTimeAndRestart("Parse Input");
#ifndef NDEBUG
	cout << endl << "------args information-------" << endl;
	inputParser.print(cout) << endl;
#endif
	//std::vector <std::string> words;//////////////////////
	//readFile(words, "input.txt");	/////////////////////////
	// create graph
	WordGraph graph;
	for (const auto &s : words) graph.createArc(s);
	graph.setRevArc();
	t.printTimeAndRestart("Create Graph");
#ifndef NDEBUG
	cout << endl << "------graph information------" << endl;
	graph.print(cout) << endl;
	cout << endl << "--reverse graph information--" << endl;
	graph.printrev(cout) << endl;
#endif

	// calculate
	if (inputParser.getWordNum() != -1) {
#ifndef NDEBUGTIME
		cout << endl << "Detail Time For Calculate: " << endl;
#endif
		if (inputParser.maximumChar())
			findAllCharList(
				ret,
				graph,
				inputParser.getWordNum(),
				inputParser.getFirstChar(),
				inputParser.getLastChar()
			);
		else findAllWordList(
			ret, 
			graph, 
			inputParser.getWordNum(), 
			inputParser.getFirstChar(), 
			inputParser.getLastChar()
		);
	} else {
		// no word number limit
	}
	t.printTime("\nCalculate Total");
	return 0;
}