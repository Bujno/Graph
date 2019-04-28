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
	L.addEdge(3, 6);
	L.addEdge(1, 6);
	L.addEdge(1, 5);
	L.addEdge(4, 2);
	L.addEdge(4, 3);

	cout << L.exist(5, 3) << endl;
	cout << L.exist(6, 2) << endl;

	M.remEdge(1, 2);
	cout << M.exist(2, 1) << endl;

	L.remEdge(3, 5);
	cout << L.exist(5, 3) << endl;

	cout << "-----------------" << endl;

	DFS <ListGraph> L_DFS(L);
	L_DFS.search(1);

	system("pause");
	return 0;
}