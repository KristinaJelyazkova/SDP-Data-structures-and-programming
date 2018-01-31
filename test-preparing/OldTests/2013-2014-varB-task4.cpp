//Да се напише шаблон на функция int countNodes(graph<T>& g), 
//която намира броя на върховете в графа g, които имат повече родители, отколкото деца;

#include<iostream>

int countParents(int vertex, bool G[5][5], int n) {
	int count = 0;
	for (int v = 0; v < n; v++) {
		if (G[v][vertex]) {
			count++;
		}
	}
	return count;
}

int countChildren(int vertex, bool G[5][5], int n) {
	int count = 0;
	for (int v = 0; v < n; v++) {
		if (G[vertex][v]) {
			count++;
		}
	}
	return count;
}

int coundNodes(bool G[5][5], int n) {
	int count = 0;
	for (int vertex = 0; vertex < n; vertex++) {
		if (countParents(vertex, G, n) > countChildren(vertex, G, n)) {
			count++;
		}
	}
	return count;
}

void testCountNodes() {
	bool G[5][5] = {
		0, 1, 0, 0, 1,
		1, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 0
	};

	std::cout << coundNodes(G, 5) << std::endl; 
}

//Път в ориентиран граф с числа по върховете наричаме “стълба”, 
//ако всеки връх е с единица по - голям от предходния, 
//а последният връх е два пъти по - голям от първия.
//Пример: пътят 2, 3, 4 е стълба.
//Да се напише функция LList<int> shortestLadder(graph<int>& g), 
//която намира най - късата стълба в даден граф, или връща празен списък, ако такава няма.
//При наличие на няколко най - къси стълби, да се върне някоя от тях.

struct VertexList {
	int v;
	VertexList *next;
	VertexList(int _v, VertexList *_next) : v(_v), next(_next) {}
};

VertexList* range(int fromVertex, int endVertex) {
	if (fromVertex == endVertex) {
		return new VertexList(fromVertex, nullptr);
	}
	return new VertexList(fromVertex, range(fromVertex + 1, endVertex));
}

VertexList* shortestLadderFromVertex(bool G[5][5], int n, int fromVertex) {
	if (2 * fromVertex > n - 1) {
		return false;
	}

	int crrVertex = fromVertex;
	int endVertex = 2 * fromVertex;

	bool ladderExists = true;

	while (crrVertex < endVertex && ladderExists) {
		if (!G[crrVertex][crrVertex + 1]) {
			ladderExists = false;
		}
		crrVertex++;
	}

	if (ladderExists) {
		return range(fromVertex, endVertex);
	}
	return nullptr;
}

bool isShorter(VertexList *path1, VertexList *path2) {
	if (path2 == nullptr) {
		return false;
	}
	if (path1 == nullptr) {
		return path2 != nullptr;
	}
	return isShorter(path1->next, path2->next);
}


VertexList* shortestLadder(bool G[5][5], int n) {
	VertexList* result = nullptr;
	for (int fromVertex = 1; fromVertex < n; fromVertex++) { // without 0 because 0 is always the shortest ladder
		VertexList *ladder = shortestLadderFromVertex(G, n, fromVertex);
		if (ladder != nullptr) {
			if (result == nullptr) {
				result = ladder;
			}
			else if (isShorter(ladder, result)) {
				VertexList *tmp = result;
				result = ladder;
				delete tmp;
			}
		}
	}
	return result;
}

void testShortestLadder(){
	bool G[5][5] = {
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 0, 1, 0, 0
	};

	VertexList *ladder = shortestLadder(G, 5);
	if (ladder == nullptr) {
		std::cout << "No ladder!\n";
		return;
	}
	while (ladder != nullptr) {
		std::cout << ladder->v << " ";
		ladder = ladder->next;
	}
	std::cout << std::endl;
}


int main() {
	//testCountNodes();
	testShortestLadder();

	system("pause");
	return 0;
}