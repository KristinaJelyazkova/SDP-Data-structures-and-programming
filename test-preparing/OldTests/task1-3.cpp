#include<iostream>
#include<vector>

struct Node {
	int x;
	Node *left, *right;
	Node(int _x, Node *_left, Node *_right) : x(_x), left(_left), right(_right) {}
};

bool complement(const Node * const t1, const Node * const t2) {
	if (t2 == nullptr) {
		return true;
	}
	if (t1 == nullptr) {
		return false;
	}
	return (t1->x == t2->x)
		&& complement(t1->left, t2->left)
		&& complement(t1->right, t2->right);
}

struct VertexList;

struct Vertex {
	int u;
	VertexList *successors;
	Vertex *next;
	Vertex(int _u, VertexList *_suc, Vertex *_next) : u(_u), successors(_suc), next(_next){}
};

struct VertexList {
	int v;
	VertexList *next;
	VertexList(int _v, VertexList *_next) : v(_v), next(_next){}
};

bool isFrom(int x, std::vector<int> v) {
	for (int y : v) {
		if (x == y) {
			return true;
		}
	}
	return false;
}

bool shorterThan(VertexList *vl1, VertexList *vl2) {
	if (vl1 == nullptr) {
		return vl2 != nullptr;
	}
	if (vl2 == nullptr) {
		return false;
	}
	return shorterThan(vl1->next, vl2->next);
}

VertexList* longestPathHelp(Vertex *graph, int u, int v, std::vector<int> &marked) {
	if (u == v) {
		return new VertexList(v, nullptr);
	}

	if (isFrom(u, marked)) {
		return nullptr;
	}

	Vertex *tmp = graph;
	while (tmp->u != u) {
		tmp = tmp->next;
	}
	marked.push_back(u);

	VertexList *suc = tmp->successors;
	if (suc == nullptr) {
		return nullptr;
	}

	VertexList *longest = nullptr;
	std::vector<int>  copy = marked;
	while (suc != nullptr) {
		//marked.push_back(suc->v);
		VertexList *path = longestPathHelp(graph, suc->v, v, marked);
		marked = copy;
		if (path != nullptr) {
			if (longest == nullptr) {
				longest = new VertexList(u,path);
			}
			else {
				if (shorterThan(longest->next, path)) {
					longest = new VertexList(u, path);
				}
			}
		}
		suc = suc->next;
	}
	return longest;
}

VertexList* longestPath(Vertex *graph, int u, int v) {
	std::vector<int> marked;
	VertexList *result = longestPathHelp(graph, u, v, marked);
	return result;
}

struct Elem {
	int x;
	Elem *next;
	Elem(int _x, Elem *_next) : x(_x), next(_next) {}
};

void combineSum(Elem **lists, int n, Elem *&L) {
	int sum = 0;
	bool flag = false;
	Elem **tmp = lists;
	for (int i = 0; i < n; i++) {
		if (tmp[i] != nullptr) {
			flag = true;
			sum += tmp[i]->x;
			tmp[i] = tmp[i]->next;
		}
	}
	if (!flag) {
		L = nullptr;
		return;
	}
	L = new Elem(sum, nullptr);
	combineSum(tmp, n, L->next);
}

void testComplement() {
	Node *tree1 = new Node(1,
		new Node(5, nullptr, nullptr),
		new Node(7, nullptr,
			new Node(8, nullptr, nullptr)));
	Node *tree2 = new Node(1,
		new Node(5, 
			new Node(9, nullptr, nullptr), 
			new Node(10, nullptr, nullptr)),
		new Node(7, nullptr,
			new Node(8, nullptr, nullptr)));
	std::cout << complement(tree1, tree2) << std::endl;
	std::cout << complement(tree2, tree1) << std::endl;
	std::cout << complement(tree1, tree1) << std::endl;
}

void testLongestPath() {
	VertexList *of1 = new VertexList(13,
		new VertexList(10,
			new VertexList(2, nullptr)));
	VertexList *of2 = new VertexList(13,
		new VertexList(10, nullptr));
	VertexList *of13 = new VertexList(15, nullptr);
	VertexList *of10 = nullptr;
	VertexList *of15 = new VertexList(10, 
		new VertexList(13, 
			new VertexList(1, nullptr)));
	Vertex *graph = new Vertex(10, of10,
		new Vertex(2, of2,
			new Vertex(13, of13,
				new Vertex(1, of1,
					new Vertex(15, of15, nullptr)))));
	VertexList *longest = longestPath(graph, 1, 10);
	while (longest != nullptr) {
		std::cout << longest->v << " ";
		longest = longest->next;
	}
	std::cout << std::endl;
}

void testCombineSum() {
	const int n = 5;
	Elem **lists = new Elem*[n];
	lists[3] = nullptr;
	lists[0] = new Elem(1,
		new Elem(3,
			new Elem(5,
				new Elem(10, nullptr))));
	lists[1] = new Elem(2, nullptr);
	lists[2] = new Elem(7,
		new Elem(8,
			new Elem(9,nullptr)));
	lists[4] = new Elem(11,
		new Elem(12,nullptr));
	Elem *L;
	combineSum(lists, n, L);
	while (L != nullptr) {
		std::cout << L->x << " ";
		L = L->next;
	}
	std::cout << std::endl;
}

int main() {
	//testComplement();
	//testLongestPath();
	testCombineSum();

	system("pause");
	return 0;
}
