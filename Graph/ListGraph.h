#pragma once
#include <iostream>
#include <vector>
using namespace std;

class ListGraph
{
protected:
	vector<vector<int> > L;
public:
	int s;													//liczba wierzcho³ków
	ListGraph(int s) : L(s, vector<int>()), s(s) {}
	void addEdge(int, int);
	void remEdge(int, int);
	bool exist(int, int);
};

void ListGraph::addEdge(int w, int v)
{
	L[v].push_back(w);
	L[w].push_back(v);
}

void ListGraph::remEdge(int w, int v)
{
	for (int i = 0; i < L[w].size(); i++)
	{
		if (L[w][i] == v)
			L[w].erase(L[w].begin() + i);
	}
	for (int i = 0; i < L[v].size(); i++)
	{
		if (L[v][i] == w)
			L[v].erase(L[v].begin() + i);
	}
}

bool ListGraph::exist(int w, int v)
{
	for (int i = 0; i < L[w].size(); i++)
	{
		if (L[w][i] == v) return true;
	}
	return false;
}
