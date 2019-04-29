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
	int counter;													//licznik sp�jnych sk�adowych
public:
	Naive(Graph &G) : G(G), visited(G.s, 0) {}

	void ccn()														//Funkcja zwracaj�ca liczb� sp�jnych sk�adowych w grafie
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

	//Zaznaczamy bie��cy wierzcho�ek jako odwiedzony. Przechodzimy do kolejnych s�siad�w wierzcho�ka bie��cego i wykonujemy dla nich t� sam� operacj� 
	//(tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich s�siad�w). Przechodzenie ko�czymy, gdy zostan� w ten spos�b odwiedzone wszystkie dost�pne wierzcho�ki.
	void DFS(int start)								
	{
		visited[start] = true;							// Zaznaczamy w�ze� jako odwiedzony					

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w
			if (G.exist(start, i) && !visited[i])
				DFS(i);
	}

	void bridgeSearch()
	{
		ccn();
		int orginalCounter = counter;
		
		for (int i = 0 ; i < G.s ; i++)				//	i - pierwszy wierzcho�ek
		{
			for (int j = i + 1; j < G.s; j++)		// j - drugi wierzcho�ek
			{
				if (G.exist(i, j))					// je�li istnieje kraw�d� ��cz�ca i,j
				{
					G.remEdge(i,j);
					ccn();							// sprawdzamy liczbe skladowych dla grafu bez tej krawedzi
					G.addEdge(i, j);

					if (counter > orginalCounter)	// jesli lista skladowych jest wieksza to znaczy ze ta kraw�d� jest mostem
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
	int counter;					//licznik sp�jnych sk�adowych
	bool firstDFS;

public:
	BetterNaive(Graph &G) : G(G), visited(G.s, 0) {firstDFS = 1; }

	void ccn()														//Funkcja zwracaj�ca liczb� sp�jnych sk�adowych w grafie
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

	//Zaznaczamy bie��cy wierzcho�ek jako odwiedzony. Przechodzimy do kolejnych s�siad�w wierzcho�ka bie��cego i wykonujemy dla nich t� sam� operacj� 
	//(tzn. zaznaczamy je jako odwiedzone i przechodzimy do ich s�siad�w). Nastepnie znaleziona krawedz wrzucamy do listy przechowujacej kraw�dzie.
	//Przechodzenie ko�czymy, gdy zostan� w ten spos�b odwiedzone wszystkie dost�pne wierzcho�ki.
	void DFS(int start)
	{
		visited[start] = true;							// Zaznaczamy wierzcho�ek jako odwiedzony					

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w
		{
			if (G.exist(start, i) && !visited[i])
			{
				if (firstDFS)							//jesli jest to pierwsze wywolanie funkcji DFS przez funckje ccn i danej kraw�dzi nie ma jeszcze na liscie, to dodajemy ja do listy
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

		for (int i = 0; i < edges.size(); i++)		//	przechodzimy przez wszystkie kraw�dzie 
		{
			G.remEdge(edges[i].first, edges[i].second);
			ccn();									// sprawdzamy liczbe skladowych dla grafu bez danej krawedzi
			G.addEdge(edges[i].first, edges[i].second);

			if (counter > orginalCounter)			// jesli lista skladowych jest wieksza to znaczy ze ta kraw�d� jest mostem
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
	int counter;					//licznik sp�jnych sk�adowych
	int vertexCounter;
	vector <bool> visited;
	vector<int> vertexNumber;		//Numeracja wierzcho�k�w

public: 
	Trojan(Graph &G) : G(G), visited(G.s, 0), vertexNumber(G.s,0) {}

	int TrojanDFS(int v, int father)		// Funkcja rekurencyjna wyszukuj�ca mosty,  v  - numer bie��cego wierzcho�ka, father - ojciec bie��cego wierzcho�ka na drzewie rozpinaj�cym
	{
		int Low = vertexCounter;
		vertexNumber[v] = vertexCounter;
		vertexCounter++;

		for (int i = 0; i < G.s; i++)					// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w
		{
			if (G.exist(v, i) && i != father)			//Jesli i jest s�siadem v i i nie jest ojcem v
			{
				if (vertexNumber[i] == 0)				//oraz i nie zosta�o jeszcze odwiedzone 
				{
					int temp = TrojanDFS(i, v);			//rekurencyjnie odwiedzam s�siada i zapamietuje jego warto�� Low
					if (temp < Low) Low = temp;			// ten i nast�pny elif ustawiaja jako warto�� Low mniejsz� spo�r�d temp i vertexNumber ojca
				}
				else if (vertexNumber[i] < Low) Low = vertexNumber[i];

			}
		}

		if ((father > -1) && (Low == vertexNumber[v]))  //je�li te warto�ci s� takie same, to znaczy �e jest to most
		{
			pair <int, int> temp(father, v);
			bridges.push_back(temp);
		}

		return Low;										//zwracam warto�� Low
	}

	void bridgeSearch()
	{
		for (int i = 0; i < G.s; i++)
			if (vertexNumber[i] == 0)			// Szukamy nieodwiedzonego wierzcho�ka
			{
				vertexCounter = 1;				// Pocz�tek numeracji DFS
				TrojanDFS(i, -1);				// Szukamy most�w
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