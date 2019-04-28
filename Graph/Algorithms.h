#pragma once
#include <iostream>
#include <vector>
#include <vector>

using namespace std;

template <class Graph>
class DFS
{
private:
	Graph &G;
	vector <bool> visited;
public:
	vector <int> 

	DFS(Graph &G) :G(G), visited(G.s, 0)  {}
	void search(int start)
	{
		visited[start] = true;							// Zaznaczamy w�ze� jako odwiedzony
		cout << start;									// Przetwarzamy w�ze� (wypisujemy jego numer)

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w
			if (G.exist(start,i) && !visited[i])
				search(i);
	}
};

