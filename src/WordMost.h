#ifndef WORDMOST_H
#define WORDMOST_H
#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include"WordGraph.h"

class ArcNode;

class ArcNode
{
public:
    std::string value;
    int depth;
};

class WordMost
{
    public:
        WordMost(WordGraph &g):graph(g) {}
        virtual ~WordMost();
        void wordMostSearch();
        void letterMostSearch();
        void setMaxLength(int len){maxlength = len;}
        int getMaxlength() {return maxlength;}
        void setQlist(std::vector<ArcNode> &qlist) {maxQlist.clear(); maxQlist.assign(qlist.begin(), qlist.end());}
		void wordMostLargeScaleSearch();
		void setTimeLimit(time_t time) { timelimit = time; }
        std::vector<ArcNode> maxQlist;

    protected:

    private:
		time_t timelimit = 1000;
		WordGraph &graph;
        int maxlength = 0;

};

#endif // WORDMOST_H
