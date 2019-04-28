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
	int k;													//liczba krawedzi
	ListGraph(int s) : L(s, vector<int>()), s(s) { k = 0; }
	void addEdge(int, int);
	void remEdge(int, int);
	bool exist(int, int);
	const vector<int> &getNeighbours(int v) { return L[v]; }
	class AdjIterator
	{
		const ListGraph &G;
		size_t index = 0;
		int node;
	public:
		AdjIterator(const ListGraph G, int v) : G(G), node(v) {}
		int begin() { if (G.L[node].size() == 0) return -1; index = 0; return G.L[node][0]; }
		bool end() { return (index == G.L[node].size()); }
		int next() { return G.L[node][index++]; }
	};
	friend class AdjIterator;
};

void ListGraph::addEdge(int w, int v)
{
	L[v].push_back(w);
	L[w].push_back(v);
	k++;
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
