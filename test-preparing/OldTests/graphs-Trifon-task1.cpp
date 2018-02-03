//По даден ориентиран непретеглен граф :

#include<iostream>
#include<set>

struct VertexList;

struct Vertex {
	int v;
	VertexList *successors;
	Vertex *next;
	Vertex(int _v, VertexList *s, Vertex *n) : v(_v), successors(s), next(n) {}
};

struct VertexList {
	int v;
	VertexList *next;
	VertexList(int _v, VertexList *_next) : v(_v), next(_next) {}
};

//да се провери има ли примки в графа

bool loop(Vertex *graph) {
	Vertex *vertex = graph;
	while (vertex != nullptr) {
		VertexList *successors = vertex->successors;
		while (successors != nullptr) {
			if (vertex->v == successors->v) {
				return true;
			}
			successors = successors->next;
		}
		vertex = vertex->next;
	}
	return false;
}

template<class T>
int size(T *l) {
	T *crr = l;
	int size = 0;
	while (crr != nullptr) {
		crr = crr->next;
		size++;
	}
	return size;
}

//да се провери дали графът е пълен (всеки връх е свързан с всички останали)
bool isFull(Vertex *graph) {
	int numberOfVertexes = size<Vertex>(graph);
	Vertex *vertex = graph;
	while (vertex != nullptr) {
		if (size<VertexList>(vertex->successors) + 1 != numberOfVertexes) {
			return false;
		}
		vertex = vertex->next;
	}
	return true;
}

bool edge(Vertex *graph, int u, int v) {
	Vertex *vertex = graph;
	while (vertex != nullptr) {
		if (vertex->v == u) {
			VertexList *successors = vertex->successors;
			while (successors != nullptr) {
				if (successors->v == v) {
					return true;
				}
				successors = successors->next;
			}
			return false;
		}
		vertex = vertex->next;
	}
}

//да се провери дали графът всъщност е неориентиран(т.е.има ребро между А и Б
//тогава и само тогава, когато има ребро между Б и А)
bool unoriented(Vertex *graph) {
	Vertex *vertex = graph;
	while (vertex != nullptr) {
		VertexList *successors = vertex->successors;
		while (successors != nullptr) {
			if (!edge(graph, successors->v, vertex->v)) {
				return false;
			}
			successors = successors->next;
		}
		vertex = vertex->next;
	}
	return true;
}

VertexList* helper(std::set<int> vertexes, std::set<int> without) {
	VertexList *result = nullptr, *crr = nullptr;
	bool flag = true;
	for (int v : vertexes) {
		if (without.count(v) == 0) {
			if (flag) {
				result = new VertexList(v, nullptr);
				crr = result;
				flag = false;
			}
			else {
				crr->next = new VertexList(v, nullptr);
				crr = crr->next;
			}
		}
	}
	return result;
}

Vertex* dopulnenieHelp(Vertex *graph, std::set<int> vertexes) {
	if (graph == nullptr) {
		return nullptr;
	}
	std::set<int> suc;
	VertexList *successors = graph->successors;
	while (successors != nullptr) {
		suc.insert(successors->v);
		successors = successors->next;
	}
	VertexList *newSuccessors = helper(vertexes, suc);
	return new Vertex(graph->v, newSuccessors, dopulnenieHelp(graph->next, vertexes));
}

//да се построи граф, допълнение на дадения
Vertex* dopulnenie(Vertex *graph) {
	std::set<int> vertexes;
	Vertex *vertex = graph;
	while (vertex != nullptr) {
		vertexes.insert(vertex->v);
		vertex = vertex->next;
	}
	return dopulnenieHelp(graph, vertexes);
}

void testLoop() {
	VertexList *of0 = new VertexList(2, nullptr);
	VertexList *of1 = new VertexList(1,
		new VertexList(0, nullptr));
	VertexList *of2 = new VertexList(1, nullptr);
	VertexList *of3 = new VertexList(2, nullptr);
	VertexList *of4 = new VertexList(0,
		new VertexList(3, nullptr));
	/*VertexList *of0 = new VertexList(2,
		new VertexList(3,
			new VertexList(4,
				new VertexList(1, nullptr))));
	VertexList *of1 = new VertexList(2,
		new VertexList(3,
			new VertexList(4,
				new VertexList(0, nullptr))));
	VertexList *of2 = new VertexList(1,
		new VertexList(3,
			new VertexList(4,
				new VertexList(0, nullptr))));
	VertexList *of3 = new VertexList(1,
		new VertexList(2,
			new VertexList(4,
				new VertexList(0, nullptr))));
	VertexList *of4 = new VertexList(1,
		new VertexList(2,
			new VertexList(3, 
				new VertexList(0, nullptr))));*/
	Vertex *graph = new Vertex(1, of1,
		new Vertex(2, of2,
			new Vertex(4, of4,
				new Vertex(3, of3,
					new Vertex(0, of0, nullptr)))));

	std::cout << loop(graph) << std::endl;
	std::cout << isFull(graph) << std::endl;
	std::cout << unoriented(graph) << std::endl;

	Vertex *dop = dopulnenie(graph);
	std::cout << edge(dop, 2, 3) << std::endl;
	std::cout << edge(dop, 0, 1) << std::endl;
	std::cout << edge(dop, 4, 4) << std::endl;
	std::cout << edge(dop, 0, 2) << std::endl;
	std::cout << edge(dop, 4, 3) << std::endl;
}

/*int main() {
	testLoop();

	system("pause");
	return 0;
}*/