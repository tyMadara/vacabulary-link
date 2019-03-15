#include "WordGraph.h"

using namespace std;

WordGraph::WordGraph() {
	for (int i = 0; i < 26; i++) {
		v.push_back(Vertex(i + 'a'));
	}
}

void WordGraph::clearAllStar() const {
	for (const auto &vex : v) {
		for (const auto &arc : vex.adjarcs) {
			arc.clearStar();
		}
	}
}