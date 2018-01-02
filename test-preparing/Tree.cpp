#include"Tree.h"
#include<vector>
#include<cassert>

template<class T>
int TreeNode<T>::maxID = 0;

template<class T>
TreeNode<T>::TreeNode(const T& _data, TreeNode<T>* _left, TreeNode<T>* _right) :
		data(_data), left(_left), right(_right) {
	id = maxID;
	maxID++;
}

template<class T>
int TreeNode<T>::getID() {
	return id;
}

template<class T>
Tree<T>::Tree() : root(nullptr) {}

template<class T>
Tree<T>::Tree(const T data, Tree<T> leftTree, Tree<T> rightTree) {
	root = new TreeNode<T>(data, leftTree.root, rightTree.root);
}

template <class T>
void printNodesLISP(std::ostream& out, TreeNode<T> *root) {
	if (root == nullptr) {
		out << "()";
		return;
	}
	out << "(" << root->data;
	printNodesLISP(out, root->left);
	printNodesLISP(out, root->right);
	out << ")";
}

template <class T>
void printNodesDotty(std::ostream& out, TreeNode<T> *root) {
	if (root == nullptr) {
		return;
	}
	out << root->getID() << "[label=\"" << root->data << "\"];" << std::endl;
	if (root->left != nullptr) {
		out << root->getID() << "->" << root->left->getID() << "[color = \"red\"]" << ";" << std::endl;
	}
	if (root->right != nullptr) {
		out << root->getID() << "->" << root->right->getID() << ";" << std::endl;
	}
	printNodesDotty(out, root->left);
	printNodesDotty(out, root->right);
}

template<class T>
std::ostream& operator<<(std::ostream& out, Tree<T>& tree) {
	tree.print(out);
	return out;
}

template<class T>
void Tree<T>::print(std::ostream& out) {
	out << "digraph G {" << std::endl;
	printNodesDotty(out, root);
	out << "}" << std::endl;
}

template<class T>
bool Tree<T>::insertElement(std::string trace, const T& data) {
	return insertElement(trace, data, root);
}

template<class T>
bool Tree<T>::insertElement(std::string trace, const T& data, TreeNode<T> *&current) {
	if (trace == "" && current == nullptr) {
		current = new TreeNode<T>(data, nullptr, nullptr);
		return true;
	}
	if (trace != "" && current == nullptr) {
		return false;
	}
	/*if (trace == "") {
		current->data = data;
		return true;
	}*/
	if (trace[0] == 'L') {
		trace.erase(0,1);
		return insertElement(trace, data, current->left);
	}
	if (trace[0] == 'R') {
		trace.erase(0,1);
		return insertElement(trace, data, current->right);
	}
	return false;
}

template<class T>
void Tree<T>::insertBOT(const T& data) {
	insertBOT(data, root);
}

template<class T>
void Tree<T>::insertBOT(const T& data, TreeNode<T> *current) {
	if (current == nullptr) {
		current = new TreeNode<T>(data, nullptr, nullptr);
		return;
	}
	if (data <= current->data) {
		insertBOT(data, current->left);
		return;
	}
	insertBOT(data, current->right);
}

template<class T>
int Tree<T>::count() const {
	return countHelp(root);
}

template<class T>
int Tree<T>::countHelp(TreeNode<T> *crr) const {
	if (crr == nullptr) {
		return 0;
	}
	return 1 + countHelp(crr->left) + countHelp(crr->right);
}

template<class T>
int Tree<T>::count(const T& data) const {
	return countHelp(root, data);
}

template<class T>
int Tree<T>::countHelp(TreeNode<T> *crr, const T& data) const {
	if (crr == nullptr) {
		return 0;
	}
	return (crr->data == data) + countHelp(crr->left, data) + countHelp(crr->right, data);
}

template<class T>
int Tree<T>::searchCount(bool(*pred)(const T&)) const {
	searchCountHelp(root, pred);
}

template<class T>
int Tree<T>::searchCountHelp(TreeNode<T> *crr, bool(*pred)(const T&)) const {
	if (crr == nullptr) {
		return 0;
	}
	return pred(crr->data) + countHelp(crr->left, pred) + countHelp(crr->right, pred);
}

template<class T>
int Tree<T>::countEvens() const {
	return searchCount([](const T& data) {return data % 2 == 0});
}

template<class T>
int Tree<T>::height() const {
	return heightHelp(root);
}

template<class T>
int Tree<T>::heightHelp(TreeNode<T> *crr) const {
	if (crr == nullptr) {
		return 0;
	}
	return 1 + std::max(heightHelp(crr->left), heightHelp(crr->right));
}

template<class T>
int Tree<T>::leaves() const {
	return leavesHelp(root);
}

template<class T>
int Tree<T>::leavesHelp(TreeNode<T> *crr) const {
	if (crr == nullptr) {
		return 0;
	}
	if (crr->left == nullptr && crr->right == nullptr) {
		return 1;
	}
	return leavesHelp(crr->left) + leavesHelp(crr->right);
}

template<class T>
std::vector<T> Tree<T>::allLeaves() const {
	std::vector<T> v;
	allLeavesHelp(root, v);
	return v;
}

template<class T>
void Tree<T>::allLeavesHelp(TreeNode<T> *crr, std::vector<T>& v) const {
	if (crr == nullptr) {
		return;
	}
	if (crr->left == nullptr && crr->right == nullptr) {
		v.push_back(current->data);
	}
	allLeavesHelp(crr->left, v);
	allLeavesHelp(crr->right, v);
}

template<class T>
T Tree<T>::maxLeaf() const {
	TreeNode<T> *crr = root;
	while (crr->left != nullptr || crr->right != nullptr) {
		if (crr->right != nullptr) crr = crr->right;
		else crr = crr->left;
	}
	return crr->data;
}

template<class T>
T Tree<T>::minNode() const {
	TreeNode<T> *crr = root;
	while (crr->left != nullptr) {
		crr = crr->left;
	}
	return crr->data;
}

template<class T>
T& Tree<T>::getElement(const char *trace) {
	return getElementHelp(root, trace);
}

template<class T>
T& Tree<T>::getElementHelp(TreeNode<T> *crr, const char *trace) {
	if (trace[0] == '\0') {
		return crr->data;
	}
	if (trace[0] == 'L') {
		return getElementHelp(crr->left, ++trace);
	}
	if (trace[0] == 'R') {
		return getElementHelp(crr->right, ++trace);
	}
}

template<class T>
void Tree<T>::prettyPrint() const {
	prettyPrintHelp(root, 0);
}

template<class T>
void Tree<T>::prettyPrintHelp(TreeNode<T> *crr, int level) const {
	if (crr == nullptr) {
		return;
	}
	prettyPrintHelp(crr->right, level + 1);
	std::cout << std::setw(level * 3) << current->data << std::endl;
	prettyPrintHelp(crr->left, level + 1);
}

template<class T>
std::string Tree<T>::findTrace(const T& x) const {
	std::string s;
	s = findTraceHelp(root, x);
	return s;
}

template<class T>
std::string Tree<T>::findTraceHelp(const T& x, TreeNode<T> *crr) const {
	if (crr == nullptr) {
		return "_";
	}
	if (crr->data == x) {
		return "";
	}
	std::string s1 = findTraceHelp(crr->left, x);
	if (s1 != "_") {
		return 'L' + s1;
	}
	std::string s2 = findTraceHelp(crr->right, x);
	if (s2 != "_") {
		return 'R' + s1;
	}
	return "_";
}

template<class T>
TreeNode<T>* Tree<T>::copyFrom(const TreeNode<T> *otherCrr) {
	if (otherCrr == nullptr) {
		return nullptr;
	}
	return new TreeNode<T>(otherCrr->data, copyFrom(otherCrr->left), copyFrom(otherCrr->right);
}

template<class T>
void Tree<T>::del(TreeNode<T> *crr) {
	if (crr == nullptr) {
		return;
	}
	del(crr->left);
	del(crr->right);
	delete crr;
}

template<class T>
bool Tree<T>::compare(const TreeNode<T> *t1, const TreeNode<T> *t2) const {
	if (t1 == nullptr) {
		return t2 == nullptr;
	}
	if (t2 == nullptr) {
		return t1 == nullptr;
	}
	return (t1->data == t2->data) && compare(t1->left, t2->left) && compare(t1->right, t2->right);
}

template<class T>
bool Tree<T>::member(const T& x, const TreeNode<T> *crr) const {
	if (crr == nullptr) {
		return false;
	}
	return (x == crr->data) || member(x, crr->left) || member(x, crr->right);
}

template<class T>
TreeNode<T>* Tree<T>::readFromStream(std::istream &in) {
	//()..............
	//( 7 ( 30 () ( 12 ( 90 () () ) () ) ) ( 5 ( 50 () () ) () ) )
	char next;
	next = in.get();
	assert(next == '(');

	next = in.get();
	assert(next == ' ' || next == ')');
	if (next == ')') {
		return nullptr;
	}

	T rootValue;
	in >> rootValue;

	next = in.get();
	assert(next == ' ');

	TreeNode<T> *left, *right;
	left = readFromStream(in);
	nextChar = in.get();
	assert(nextChar == ' ');
	right = readFromStream(in);

	next = in.get();
	assert(next == ' ');

	next = in.get();
	assert(next == ')');

	return new TreeNode<T>(rootValue, left, right);
}

template<class T>
Tree<T>::Tree(const Tree<T>& other) {
	root = copyFrom(other.root);
}

template<class T>
Tree<T>& Tree<T>::operator = (const BTree<T>& other) {
	if (this != &other) {
		del(root);
		root = copyFrom(other.root);
	}
	return *this;
}

template<class T>
Tree<T>::~Tree() {
	del(root);
}

template<class T>
bool Tree<T>::operator == (const BTree<T> &other) const {
	return compare(root, other.root)
}

template<class T>
bool Tree<T>::member(const T& x) const {
	return member(x, root);
}

template<class T>
void Tree<T>::read(std::istream &in) {
	root = readFromStream(in);
}

void Tree<char>::parseExpression(std::string s) {
	root = parseExpressionHelp(s);
}

TreeNode<char>* Tree<char>::parseExpressionHelp(std::string& s) {
	if (s.empty()) {
		return nullptr;
	}
	if (s[0] != '(') {
		char save = s[0];
		s.erase(0, 1);
		return new TreeNode<char>(save, nullptr, nullptr);
	}
	assert(s[0] == '(');
	s.erase(0, 1);
	TreeNode<char> *left = parseExpressionHelp(s);
	char rootValue = s[0];
	assert(rootValue == '+' || rootValue == '-' || rootValue == '*' || rootValue == '/');
	s.erase(0, 1);
	TreeNode<char> *right = parseExpressionHelp(s);
	assert(s[0] == ')');
	s.erase(0, 1);
	return new TreeNode<char>(rootValue, left, right);
}

double Tree<char>::calculateExpressionTree() const {
	return calculateExpressionTree(root);
}

double Tree<char>::calculateExpressionTree(TreeNode<char> *crr) const {
	if (crr == nullptr) {
		return 0;
	}
	char rootValue = crr->data;
	if (rootValue == '+' || rootValue == '-' || rootValue == '*' || rootValue == '/') {
		double left = calculateExpressionTree(crr->left),
			right = calculateExpressionTree(crr->left);
		switch (rootValue) {
		case '+': return left + right; break;
		case '-': return left - right; break;
		case '*': return left * right; break;
		case '/': return (double)left / right; break;
		}
	}
	return rootValue - '0';
}

template<class T>
T& Tree<T>::operator[](int i) {
	return operHelp(i, root);
}

template<class T>
T& Tree<T>::operHelp(int& i, TreeNode<T> *crr) {
	if (i == 0) {
		T& data = crr->data;
		return data;
	}
	if (crr->left != nullptr) {
		T& data = operHelp(--i, crr->left);
		if (i == 0) {
			return data;
		}
	}
	if (crr->right != nullptr) {
		T& data = operHelp(--i, crr->right);
		if (i == 0) {
			return data;
		}
	}
}

template <class T>
std::vector<T> Tree<T>::level(int k) const {
	std::vector<T> v;
	levelHelp(k, v, root);
	return v;
}

template <class T>
void Tree<T>::levelHelp(int k, std::vector<T>& v, TreeNode<T> *crr) const {
	if (crr == nullptr) {
		return;
	}
	if (k == 0) {
		v.push_back(crr->data);
		return;
	}
	levelHelp(k - 1, v, crr->left);
	levelHelp(k - 1, v, crr->right);
}