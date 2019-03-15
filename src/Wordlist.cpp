#include "InputParser.h"
#include "WordGraph.h"

using namespace std;

int main(int argc, char *argv[]) {
	InputParser inputParser(argv);
	try {
		inputParser.parse();
	} catch (runtime_error err) {
		cerr << err.what() << endl;
		//exit(0);
	}



	getchar();
	return 0;
}