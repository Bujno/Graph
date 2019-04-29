#pragma once
#include <iostream>
#include <vector>
#include <deque>

using namespace std;


//-----------------------------------NAIVE--------------------------------------------------------------------------


template <class Graph>
class Naive
{
private:
	Graph &G;
	vector<pair<int, int> >  bridges;
	vector <bool> visited;
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

	//Zaznaczamy bie¿¹cy wierzcho³ek jako odwiedzony. Przechodzimy do kolejnych s¹siadów wierzcho³ka bie¿¹cego i wykonujemy dla nich t¹ sam¹ operacjê 
	//(tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich s¹siadów). Przechodzenie koñczymy, gdy zostan¹ w ten sposób odwiedzone wszystkie dostêpne wierzcho³ki.
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
	int counter;					//licznik spójnych sk³adowych
	bool firstDFS;

public:
	BetterNaive(Graph &G) : G(G), visited(G.s, 0) {firstDFS = 1; }

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
		firstDFS = 0;
	}

	//Zaznaczamy bie¿¹cy wierzcho³ek jako odwiedzony. Przechodzimy do kolejnych s¹siadów wierzcho³ka bie¿¹cego i wykonujemy dla nich t¹ sam¹ operacjê 
	//(tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich s¹siadów). Nastepnie znaleziona krawedz wrzucamy do listy przechowujacej krawêdzie.
	//Przechodzenie koñczymy, gdy zostan¹ w ten sposób odwiedzone wszystkie dostêpne wierzcho³ki.
	void DFS(int start)
	{
		visited[start] = true;							// Zaznaczamy wierzcho³ek jako odwiedzony					

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów
		{
			if (G.exist(start, i) && !visited[i])
			{
				if (firstDFS)							//jesli jest to pierwsze wywolanie funkcji DFS przez funckje ccn i danej krawêdzi nie ma jeszcze na liscie, to dodajemy ja do listy
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

		for (int i = 0; i < edges.size(); i++)		//	przechodzimy przez wszystkie krawêdzie 
		{
			G.remEdge(edges[i].first, edges[i].second);
			ccn();									// sprawdzamy liczbe skladowych dla grafu bez danej krawedzi
			G.addEdge(edges[i].first, edges[i].second);

			if (counter > orginalCounter)			// jesli lista skladowych jest wieksza to znaczy ze ta krawêdŸ jest mostem
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



//-------------------------------------BETTER NAIVE------------------------------------------------------------------------


template <class Graph>
class Trojan
{
private:
	Graph &G;
	vector<pair<int, int> >  bridges;
	int counter;					//licznik spójnych sk³adowych
	int vertexCounter;
	vector <bool> visited;
	vector<int> vertexNumber;		//Numeracja wierzcho³ków

public: 
	Trojan(Graph &G) : G(G), visited(G.s, 0), vertexNumber(G.s,0) {}

	int TrojanDFS(int v, int father)		// Funkcja rekurencyjna wyszukuj¹ca mosty,  v  - numer bie¿¹cego wierzcho³ka, father - ojciec bie¿¹cego wierzcho³ka na drzewie rozpinaj¹cym
	{
		int Low = vertexCounter;
		vertexNumber[v] = vertexCounter;
		vertexCounter++;

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów
		{
			if (G.exist(v, i) && i != father)			//Jesli i jest s¹siadem v i i nie jest ojcem v
			{
				if (vertexNumber[i] == 0)				//oraz i nie zosta³o jeszcze odwiedzone 
				{
					int temp = TrojanDFS(i, v);			//rekurencyjnie odwiedzam s¹siada i zapamietuje jego wartoœæ Low
					if (temp < Low) Low = temp;			// ten i nastêpny elif ustawiaja jako wartoœæ Low mniejsz¹ spoœród temp i vertexNumber ojca
				}
				else if (vertexNumber[i] < Low) Low = vertexNumber[i];

			}
		}

		if ((father > -1) && (Low == vertexNumber[v]))  //jeœli te wartoœci s¹ takie same, to znaczy ¿e jest to most
		{
			pair <int, int> temp(father, v);
			bridges.push_back(temp);
		}

		return Low;										//zwracam wartoœæ Low
	}

	void bridgeSearch()
	{
		for (int i = 0; i < G.s; i++)
			if (vertexNumber[i] == 0)			// Szukamy nieodwiedzonego wierzcho³ka
			{
				vertexCounter = 1;				// Pocz¹tek numeracji DFS
				TrojanDFS(i, -1);				// Szukamy mostów
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