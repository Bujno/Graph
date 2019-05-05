#pragma once
#include <iostream>
#include <vector>

using namespace std;

class MatrixGraph
{
	vector<vector<int> > L;
public:
	int s;													//liczba wierzcho³ków
	MatrixGraph(int s) : L(s, vector<int>(s, 0)), s(s) {}
	void addEdge(int, int);
	void remEdge(int, int);
	bool exist(int, int);
};

void MatrixGraph::addEdge(int w, int v)
{
	L[w][v] = 1;
	L[v][w] = 1;
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