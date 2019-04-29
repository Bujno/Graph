#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Algorithms.h"

int main()
{
	MatrixGraph M(17);
	M.addEdge(0, 3);
	M.addEdge(0, 2);
	M.addEdge(0, 1);
	M.addEdge(2, 1);
	M.addEdge(1, 14);
	M.addEdge(14, 13);
	M.addEdge(14, 16);
	M.addEdge(13, 16);
	M.addEdge(10, 15);
	M.addEdge(15, 12);
	M.addEdge(11, 12);
	M.addEdge(4, 11);
	M.addEdge(4, 12);
	M.addEdge(9, 5);
	M.addEdge(5, 6);
	M.addEdge(8, 6);
	M.addEdge(6, 7);

	ListGraph L(7);
	L.addEdge(1, 5);
	L.addEdge(1, 4);
	L.addEdge(4, 5);
	L.addEdge(1, 0);
	L.addEdge(0, 2);
	L.addEdge(0, 3);
	L.addEdge(3, 2);
	L.addEdge(6, 2);
	L.addEdge(6, 3);

	MatrixGraph K(7);
	K.addEdge(0, 2);
	K.addEdge(0, 3);
	K.addEdge(0, 1);
	K.addEdge(1, 2);
	K.addEdge(1, 4);
	K.addEdge(4, 6);
	K.addEdge(5, 6);
	K.addEdge(4, 5);


	cout << "----------------- LIST L" << endl;

	Naive <ListGraph> L_Naive(L);
	L_Naive.bridgeSearch();
	L_Naive.show();

	BetterNaive <ListGraph> L_Naive2(L);
	L_Naive2.bridgeSearch();
	L_Naive2.show();

	Tarjan <ListGraph> L_Trojan(L);
	L_Trojan.bridgeSearch();
	L_Trojan.show();

	cout << "-----------------MARTIX  K" << endl;

	Naive <MatrixGraph> M_Naive(K);
	M_Naive.bridgeSearch();
	M_Naive.show();

	BetterNaive <MatrixGraph> M_Naive2(K);
	M_Naive2.bridgeSearch();
	M_Naive2.show();

	Tarjan <MatrixGraph> M_Naive21(K);
	M_Naive21.bridgeSearch();
	M_Naive21.show();

	cout << "-----------------MARTIX M " << endl;

	Naive <MatrixGraph> M_Naive3(M);
	M_Naive3.bridgeSearch();
	M_Naive3.show();
	
	BetterNaive <MatrixGraph> M_Naive22(M);
	M_Naive22.bridgeSearch();
	M_Naive22.show(); 

	Tarjan <MatrixGraph> Trojan_L(M);
	Trojan_L.bridgeSearch();
	Trojan_L.show();

	system("pause");
	return 0;
}