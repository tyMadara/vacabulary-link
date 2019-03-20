#ifndef WORDMOST_H
#define WORDMOST_H
#include<iostream>
#include<vector>
#include"WordGraph.h"

class ArcNode;
class WordMost;

class ArcNode
{
public:
    std::string value;
    int depth;
};

class WordMost
{
    public:
        WordMost(WordGraph g){graph = g;}
        virtual ~WordMost();
        void linkSearch();
        void setMaxLength(int len){maxlength = len;}
        int getMaxlength() {return maxlength;}
        void setQlist(std::vector<ArcNode> &qlist) {maxQlist.clear(); maxQlist.assign(qlist.begin(), qlist.end());}
        std::vector<ArcNode> maxQlist;

    protected:

    private:
        WordGraph graph;
        int maxlength = 0;

};

#endif // WORDMOST_H
