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
		/*for (int i = 0; i < qlist.size(); i++)
			cout << qlist[i].value << " ";
		cout << endl;*/
        if(depth-1 > wm->getMaxlength())
        {
            wm->setMaxLength(depth-1);
            wm->setQlist(qlist);
        }
    }
}

void DSearch2(vector<ArcNode> &qlist, int depth, Vertex &vex, ArcNode &node, WordMost *wm)
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
            DSearch2(qlist, depth+(int)node.value.length(), vex.adjArcs()[i].adjVex() , node, wm);
            vex.adjArcs()[i].clearStar();
            qlist.pop_back();
            /*for(int i=0; i<qlist.size() ; i++)
                cout << qlist[i].value << qlist.size() << " ";
            cout << endl;*/
        }
    }
    if(flag == 0)
    {
		/*for (int i = 0; i < qlist.size() ; i++)
			cout << qlist[i].value << "-";
		cout << endl;*/
        if(depth > wm->getMaxlength())
        {
            wm->setMaxLength(depth);
            wm->setQlist(qlist);
        }
    }
}

void WordMost::wordMostSearch()
{
    setMaxLength(0);
    graph.clearAllStar();
    vector<ArcNode> qlist;
    ArcNode node;
    vector<Vertex> &v = graph.v;
    for(int i=0; i<26; i++)
    {
        DSearch(qlist, 1, v[i], node, this);
		graph.clearAllStar();
    }
}

void WordMost::letterMostSearch()
{
    setMaxLength(0);
    graph.clearAllStar();
    vector<ArcNode> qlist;
    ArcNode node;
    vector<Vertex> &v = graph.v;
    for(int i=0; i<26; i++)
    {
        DSearch2(qlist, 0, v[i], node, this);
		graph.clearAllStar();
    }
}

void randDSearch(vector<Arc *> &arclist,vector<ArcNode> &qlist, Vertex &vex, ArcNode &node)
{
	vector<int> arcArray;
	for (int i = 0; i < vex.adjArcs().size(); i++)
	{
		if (vex.adjArcs()[i].isStar() == false)
		{
			arcArray.push_back(i);
		}
	}
	/*cout <<"vex " << vex.getName() << " " <<  " arcArray = " << arcArray.size() << endl;*/
	if (arcArray.size() == 0)
	{
		/*for (int i = 0; i < qlist.size() ; i++)
			cout << qlist[i].value << "-";
		cout << endl;*/
		return;
	}
	else
	{
		int rnum = rand() % arcArray.size();
		vex.adjArcs()[arcArray[rnum]].setStar();
		arclist.push_back(&vex.adjArcs()[arcArray[rnum]]);
		node.value = vex.adjArcs()[arcArray[rnum]].getName();
		qlist.push_back(node);
		randDSearch(arclist, qlist, vex.adjArcs()[arcArray[rnum]].adjVex(), node);
	}
}

void WordMost::wordMostLargeScaleSearch()
{
	srand(time(0));
	setMaxLength(0);
	graph.clearAllStar();
	vector<Arc *> arclist,lastarclist;
	vector<ArcNode> qlist,lastqlist;
	ArcNode node;
	vector<Vertex> &v = graph.v;
	time_t starttime = clock(),lasttime = clock();
	int vexnum;
	int arcnum;
	int curlength;
	while (clock() - starttime < timelimit)
	{
		do
		{
			graph.clearAllStar();
			/*cout << "curtime1  " << clock() - starttime << endl;*/
			qlist.clear();
			arclist.clear();
			vexnum = rand() % 26;
			//cout << "vexnum  " << char(vexnum + 'a') << endl;
			randDSearch(arclist, qlist, v[vexnum], node);
			curlength = qlist.size();
			if (curlength > getMaxlength())
			{
				setMaxLength(curlength);
				setQlist(qlist);
			}
			lastarclist.assign(arclist.begin(), arclist.end());
			lastqlist.assign(qlist.begin(), qlist.end());
			//cout << curlength << endl;
		} while (curlength == 0);
		lasttime = clock();

		while (clock() - lasttime < timelimit/4)
		{
			/*cout << "curtime2  " << clock() - lasttime << endl;*/
			if (curlength > 20)
				arcnum = curlength - rand() % 10 - 1;
			else
				arcnum = curlength - rand() % (curlength / 2) - 1;
			qlist.erase(begin(qlist) + arcnum, end(qlist));

			for (int j = arcnum; j < curlength; j++)
			{
				arclist[j]->clearStar();
			}

			arclist.erase(begin(arclist) + arcnum, end(arclist));

	
			randDSearch(arclist, qlist, arclist[arcnum -1]->adjVex(), node);
			if (qlist.size() > curlength)
			{
				curlength = qlist.size();
				lastarclist.assign(arclist.begin(), arclist.end());
				lastqlist.assign(qlist.begin(), qlist.end());
			}
			else
			{
				graph.clearAllStar();
				arclist.assign(lastarclist.begin(), lastarclist.end());
				qlist.assign(lastqlist.begin(), lastqlist.end());
				for (int j = 0; j < arclist.size(); j++)
				{
					arclist[j]->setStar();
				}
			}
			
			/*for (int j = 0; j < arclist.size(); j++)
				cout << arclist[j]->getName() << " ";
			cout << qlist.size() << endl;*/
		}
		if (curlength > getMaxlength())
		{
			setMaxLength(curlength);
			setQlist(qlist);
		}
	}

}