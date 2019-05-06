#pragma once
#include <iostream>
#include <vector>

using namespace std;


//-----------------------------------NAIVE--------------------------------------------------------------------------


template <class Graph>
class Naive
{
private:
	Graph &G;
	vector<pair<int, int> >  bridges;
	vector <bool> visited;
	int counter;													//licznik spójnych składowych
public:
	Naive(Graph &G) : G(G), visited(G.s, 0) {}

	void ccn()														//Funkcja zwracająca liczbę spójnych składowych w grafie
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

	//Zaznaczamy bieżący wierzchołek jako odwiedzony. Przechodzimy do kolejnych sąsiadów wierzchołka bieżącego i wykonujemy dla nich tą samą operację 
	//(tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich sąsiadów). Przechodzenie kończymy, gdy zostaną w ten sposób odwiedzone wszystkie dostępne wierzchołki.
	void DFS(int start)								
	{
		visited[start] = true;							// Zaznaczamy węzeł jako odwiedzony					

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych sąsiadów
			if (G.exist(start, i) && !visited[i])
				DFS(i);
	}

	void bridgeSearch()
	{
		ccn();
		int orginalCounter = counter;
		
		for (int i = 0 ; i < G.s ; i++)				//	i - pierwszy wierzchołek
		{
			for (int j = i + 1; j < G.s; j++)		// j - drugi wierzchołek
			{
				if (G.exist(i, j))					// jeśli istnieje krawędź łącząca i,j
				{
					G.remEdge(i,j);
					ccn();							// sprawdzamy liczbe skladowych dla grafu bez tej krawedzi
					G.addEdge(i, j);

					if (counter > orginalCounter)	// jesli lista skladowych jest wieksza to znaczy ze ta krawędź jest mostem
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
			cout << bridges[i].first <<"," << bridges[i].second << " ";
		}
		cout << endl;
	}
};


//-------------------------------------BETTER NAIVE------------------------------------------------------------------------


template <class Graph>
class BetterNaive
{
private:
	Graph &G;
	vector<pair<int, int> >  bridges;
	vector <bool> visited;
	vector<pair<int, int> >  edges;
	int counter;					//licznik spójnych składowych
	bool firstDFS;

public:
	BetterNaive(Graph &G) : G(G), visited(G.s, 0) {firstDFS = 1; }

	void ccn()														//Funkcja zwracająca liczbę spójnych składowych w grafie
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
		firstDFS = 0;
	}

	//Zaznaczamy bieżący wierzchołek jako odwiedzony. Przechodzimy do kolejnych sąsiadów wierzchołka bieżącego i wykonujemy dla nich tą samą operację 
	//(tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich sąsiadów). Nastepnie znaleziona krawedz wrzucamy do listy przechowujacej krawędzie.
	//Przechodzenie kończymy, gdy zostaną w ten sposób odwiedzone wszystkie dostępne wierzchołki.
	void DFS(int start)
	{
		visited[start] = true;							// Zaznaczamy wierzchołek jako odwiedzony					

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych sąsiadów
		{
			if (G.exist(start, i) && !visited[i])
			{
				if (firstDFS)							//jesli jest to pierwsze wywolanie funkcji DFS przez funckje ccn i danej krawędzi nie ma jeszcze na liscie, to dodajemy ja do listy
				{
					pair <int, int> temp(start, i);
					edges.push_back(temp);
				}				
				DFS(i);
			}
		}
	}

	void bridgeSearch()
	{
		ccn();
		int orginalCounter = counter;

		for (int i = 0; i < edges.size(); i++)		//	przechodzimy przez wszystkie krawędzie 
		{
			G.remEdge(edges[i].first, edges[i].second);
			ccn();									// sprawdzamy liczbe skladowych dla grafu bez danej krawedzi
			G.addEdge(edges[i].first, edges[i].second);

			if (counter > orginalCounter)			// jesli lista skladowych jest wieksza to znaczy ze ta krawędź jest mostem
			{
				bridges.push_back(edges[i]);		//wiec dodaje ja do vectora przechowujacego krawedzie bedace mostami
			}
		}
	}

	void show()
	{
		cout << "Mosty: ";
		for (int i = 0; i < bridges.size(); i++)
		{
			cout << bridges[i].first << "," << bridges[i].second << " "; 
		}
		cout << endl;
	}
};



//-------------------------------------TARJAN------------------------------------------------------------------------


template <class Graph>
class Tarjan
{
private:
	Graph &G;
	vector<pair<int, int> >  bridges;
	int counter;					//licznik spójnych składowych
	int vertexCounter;
	vector <bool> visited;
	vector<int> vertexNumber;		//Numeracja wierzchołków

public: 
	Tarjan(Graph &G) : G(G), visited(G.s, 0), vertexNumber(G.s,0) {}

	int TarjanDFS(int v, int father)		// Funkcja rekurencyjna wyszukująca mosty,  v  - numer bieżącego wierzchołka, father - ojciec bieżącego wierzchołka na drzewie rozpinającym
	{
		int Low = vertexCounter;
		vertexNumber[v] = vertexCounter;
		vertexCounter++;

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych sąsiadów
		{
			if (G.exist(v, i) && i != father)			//Jesli i jest sąsiadem v i i nie jest ojcem v
			{
				if (vertexNumber[i] == 0)				//oraz i nie zostało jeszcze odwiedzone 
				{
					int temp = TarjanDFS(i, v);			//rekurencyjnie odwiedzam sąsiada i zapamietuje jego wartość Low
					if (temp < Low) Low = temp;			// ten i następny elif ustawiaja jako wartość Low mniejszą spośród temp i vertexNumber ojca
				}
				else if (vertexNumber[i] < Low) Low = vertexNumber[i];

			}
		}

		if ((father > -1) && (Low == vertexNumber[v]))  //jeśli te wartości są takie same, to znaczy że jest to most
		{
			pair <int, int> temp(father, v);
			bridges.push_back(temp);
		}

		return Low;										//zwracam wartość Low
	}

	void bridgeSearch()
	{
		for (int i = 0; i < G.s; i++)
			if (vertexNumber[i] == 0)			// Szukamy nieodwiedzonego wierzchołka
			{
				vertexCounter = 1;				// Początek numeracji DFS
				TarjanDFS(i, -1);				// Szukamy mostów
			}
	}

	void show()
	{
		cout << "Mosty: ";
		for (int i = 0; i < bridges.size(); i++)
		{
			cout << bridges[i].first << "," << bridges[i].second << " ";
		}
		cout << endl;
	}
};
