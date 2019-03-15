#include "InputParser.h"
#include "WordGraph.h"

using namespace std;

int main(int argc, char *argv[]) {
	InputParser inputParser(argv);
	inputParser.parse();

	WordGraph graph;
	graph.createArc("abc");
	graph.createArc("cba");
	graph.createArc("abc");
	graph.createArc("aaa");
	graph.getVertex('a').adjArcs()[1].setStar();
	
	graph.print(cout);

	getchar();
	return 0;
}