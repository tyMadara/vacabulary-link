#ifndef WORD_GRAPH_H
#define WORD_GRAPH_H

#include <vector>
#include <string>
#include <iostream>

class Arc;
class Vertex;
class WordGraph;

class Arc {
	friend class WordGraph;
private:
	std::string name;
	Vertex &adjv;
	mutable bool star = false;

public:
	Arc(const std::string &s, Vertex &v) : name(s), adjv(v) {}
	std::string::size_type getLength() const { return name.size(); }
	const std::string &getName() const { return name; }
	char adjVexName() const { return name[name.size() - 1]; }	// arc head
	Vertex &adjVex() const { return adjv; }	// arc head
	void setStar() const { star = true; }
	void clearStar() const { star = false; }
	bool isStar() const { return star; }
};


class Vertex {
	friend class WordGraph;
private:
	char name;
	std::vector<Arc> adjarcs;

public:
	Vertex(char n) : name(n) {}
	char getName() const { return name; }
	const std::vector<Arc> &adjArcs() const { return adjarcs; }
	std::vector<Arc> &adjArcs() { return adjarcs; }
};


class WordGraph {

private:
	std::vector<Vertex> v;
	
public:
	WordGraph();
	Vertex &getVertex(char c) { return v[c - 'a']; }
	const Vertex &getVertex(char c) const { return v[c - 'a']; }
	void createArc(const std::string &s) {
		const char b = s[0];
		const char e = s[s.size() - 1];
		getVertex(b).adjarcs.push_back(Arc(s, getVertex(e)));
	}
	void clearAllStar() const;

#ifndef NDEBUG
	std::ostream &print(std::ostream &os) const {
		for (const auto &vex : v) {
			if (!vex.adjarcs.size()) continue;
			os << vex.name << ": " << std::endl;
			for (const auto &arc : vex.adjarcs) {
				os << "\t" << (arc.isStar() ? "(*)" : "") << arc.name;
			}
			os << std::endl;
		}
		return os;
	}
#endif	// NDEBUG

};

#endif	// WORD_GRAPH_H