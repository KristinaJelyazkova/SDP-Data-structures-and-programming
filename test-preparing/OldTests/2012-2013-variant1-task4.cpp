//Дадени са граф g и два негови върха a и b.Да се напише програма, която намира(ако съществува) такъв връх на g, 
//който е различен от a и  b и принадлежи на всеки ацикличен път от a до b.

#include<iostream>
#include<vector>

bool isVisited(int vertex, std::vector<int> visited) {
	for (int v : visited) {
		if (v == vertex) {
			return true;
		}
	}
	return false;
}

bool hasPathWithoutVertex(bool G[7][7], int n, int a, int b, int vertex, std::vector<int> &visited) {
	if (a == b) {
		return true;
	}
	if (isVisited(a, visited)) {
		return false;
	}
	if (a == vertex) {
		return false;
	}
	visited.push_back(a);
	std::vector<int> copy = visited;
	for (int nextVertex = 0; nextVertex < n; nextVertex++) {
		if (G[a][nextVertex] && hasPathWithoutVertex(G, n, nextVertex, b, vertex, visited)) {
			return true;
		}
		visited = copy;
	}
	return false;
}

int VertexFromEveryPath(bool G[7][7], int n, int a, int b) {
	for (int vertex = 0; vertex < n; vertex++) {
		if (vertex != a && vertex != b) {
			/*bool *saveRow = new bool[n];
			for (int i = 0; i < n; i++) {
				saveRow[i] = G[vertex][i];
				G[vertex][i] = false;
			}*/
			std::vector<int> visited;
			if (!hasPathWithoutVertex(G, n, a, b, vertex, visited)) {
				return vertex;
			}
		}
	}
	return -1;
}

void testVertexFromEveryPath() {
	bool G[7][7] = {
		0, 0, 1, 0, 0, 0, 1,
		0, 1, 0, 1, 0, 1, 0,
		0, 0, 1, 0, 0, 0, 1,
		0, 1, 0, 0, 1, 0, 0,
		0, 1, 0, 0, 0, 1, 0,
		1, 0, 1, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0
	};

	std::cout << VertexFromEveryPath(G, 7, 3, 6) << std::endl;
}

/*int main() {
	testVertexFromEveryPath();

	system("pause");
	return 0;
}*/

