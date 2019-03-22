#include "WordMost.h"

using namespace std;

WordMost::~WordMost()
{
    //dtor
}

void DSearch(vector<ArcNode> &qlist, int depth, Vertex &vex, ArcNode &node, WordMost *wm)
{
    int flag = 0;
    for(int i=0; i<vex.adjArcs().size(); i++)
    {
        if(vex.adjArcs()[i].isStar() == false)
        {
            /*cout << vex.adjArcs()[i].getName() << endl;*/
            flag = 1;
            vex.adjArcs()[i].setStar();
            node.depth = depth;
            node.value = vex.adjArcs()[i].getName();
            qlist.push_back(node);
            DSearch(qlist, depth+1, vex.adjArcs()[i].adjVex() , node, wm);
            vex.adjArcs()[i].clearStar();
            qlist.pop_back();
            /*for(int i=0; i<qlist.size() ; i++)
                cout << qlist[i].value << " ";
            cout << endl;*/
        }
    }
    if(flag == 0)
    {
		/*for (int i = 0; i < depth - 1; i++)
			cout << qlist[i].value << " ";
		cout << endl;*/
        if(depth-1 > wm->getMaxlength())
        {
            wm->setMaxLength(depth-1);
            wm->setQlist(qlist);
        }
    }
}

void WordMost::linkSearch()
{
    vector<ArcNode> qlist;
    ArcNode node;
    vector<Vertex> &v = graph.v;
    for(int i=0; i<26; i++)
    {
        DSearch(qlist, 1, v[i], node, this);
    }
}
