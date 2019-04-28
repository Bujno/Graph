#pragma once
#include <iostream>
#include <vector>

using namespace std;

class MatrixGraph
{
	vector<vector<int> > L;
public:
	int s;													//liczba wierzcho³ków
	int k;													//liczba krawedzi
	MatrixGraph(int s) : L(s, vector<int>(s, 0)), s(s) { k = 0; }
	void addEdge(int, int);
	void remEdge(int, int);
	bool exist(int, int);
	const vector<int> &getNeighbours(int v) { return L[v]; }

	class AdjIterator
	{
		const MatrixGraph &G;
		size_t index = 0;
		int node;
	public:
		AdjIterator(const MatrixGraph G, int v) : G(G), node(v) {}
		int begin()
		{
			index = 0;
			for (int i = 0; i < G.L[node].size(); i++)
			{
				if (G.L[node][i] == 1) return i;
			}
			return -1;
		}
		bool end() { return (index == G.L[node].size()); }
		int next() { if (G.L[node][index] == 0) index++; else return G.L[node][index++]; }
	};
	friend class AdjIterator;
};

void MatrixGraph::addEdge(int w, int v)
{
	L[w][v] = 1;
	L[v][w] = 1;
	k++;
}

void MatrixGraph::remEdge(int w, int v)
{
	L[w][v] = 0;
	L[v][w] = 0;

}

bool MatrixGraph::exist(int w, int v)
{
	if (L[w][v]==1)
		return true;
	else return false;
}