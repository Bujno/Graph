#pragma once
#include<ctime>
#include <stdlib.h>

using namespace std;

template <class Graph>
double generate(Graph &G, int e)									// e - krawedzie
{
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < e; i++)
	{	
		do {
			x = rand() % G.s;
			y = rand () % G.s;
		} while (x == y || G.exist(x,y));
		G.addEdge(x, y);
	}
	return (double)e / (double)G.s;												// zwraca gêstoœæ
}

template <class Graph>
void show(Graph &G)
{
	int counter = 1;
	cout << endl;
	for (int i = 0; i < G.s; i++)
	{
		for (int j = i + 1; j < G.s; j++)
		{
			if (G.exist(i, j))
			{
				cout << counter << ". (" << i << "," << j << ")" << endl;
				counter++;
			}
		}
	}
}