#pragma once
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template <class Graph>
class DFSClass
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
	DFSClass(Graph &G) :G(G), visited(G.s, 0)  {}
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
	vector<pair<int, int> >  bridges;
	vector <bool> visited;
	deque <int> S;													//Stos
	int counter;													//licznik spójnych sk³adowych
public:
	Naive(Graph &G) : G(G), visited(G.s, 0) {}
	void ccn()														//Funkcja zwracaj¹ca liczbê spójnych sk³adowych w grafie
	{
		counter = 0;
		for (int i = 0; i < G.s; i++)
		{
			if (!visited[i])
			{
				DFS(i);
				counter++;
			}
		}
		for (int i = 0; i < visited.size(); i++) visited[i] = 0;
	}

	void DFS(int start)
	{
		visited[start] = true;							// Zaznaczamy wêze³ jako odwiedzony					

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów
			if (G.exist(start, i) && !visited[i])
				DFS(i);
	}

	void bridgeSearch()
	{
		ccn();
		int orginalCounter = counter;
		
		for (int i = 0 ; i < G.s ; i++)				//	i - pierwszy wierzcho³ek
		{
			for (int j = i + 1; j < G.s; j++)		// j - drugi wierzcho³ek
			{
				if (G.exist(i, j))					// jeœli istnieje krawêdŸ ³¹cz¹ca i,j
				{
					G.remEdge(i,j);
					ccn();							// sprawdzamy liczbe skladowych dla grafu bez tej krawedzi
					G.addEdge(i, j);

					if (counter > orginalCounter)	// jesli lista skladowych jest wieksza to znaczy ze ta krawêdŸ jest mostem
					{
						pair<int, int> temp(i, j);
						bridges.push_back(temp);	//wiec dodaje ja do vectora przechowujacego krawedzie bedace mostami
					}
				}
			}
		}
	}

	void show()
	{
		cout << "Mosty: ";
		for (int i = 0; i < bridges.size(); i++)
		{
			cout << bridges[i].first <<"," << bridges[i].second << " " << endl;
		}
	}
};