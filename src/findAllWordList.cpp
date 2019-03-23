#include "findAllWordList.h"

using namespace std;
#define OUTPUT_FILE "solution.txt"
static vector<const string *>::size_type depthLimit;
static vector<const string *> wordlist;
static FILE *fp;
static int num = 0;
static char endc;

static inline void openFile() {
	if ((fp = fopen(OUTPUT_FILE, "w")) == NULL) {
		cerr << "error: cannot open file 'solution.txt'" << endl;
		exit(0);
	}
	fprintf(fp, "           \n");
}

static inline void closeFile() {
	rewind(fp);
	fprintf(fp, "%d", num);
	fclose(fp);
}

static inline void writeListToFile(const char *s) {	// s is the last string 
	++num;
	for (const auto *s : wordlist) {
		fprintf(fp, "%s\n", s->c_str());
	}
	fprintf(fp, "%s\n\n", s);
}

static inline void revWriteListToFile(const char *s) {	// s is the first string 
	++num;
	fprintf(fp, "%s\n", s);
	for (auto it = wordlist.cend(); it != wordlist.cbegin(); --it) {
		fprintf(fp, "%s\n", (*(it - 1))->c_str());
	}
	fprintf(fp, "\n");
}

static void DLS(const Vertex &v) {
	if (wordlist.size() == depthLimit) {
		for (const auto &arc : v.adjArcs()) {
			if (arc.isStar() == false) {
				writeListToFile(arc.getName().c_str());
			}
		}
	} else {
		for (const auto &arc : v.adjArcs()) {
			if (arc.isStar() == false) {
				arc.setStar();
				wordlist.push_back(&arc.getName());
				DLS(arc.adjVex());
				wordlist.pop_back();
				arc.clearStar();
			}
		}
	}
}

static void DLSWithEnd(const Vertex &v) {
	if (wordlist.size() == depthLimit) {
		for (const auto &arc : v.adjArcs()) {
			if (arc.adjVexName() == endc && arc.isStar() == false) {
				writeListToFile(arc.getName().c_str());
			}
		}
	} else {
		for (const auto &arc : v.adjArcs()) {
			if (arc.isStar() == false) {
				arc.setStar();
				wordlist.push_back(&arc.getName());
				DLSWithEnd(arc.adjVex());
				wordlist.pop_back();
				arc.clearStar();
			}
		}
	}
}

static void revDLS(const Vertex &v) {
	if (wordlist.size() == depthLimit) {
		for (const auto *arc : v.revAdjArcsPtr()) {
			if (arc->isStar() == false) {
				revWriteListToFile(arc->getName().c_str());	
			}
		}
	} else {
		for (const auto *arc : v.revAdjArcsPtr()) {
			if (arc->isStar() == false) {
				arc->setStar();
				wordlist.push_back(&arc->getName()); //cout << v.getName() << "->" << arc->revAdjVexName() << " : " << arc->getName() << endl;
				revDLS(arc->revAdjVex());
				wordlist.pop_back();
				arc->clearStar();
			}
		}
	}
}

void findAllWordList(const WordGraph &graph, int wordnum, char b, char e) {
	openFile();
	depthLimit = wordnum - 1;
	if (b == '\0' && e == '\0') {
		for (const auto &v : graph.getAllVertex()) 
			DLS(v);
	} else if (b && e == '\0') {
		DLS(graph.getVertex(b));
	} else if (b == '\0' && e) {
		revDLS(graph.getVertex(e));
	} else {
		endc = e;
		DLSWithEnd(graph.getVertex(b));
	}
	
	closeFile();
}
