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
		visited[start] = true;							// Zaznaczamy wêze³ jako odwiedzony
		cout << start;									// Przetwarzamy wêze³ (wypisujemy jego numer)

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów
			if (G.exist(start,i) && !visited[i])
				search(i);
	}
};

