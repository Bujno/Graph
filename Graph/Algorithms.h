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
	vector <int> components;
public:
	void show()
	{
		for (int i = 0; i < components.size(); i++)
			cout << components[i] << " ";
	}
	DFS(Graph &G) :G(G), visited(G.s, 0)  {}
	void search(int start)
	{
		visited[start] = true;							// Zaznaczamy wêze³ jako odwiedzony					
		components.push_back(start);					// Przetwarzamy wêze³ (dodaje do listy)

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów
			if (G.exist(start,i) && !visited[i])
				search(i);
	}
};

template <class Graph>
class Naive
{
private:
	Graph &G;
public:
	Naive(Graph &G) : G(G) {}



};