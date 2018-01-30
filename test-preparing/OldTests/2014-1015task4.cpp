#include<iostream>
#include<vector>

//Äàäåí å îðèåíòèðàí ãðàô G, ïðåäñòàâåí ÷ðåç ñïèñúê îò íàñëåäíèöè.

struct VertexList;

struct Vertex {
	int u;
	VertexList *successors;
	Vertex *next;
	Vertex(int _u, VertexList *_suc, Vertex *_next) : u(_u), successors(_suc), next(_next) {}
};

struct VertexList {
	int v;
	VertexList *next;
	VertexList(int _v, VertexList *_next) : v(_v), next(_next) {}
};

bool isMarked(int vertex, std::vector<int> marked) {
	for (int crr : marked) {
		if (vertex == crr) {
			return true;
		}
	}
	return false;
}

//â ãðàôà G ñúùåñòâóâà ïúò îò b äî a, êîéòî âêëþ÷âà ñàìî è åäèíñòâåíî âúðõîâå îò ïúòÿ p.
bool hasPath(int from, int to, std::vector<int> path, Vertex *graph, std::vector<int> &marked) {
	if (isMarked(from, marked)) {
		return false;
	}
	if (!isMarked(from, path)) {
		return false;
	}
	if (from == to) {
		return true;
	}
	marked.push_back(from);
	Vertex *crrVertex = graph;
	while (crrVertex != nullptr && crrVertex->u != from) {
		crrVertex = crrVertex->next;
	}

	std::vector<int> copy = marked;
	VertexList *successors = crrVertex->successors;
	while (successors != nullptr) {
		if (hasPath(successors->v, to, path, graph, marked)) {
			return true;
		}
		marked = copy;
		successors = successors->next;
	}
	return false;
}

bool hasReversePath(std::vector<int> path, Vertex *graph) {
	std::vector<int> marked;
	return hasPath(path.back(), path[0], path, graph, marked);
}

VertexList* pathHelp(int from, int to, Vertex *graph, std::vector<int> &marked) {
	if (isMarked(from, marked)) {
		return nullptr;
	}

	marked.push_back(from);
	if (from == to) {
		if (hasReversePath(marked, graph)) {
			return new VertexList(from, nullptr);
		}
		return nullptr;
	}
	
	Vertex *crrVertex = graph;
	while (crrVertex->u != from) {
		crrVertex = crrVertex->next;
	}

	std::vector<int> copy = marked;

	VertexList *successors = crrVertex->successors;

	while (successors != nullptr) {
		VertexList *newPath = pathHelp(successors->v, to, graph, marked);
		if (newPath != nullptr) {
			VertexList *path = new VertexList(from, newPath);
			return path;
		}
		marked = copy;
		successors = successors->next;
	}

	return nullptr;
}

//Äà ñå íàìåðè àöèêëè÷åí ïúò p îò a äî b, çà êîéòî å èçïúëíåíî ñëåäíîòî óñëîâèå : 
//â ãðàôà G ñúùåñòâóâà ïúò îò b äî a, êîéòî âêëþ÷âà ñàìî è åäèíñòâåíî âúðõîâå îò ïúòÿ p.
//Àêî òàêúâ ïúò íå ñúùåñòâóâà, äà ñå âúðíå ïðàçåí ïúò.
VertexList* path(int from, int to, Vertex *graph) {
	std::vector<int> marked;
	return pathHelp(from, to, graph, marked);
}

void testPath() {
	VertexList *of1 = new VertexList(3,
		new VertexList(6,
			new VertexList(5, nullptr)));
	VertexList *of2 = new VertexList(5,
		new VertexList(7, nullptr));
	VertexList *of3 = new VertexList(5, nullptr);
	VertexList *of5 = nullptr;
	VertexList *of4 = new VertexList(1,
		new VertexList(3,
			new VertexList(5, nullptr)));
	VertexList *of6 = new VertexList(4, 
		new VertexList(2, nullptr));
	VertexList *of7 = new VertexList(6,
		new VertexList(7, nullptr));
	Vertex *graph = new Vertex(3, of3,
		new Vertex(2, of2,
			new Vertex(4, of4,
				new Vertex(1, of1,
					new Vertex(5, of5,
						new Vertex(7, of7,
							new Vertex(6, of6, nullptr)))))));
	VertexList *Path = path(2, 1, graph);
	if (Path == nullptr) {
		std::cout << "No such path!\n";
	}
	else {
		while (Path != nullptr) {
			std::cout << Path->v << " ";
			Path = Path->next;
		}
	}
}


int main() {
	testPath();

	system("pause");
	return 0;
}
