#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Algorithms.h"
#include "Generator.h"
#include <fstream>


int main()
{
	ofstream MatrixFile("Martix.txt", ios::app);
	ofstream ListFile("List.txt", ios::app);
	int density [] = { 10, 20, 40, 60, 80, 100 };

	StartCounter();
	MatrixGraph M(20);
	MatrixFile << GetCounter() << ";";

	StartCounter();
	ListGraph L(20);
	ListFile << GetCounter() << ";";

	for (int i = 0; i < 6; i++)
	{
		StartCounter();
		MatrixFile << generate<MatrixGraph>(M, density[i]) << ";";
		MatrixFile << GetCounter() << ";";

		StartCounter();
		ListFile << generate<ListGraph>(L, density[i]) << ";";
		ListFile << GetCounter() << ";";
		
		//--------------------

		StartCounter();
		Naive<MatrixGraph> NaiveSearch_M(M);
		NaiveSearch_M.bridgeSearch();
		MatrixFile << GetCounter() << ";";

		StartCounter();
		BetterNaive<MatrixGraph> BetterNaiveSearch_M(M);
		BetterNaiveSearch_M.bridgeSearch();
		MatrixFile << GetCounter() << ";";

		StartCounter();
		Tarjan<MatrixGraph> TarjanSearch_M(M);
		TarjanSearch_M.bridgeSearch();
		MatrixFile << GetCounter() << ";";

		//--------------------

		StartCounter();
		Naive<ListGraph> NaiveSearch_L(L);
		NaiveSearch_L.bridgeSearch();
		ListFile << GetCounter() << ";";

		StartCounter();
		BetterNaive<ListGraph> BetterNaiveSearch_L(L);
		BetterNaiveSearch_L.bridgeSearch();
		ListFile << GetCounter() << ";";

		StartCounter();
		Tarjan<ListGraph> TarjanSearch_L(L);
		TarjanSearch_L.bridgeSearch();
		ListFile << GetCounter() << ";";

		//--------------------

		StartCounter();
		for (int j = 0; j < M.s; j++)
		{
			for (int k = j + 1; k < M.s; k++)
			{	
				M.exist(j, k);
			}
		}
		MatrixFile << GetCounter() << ";";

		StartCounter();
		for (int j = 0; j < L.s; j++)
		{
			for (int k = j + 1; k < L.s; k++)
			{
				L.exist(j, k);
			}
		}
		ListFile << GetCounter() << ";";

		//--------------------

		StartCounter();
		for (int j = 0; j < M.s; j++)
		{
			for (int k = j + 1; k < M.s; k++)
			{
				if (M.exist(j, k))
				{
					M.remEdge(j, k);
				}
			}
		}
		MatrixFile << GetCounter() << ";";

		StartCounter();
		for (int j = 0; j < L.s; j++)
		{
			for (int k = j + 1; k < L.s; k++)
			{
				if (L.exist(j, k))
				{
					L.remEdge(j, k);
				}
			}
		}
		ListFile << GetCounter() << ";";

		MatrixFile << endl;
		ListFile << endl;
	}








	MatrixFile.close();
	ListFile.close();
	system("pause");
	return 0;
}