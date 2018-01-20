#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<queue>

void numberOfPathsFrom(std::vector<char> **G, int n, int state, 
						std::string word, int index, int &count) {
	if (index == word.length()) {
		count++;
		return;
	}
	for (int nextState = 0; nextState < n; nextState++) {
		for (char symbol : G[state][nextState]) {
			if (symbol == word[index]) {
				numberOfPathsFrom(G, n, nextState, word, index + 1, count);
			}
		}
	}
}

int numberOfPaths(std::vector<char> **G, int n, std::string word) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		numberOfPathsFrom(G, n, i, word, 0, count);
	}
	return count;
}

void testNumberOfPaths(){
	std::vector<char> **G;
	G = new std::vector<char>*[5];
	for (int i = 0; i < 5; i++) {
		G[i] = new std::vector<char>[5];
	}
	std::vector<char> empty;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			G[i][j] = empty;
		}
	}

	G[0][0].push_back('i');
	G[0][0].push_back('v');
	G[0][0].push_back('o');

	G[1][4].push_back('i');

	G[1][3].push_back('i');
	G[1][3].push_back('v');

	G[2][1].push_back('o');

	G[3][2].push_back('v');
	G[3][4].push_back('v');

	G[4][4].push_back('o');
	G[4][2].push_back('o');
	G[4][2].push_back('v');

	std::cout << numberOfPaths(G, 5, "ivo") << std::endl;
}

struct TreeNode {
	static int maxID;
	int ID;
	int data;
	std::vector<TreeNode*> children;
	TreeNode(int _data, std::vector<TreeNode*> _children) :
		data(_data), children(_children){
		ID = maxID;
		maxID++;
	}
};

int TreeNode::maxID = 0;

TreeNode* makeTree(bool **G, int n, int state, int k) {
	if (k <= 0) {
		return nullptr;
	}
	std::vector<TreeNode*> children;
	for (int nextState = 0; nextState < n; nextState++) {
		TreeNode* child = nullptr;
		if (G[state][nextState]) {
			child = makeTree(G, n, nextState, k - 1);
		}
		children.push_back(child);
	}
	return new TreeNode(state, children);
}

void dottyPrint(std::ostream& out, TreeNode *crr) {
	out << crr->ID << "[label=\"" << crr->data << "\"];" << std::endl;
	for (TreeNode *child : crr->children) {
		if (child != nullptr) {
			out << crr->ID << "->" << child->ID << std::endl;
		}
	}
	for (TreeNode *child : crr->children) {
		if (child != nullptr) {
			dottyPrint(out, child);
		}
	}
}

void testMakeTree() {
	bool **G = new bool*[17];
	for (int i = 0; i < 17; i++) {
		G[i] = new bool[17];
		for (int j = 0; j < 17; j++) {
			G[i][j] = false;
		}
	}
	G[0][1] = true;
	G[1][4] = true;
	G[2][1] = true;
	G[2][4] = true;
	G[3][4] = true;
	G[4][5] = true;
	G[4][6] = true;
	G[4][7] = true;
	G[5][9] = true;
	G[6][9] = true;
	G[6][10] = true;
	G[7][6] = true;
	G[7][8] = true;
	G[8][10] = true;
	G[9][11] = true;
	G[9][12] = true;
	G[9][13] = true;
	G[10][14] = true;
	G[11][12] = true;
	G[12][16] = true;
	G[14][13] = true;
	G[14][15] = true;

	TreeNode *tree = makeTree(G, 17, 4, 4);

	std::ofstream out("treeFromGraph.dot");
	out << "digraph G {" << std::endl;
	dottyPrint(out, tree);
	out << "}" << std::endl;
}

bool isFrom(int state, std::vector<int> marked) {
	for (int crr : marked) {
		if (crr == state) {
			return true;
		}
	}
	return false;
}

bool hasPath(bool **G, int n, int fromState, int toState, std::vector<int> &marked) {
	if (G[fromState][toState]) {
		return true;
	}
	marked.push_back(fromState);
	for (int nextState = 0; nextState < n; nextState++) {
		if (!isFrom(nextState, marked)) {
			if (G[fromState][nextState] && hasPath(G, n, nextState, toState, marked)) {
				return true;
			}
		}
	}
	return false;
}

bool topolSort(bool **G, int n, std::vector<int> &v) {
	if (v.size() <= 1) {
		return true;
	}
	bool flag;
	std::vector<int> marked;
	for (int i = 0; i < v.size(); i++) {
		flag = true;
		for (int toState : v) {
			if (hasPath(G, n, v[i], toState, marked)) {
				flag = false;
				break;
			}
		}
		if (flag) {
			int last = v[i];
			v.erase(v.begin() + i);
			if (topolSort(G, n, v)) {
				v.push_back(last);
				return true;
			}
		}
	}
	return false;
}

void testTopolSort() {
	bool **G = new bool*[9];
	for (int i = 0; i < 9; i++) {
		G[i] = new bool[9];
		for (int j = 0; j < 9; j++) {
			G[i][j] = false;
		}
	}

	G[0][1] = true;
	G[0][8] = true;
	G[1][3] = true;
	G[1][7] = true;
	G[1][6] = true;
	G[2][8] = true;
	G[4][0] = true;
	G[4][7] = true;
	G[5][4] = true;
	G[5][0] = true;
	G[5][4] = true;
	G[5][4] = true;
	G[5][4] = true;
	G[7][3] = true;
	G[8][7] = true;

	std::vector<int> v;
	for (int i = 0; i < 9; i++) {
		v.push_back(i);
	}

	topolSort(G, 9, v);
	for (int state : v) {
		std::cout << state << " ";
	}
	std::cout << std::endl;
}

bool areNeighbours(int Xrow, int Xcol, int Yrow, int Ycol) {
	return (abs(Xrow - Yrow) == 1 && (Xcol == Ycol))
		|| (abs(Xcol - Ycol) == 1 && (Xrow == Yrow));
}

bool** makeGraph(bool **L, int n) {
	int size = n * n;
	bool **G = new bool*[size];
	for (int i = 0; i < size; i++) {
		G[i] = new bool[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (L[i / n][i % n] && L[j / n][j % n] && 
					areNeighbours(i / n, i % n, j / n, j % n)) {
				G[i][j] = true;
			}
			else {
				G[i][j] = false;
			}
		}
	}
	return G;
}

int countConnectedComponents(bool **G, int n, std::vector<int> &allVertexes) {
	if (allVertexes.empty()){ 
		return 0;
	}
	if (allVertexes.size() == 1) {
		return 1;
	}
	int vertex = allVertexes[allVertexes.size() - 1];
	for (int i = 0; i < allVertexes.size() - 1; i++) {
		std::vector<int> marked;
		if (hasPath(G, n, vertex, allVertexes[i], marked)) {
			allVertexes.erase(allVertexes.begin() + i);
			i--;
		}
	}
	allVertexes.erase(allVertexes.begin() + allVertexes.size() - 1);
	return 1 + countConnectedComponents(G, n, allVertexes);
}

#define SENTINEL INT_MAX

int countConnectedComponents2(bool **G, int n) {
	int count = 0;

	std::queue<int> marked;
	marked.push(0);
	std::vector<int> v;
	v.push_back(0);

	while (v.size() < n) {
		while (!marked.empty()) {
			int vertex = marked.front();
			marked.pop();
			for (int nextVertex = 0; nextVertex < n; nextVertex++) {
				if (!isFrom(nextVertex, v) && G[vertex][nextVertex]) {
					marked.push(nextVertex);
					v.push_back(nextVertex);
				}
			}
		}
		count++;
		if (v.size() == n - 1) {
			count++;
			return count;
		}
		for (int vertex = 0; vertex < n; vertex++) {
			if (!isFrom(vertex, v)) {
				marked.push(vertex);
				v.push_back(vertex);
				break;
			}
		}
	}
	return count;
}

void testMakeGraph() {
	bool **L = new bool*[3];
	for (int i = 0; i < 3; i++) {
		L[i] = new bool[3];
		for (int j = 0; j < 3; j++) {
			L[i][j] = true;
		}
	}
	/*bool L[3][3] = {
		1, 0, 1,
		1, 0, 1,
		1, 1, 0
	};*/

	L[0][1] = false;
	L[1][1] = false;
	L[2][2] = false;

	bool **G = new bool*[9];
	for (int i = 0; i < 9; i++) {
		G[i] = new bool[9];
		for (int j = 0; j < 9; j++) {
			G[i][j] = false;
		}
	}
	G = makeGraph(L, 3);
	
	std::ofstream out("graph-from-labirint.dot");
	out << "digraph G {" << std::endl;
	for (int i = 0; i < 9; i++) {
		out << i;
		if (!L[i / 3][i % 3]) {
			out << "[style=\"" << "filled" << "\"];";
		}
		out << std::endl;
		for (int j = 0; j < 9; j++) {
			if (G[i][j])
				out << i << "->" << j << std::endl;
		}
	}
	out << "}" << std::endl;

	std::vector<int> allVertexes;
	for (int i = 0; i < 9; i++) {
		allVertexes.push_back(i);
	}
	std::cout << countConnectedComponents(G, 9, allVertexes) << std::endl;
	std::cout << countConnectedComponents2(G, 9) << std::endl;
	//std::vector<int> marked;
	//std::cout << hasPath(G, 9, 7, 1, marked);
}

bool hasKPath(bool **G, int n, int fromVertex, int toVertex, int k) {
	if (k == 0) {
		return fromVertex == toVertex;
	}
	for (int vertex = 0; vertex < n; vertex++) {
		if (G[fromVertex][vertex] && hasKPath(G, n, vertex, toVertex, k - 1)) {
			return true;
		}
	}
	return false;
}

bool hasKCycle(bool **G, int n, int k) {
	for (int fromVertex = 0; fromVertex < n; fromVertex++) {
		if (hasKPath(G, n, fromVertex, fromVertex, k)) {
			return true;
		}
	}
	return false;
}

void testHasKCycle() {
	bool **G = new bool*[5];
	for (int i = 0; i < 5; i++) {
		G[i] = new bool[5];
		for (int j = 0; j < 5; j++) {
			G[i][j] = false;
		}
	}
	G[0][1] = G[1][0] = G[0][4] = G[4][0] = true;
	std::cout << hasKCycle(G, 5, 4) << std::endl;
	std::cout << hasKCycle(G, 5, 3) << std::endl;
	std::cout << hasKCycle(G, 5, 2) << std::endl;
	std::cout << hasKCycle(G, 5, 5) << std::endl;
	G[1][4] = G[4][3] = G[3][2] = G[2][0] = true;
	std::cout << hasKCycle(G, 5, 5) << std::endl;
	std::cout << hasKCycle(G, 5, 6) << std::endl;
}

int main() {
	//testNumberOfPaths();
	//testMakeTree();
	//testTopolSort();
	//testMakeGraph();
	testHasKCycle();

	system("pause");
	return 0;
}