// да се напише следната функция: createGraph, която създава графа по зададен
//списък от ребра, представени като наредени двойки от възли

#include<iostream>
#include<fstream>
#include<vector>
#include<set>

struct VertexList;

struct Vertex {
	int v;
	VertexList *successors;
	Vertex *next;
	Vertex(int _v, VertexList *_s, Vertex *_n) : v(_v), successors(_s), next(_n) {};
};

struct VertexList{
	int v;
	VertexList *next;
	VertexList(int _v, VertexList *_next) : v(_v), next(_next) {}
};

Vertex* locate(Vertex *graph, int v) {
	Vertex *crr = graph;
	while (crr != nullptr) {
		if (crr->v == v) {
			return crr;
		}
		crr = crr->next;
	}
	return nullptr;
}

void addEdge(Vertex *&graph, int from, int to) {
	Vertex *To = locate(graph, to);
	if (To == nullptr) {
		graph = new Vertex(to, nullptr, graph);
	}
	Vertex *From = locate(graph, from);
	if(From == nullptr) {
		graph = new Vertex(from, new VertexList(to, nullptr), graph);
	}
	else {
		From->successors = new VertexList(to, From->successors);
	}
}

void createGraphHelp(Vertex *&graph, std::vector<std::pair<int, int>> edges) {
	for (std::pair<int, int> edge : edges) {
		addEdge(graph, edge.first, edge.second);
	}
}

Vertex* createGraph(std::vector<std::pair<int, int>> edges) {
	Vertex *graph = nullptr;
	createGraphHelp(graph, edges);
	return graph;
}

void printDottyHelp(std::ostream& out, Vertex *crr, std::set<int> &visited, Vertex *graph) {
	if (crr == nullptr) {
		return;
	}
	if (visited.count(crr->v) > 0) {
		return;
	}
	visited.insert(crr->v);
	VertexList *succ = crr->successors;
	while (succ != nullptr) {
		out << crr->v << "->" << succ->v << ";\n";
		succ = succ->next;
	}
	succ = crr->successors;
	while (succ != nullptr) {
		Vertex *s = locate(graph, succ->v);
		printDottyHelp(out, s, visited, graph);
		succ = succ->next;
	}
}

void printDotty(std::ostream& out, Vertex *graph) {
	std::set<int> visited;
	printDottyHelp(out, graph, visited, graph);
}

//двупосочен път в ориентиран граф наричаме път, в който всяко ребро има обратно, 
//т.е. огледалният образ на пътя също е път в графа. 
//Да се напише функция maxTwoWayFrom, която за даден граф g намира двупосовен 
//ацикличен път с максимална дължина, започващ от даден възел n

bool isEdge(Vertex *graph, int from, int to) {
	Vertex *From = locate(graph, from);
	VertexList *succ = From->successors;
	while (succ != nullptr) {
		if (succ->v == to) {
			return true;
		}
	    succ = succ->next;
	}
	return false;
}

bool isShorter(VertexList *a, VertexList *b) {
	if (b == nullptr) {
		return false;
	}
	if (a == nullptr) {
		return true;
	}
	return isShorter(a->next, b->next);
}

void del(VertexList *l) {
	if (l == nullptr) {
		return;
	}
	VertexList *tmp = l;
	del(l->next);
	delete tmp;
}

VertexList* maxTwoWayFromHelp(Vertex *graph, int from, std::set<int> visited) {
	if (visited.count(from) > 0) {
		return nullptr;
	}
	visited.insert(from);

	VertexList *result = nullptr;

	Vertex *From = locate(graph, from);
	VertexList *succ = From->successors;
	//std::set<int> copy = visited;

	while (succ != nullptr) {
		if (isEdge(graph, succ->v, from)) {
			VertexList *newTwoWay = maxTwoWayFromHelp(graph, succ->v, visited);
			if (newTwoWay != nullptr) {
				if (result == nullptr) {
					result = new VertexList(from, newTwoWay);
				}
				else {
					VertexList *newResult = new VertexList(from, newTwoWay);
					if (isShorter(result, newResult)) {
						VertexList *tmp = result;
						result = newResult;
						del(tmp);
					}
				}
			}
		}
		//visited = copy;
		succ = succ->next;
	}

	visited.erase(from);
	if (result == nullptr) {
		return new VertexList(from, nullptr);
	}
	return result;
}

VertexList* maxTwoWayFrom(Vertex *graph, int n) {
	std::set<int> visited;
	return maxTwoWayFromHelp(graph, n, visited);
}

void testCreateGraph() {
	std::vector<std::pair<int, int>> edges;
	edges.push_back({ 2,5 });
	edges.push_back({ 4,1 });
	edges.push_back({ 0,5 });
	edges.push_back({ 4,2 });
	edges.push_back({ 5,2 });
	edges.push_back({ 2,4 });
	edges.push_back({ 5,0 });
	edges.push_back({ 1,4 });
	edges.push_back({ 2,1 });
	edges.push_back({ 1,0 });
	edges.push_back({ 5,1 });
	edges.push_back({ 0,3 });
	edges.push_back({ 3,0 });

	Vertex *graph = createGraph(edges);
	std::ofstream out("graph.dot");
	out << "digraph G {\n";
	printDotty(out, graph);
	out << "}\n";

	VertexList *maxTwoWay = maxTwoWayFrom(graph, 2);
	if (maxTwoWay == nullptr) {
		std::cout << "No such way!";
	}
	VertexList *crr = maxTwoWay;
	while (crr != nullptr) {
		std::cout << crr->v << " ";
		crr = crr->next;
	}
	std::cout << std::endl;
}

int main() {
	testCreateGraph();

	system("pause");
	return 0;
}
