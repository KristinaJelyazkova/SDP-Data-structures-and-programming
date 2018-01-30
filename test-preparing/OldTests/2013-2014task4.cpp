//Äà ñå íàïèøå øàáëîí íà ôóíêöèÿ bool singleChild(graph<T>& g, T const& a), 
//êîÿòî ïðîâåðÿâà äàëè å âÿðíî, ÷å âúðõúò a å åäèíñòâåíî äåòå íà âñè÷êèòå ñè ðîäèòåëè;

#include<iostream>
#include<vector>

bool singleChild(bool G[5][5], int n, int a) {
	for (int vertex = 0; vertex < n; vertex++) {
		if (G[vertex][a]) {
			for (int otherVertex = 0; otherVertex < n; otherVertex++) {
				if (otherVertex != a && G[vertex][otherVertex]) {
					return false;
				}
			}
		}
	}
	return true;
}

void testSingleChild(){
	bool G[5][5] = {
		0, 0, 1, 0, 0,
		1, 1, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 1, 0
	};
	std::cout << singleChild(G, 5, 2) << std::endl;
}

//Ïúò â îðèåíòèðàí ãðàô íàðè÷àìå “ëàñî”, àêî âñè÷êè âúðõîâå â íåãî ñà ðàçëè÷íè, 
//ñ èçêëþ÷åíèå íà ïîñëåäíèÿ, êîéòî ñúâïàäà ñ íÿêîé äðóã âðúõ îò ïúòÿ. 
//Ïðèìåð: ïúòÿò 1, 2, 3, 4, 2 å ëàñî. 
//Äà ñå íàïèøå øàáëîí íà ôóíêöèÿ LList<T> longestLasso(graph<T>& g), 
//êîÿòî íàìèðà íàé-äúëãîòî ëàñî â äàäåí ãðàô, èëè âðúùà ïðàçåí ñïèñúê, àêî òàêîâà íÿìà. 
//Ïðè íàëè÷èå íà íÿêîëêî íàé-äúëãè ëàñà, äà ñå âúðíå íÿêîå îò òÿõ.

struct VertexList;

struct Vertex {
	int v;
	VertexList *successors;
	Vertex *next;
	Vertex(int _v, VertexList *s, Vertex *n) : v(_v), successors(s), next(n){}
};

struct VertexList {
	int v;
	VertexList *next;
	VertexList(int _v, VertexList *_next) : v(_v), next(_next) {}
};

bool isFrom(int vertex, std::vector<int> path) {
	for (int v : path) {
		if (v == vertex) {
			return true;
		}
	}
	return false;
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

VertexList* longestLassoFromVertex(Vertex *graph, int vertex, std::vector<int> &path) {
	if (isFrom(vertex, path)) {
		return new VertexList(vertex, nullptr);
	}

	path.push_back(vertex);

	Vertex *tmp = graph;
	while (tmp != nullptr && tmp->v != vertex) {
		tmp = tmp->next;
	}

	VertexList *successors = tmp->successors;
	std::vector<int> copy = path;
	VertexList *result = nullptr;

	while (successors != nullptr) {
		VertexList *lasso = longestLassoFromVertex(graph, successors->v, path);

		if (lasso != nullptr) {
			VertexList *crrLasso = new VertexList(vertex, lasso);
			if (result == nullptr) {
				result = crrLasso;
			}
			else if (isShorter(result, crrLasso)) {
				VertexList *tmp = result;
				result = crrLasso;
				delete tmp;
			}
		}

		path = copy;
		successors = successors->next;
	}

	return result;
}

VertexList* longestLasso(Vertex *graph) {
	VertexList *result = nullptr;
	Vertex *crr = graph;

	while (crr != nullptr) {
		std::vector<int> path;
		VertexList *lasso = longestLassoFromVertex(graph, crr->v, path);
		if (lasso != nullptr) {
			if (result == nullptr) {
				result = lasso;
			}
			else if (isShorter(result, lasso)) {
				VertexList *tmp = result;
				result = lasso;
				delete tmp;
			}
		}
		crr = crr->next;
	}
	return result;
}

void testLongestLasso() {
	VertexList *of0 = new VertexList(2, nullptr);
	VertexList *of1 = new VertexList(1,
		new VertexList(0, nullptr));
	VertexList *of2 = new VertexList(1, nullptr);
	VertexList *of3 = new VertexList(2, nullptr);
	VertexList *of4 = new VertexList(0,
		new VertexList(3, nullptr));
	Vertex *graph = new Vertex(1, of1,
		new Vertex(2, of2,
			new Vertex(4, of4,
				new Vertex(3, of3, 
					new Vertex(0, of0, nullptr)))));

	VertexList *lasso = longestLasso(graph);
	if (lasso == nullptr) {
		std::cout << "No lasso!\n";
		return;
	}
	while (lasso != nullptr) {
		std::cout << lasso->v << " ";
		lasso = lasso->next;
	}
	std::cout << std::endl;
}


int main() {
	//testSingleChild();
	testLongestLasso();

	system("pause");
	return 0;
}
