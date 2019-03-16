CXX=g++

Wordlist: InputParser.o readFile.o WordGraph.o Wordlist.o
	$(CXX) $^ -o $@
	
.PHONY: clean

clean:
	rm -f *.o Wordlist