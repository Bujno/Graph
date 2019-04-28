#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Algorithms.h"

int main()
{
	MatrixGraph M(4);
	M.addEdge(1, 0);
	M.addEdge(2, 1);

	cout << M.exist(1, 2) << endl;

	ListGraph L(7);
	L.addEdge(5, 3);
	L.addEdge(1, 5);
	L.addEdge(1, 4);
	L.addEdge(4, 5);
	L.addEdge(1, 0);
	L.addEdge(0, 2);
	L.addEdge(0, 3);
	L.addEdge(3, 2);
	L.addEdge(6, 2);
	L.addEdge(6, 3);

	cout << L.exist(5, 3) << endl;
	cout << L.exist(6, 2) << endl;

	M.remEdge(1, 2);
	cout << M.exist(2, 1) << endl;

	L.remEdge(3, 5);
	cout << L.exist(5, 3) << endl;

	cout << "-----------------" << endl;

	DFSClass <ListGraph> L_DFS(L);
	L_DFS.search(1);
	L_DFS.show();

	Naive <ListGraph> L_Naive(L);
	L_Naive.bridgeSearch();
	L_Naive.show();

	system("pause");
	return 0;
}