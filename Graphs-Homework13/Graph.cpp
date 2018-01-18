#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>

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

bool hasPath(bool **G, int n, int fromState, int toState) {
	if (G[fromState][toState]) {
		return true;
	}
	for (int nextState = 0; nextState < n; nextState++) {
		if (G[fromState][nextState] && hasPath(G, n, nextState, toState)) {
			return true;
		}
	}
	return false;
}

bool topolSort(bool **G, int n, std::vector<int> &v) {
	if (v.size() <= 1) {
		return true;
	}
	bool flag;
	for (int i = 0; i < v.size(); i++) {
		flag = true;
		for (int toState : v) {
			if (hasPath(G, n, v[i], toState)) {
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
}

int main() {
	//testNumberOfPaths();
	//testMakeTree();
	//testTopolSort();
	testMakeGraph();

	system("pause");
	return 0;
}