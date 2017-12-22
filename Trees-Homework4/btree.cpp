#include "btree.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iomanip>

template <class T>
void BTree<T>::prettyPrint() const {
	prettyPrintHelp(root, 0);
}

template <class T>
void BTree<T>::prettyPrintHelp(TreeNode<T>* current, int height) const {
	if (current == nullptr) return;
	prettyPrintHelp(current->right, height + 1);
	std::cout << std::setw(height * 3) << current->data;
	std::cout << std::endl;
	prettyPrintHelp(current->left, height + 1);
}

template <class T>
std::string BTree<T>::findTrace(const T& x) const {
	std::string s;
	s = findTraceHelp(x, root);
	return s;
}

template <class T>
std::string BTree<T>::findTraceHelp(const T& x, TreeNode<T>* current) const {
	if (current == nullptr) {
		return "_";
	}
	if (current->data == x) {
		return "";
	}
	std::string s1 = findTraceHelp(x, current->left);
	if (s1 != "_") {
		return "L" + s1;
	}
	std::string s2 = findTraceHelp(x, current->right);
	if (s2 != "_") {
		return "R" + s2;
	}
	return "_";
}

template <class T>
int BTree<T>::countHelp(TreeNode<T> *current) const {
	if (current == nullptr) return 0;
	return 1 + countHelp(current->left) + countHelp(current->right);
}

template <class T>
int BTree<T>::count() const {
	//return countHelp(root);
	return searchCount([](const T& _data) { return true; });
}

template <class T>
int BTree<T>::countHelp(TreeNode<T> *current, const T& data) const {
	if (current == nullptr) return 0;
	return (current->data == data) + countHelp(current->left, data) + countHelp(current->right, data);
}


template <class T>
int BTree<T>::count(const T& data) const {
	return countHelp(root, data);
}

template <class T>
int BTree<T>::searchCountHelp(TreeNode<T> *current, bool(*pred)(const T&)) const {
	if (current == nullptr) return 0;
	return pred(current->data) + searchCountHelp(current->left, pred) + searchCountHelp(current->right, pred);
}

template <class T>
int BTree<T>::searchCount(bool(*pred)(const T&)) const {
	return searchCountHelp(root, pred);
}

template <class T>
int  BTree<T>::countEvens() const {
	return searchCount([](const T& _data) {return _data % 2 == 0; });
}

/*template <class T>
int BTree<T>::heightHelp(TreeNode<T> *current) const {
if (current == nullptr) return 0;
int k1 = heightHelp(current->left),
k2 = heightHelp(current->right),
max = k1;
if (k2 > max) max = k2;
return 1 + max;
}*/

template <class T>
int BTree<T>::heightHelp(TreeNode<T> *current) const {
	if (current == nullptr) return 0;
	return 1 + std::max(heightHelp(current->left), heightHelp(current->right));
}

template <class T>
int BTree<T>::height() const {
	return heightHelp(root);
}

template <class T>
int BTree<T>::leavesHelp(TreeNode<T> *current) const {
	if (current == nullptr) return 0;
	if (current->left == nullptr && current->right == nullptr) return 1;
	return leavesHelp(current->left) + leavesHelp(current->right);
}

template <class T>
int BTree<T>::leaves() const {
	return leavesHelp(root);
}

template <class T>
void BTree<T>::allLeavesHelp(TreeNode<T> *current, std::vector<T>& v) const {
	if (current == nullptr) return;
	if (current->left == nullptr && current->right == nullptr) v.push_back(current->data);
	allLeavesHelp(current->left, v);
	allLeavesHelp(current->right, v);
}

template <class T>
std::vector<T> BTree<T>::allLeaves() const {
	std::vector<T> v;
	allLeavesHelp(root, v);
	return v;
}

/*template<class T>
T BTree<T>::maxLeafHelp(TreeNode<T> *current, T& max) const {
	if (current->left == nullptr && current->right == nullptr) {
		if (current->data > max) {
			max = current->data;
		}
		return max;
	}
	return std::max(maxLeafHelp(current->left, max), maxLeafHelp(current->right, max));
}*/

template<class T>
T BTree<T>::minNode() const {
	TreeNode<T> *current = root;
	assert(root != nullptr);
	while (current->left != nullptr) {
		current = current->left;
	}
	return current->data;
}

template <class T>
T BTree<T>::maxLeaf() const {
	assert(root != nullptr);
	//T max = minNode();
	//return maxLeafHelp(root, max);
	TreeNode<T> *current = root;
	while (current->right != nullptr || current->left != nullptr) {
		if (current->right != nullptr) current = current->right;
		else current = current->left;
	}
	return current->data;
}

template <class T>
T& BTree<T>::getElementHelp(TreeNode<T>* current, const char *s) {
	int a = 0;
	if (current == nullptr) return a;
	if (s[0] == '\0') return current->data;
	if (s[0] == 'L') {
		return getElementHelp(current->left, ++s);
	}
	if (s[0] == 'R') {
		return getElementHelp(current->right, ++s);
	}
}

template <class T>
T& BTree<T>::getElement(const char *s) {
	return getElementHelp(root, s);
}




template <class T>
TreeNode<T>::TreeNode(const T& _data,
	TreeNode<T> *_left,
	TreeNode<T> *_right) :data(_data),
	left(_left),
	right(_right)
{
	id = maxid;
	maxid++;
}

template <class T>
int TreeNode<T>::getId()
{
	return id;
}

template <class T>
int TreeNode<T>::maxid = 0;


template <class T>
BTree<T>::BTree() :root(nullptr)
{

}

template <class T>
BTree<T>::BTree(const T data, const BTree<T> &lt, const BTree<T> &rt)
{
	//TODO: НЕ ТАКА!!!
	root = new TreeNode<T>(data, lt.root, rt.root);

}

template <class T>
void printNodesLISP(std::ostream& out, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		out << "()";
		return;
	}

	out << "(" << root->data << ",";
	printNodes(out, root->left);
	out << ",";
	printNodes(out, root->right);
	out << ")";
}

template <class T>
void printNodesDotty(std::ostream& out, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return;
	}

	out << root->getId()
		<< "[label=\""
		<< root->data
		<< "\"];"
		<< std::endl;

	if (root->left != nullptr)
	{
		out << root->getId()
			<< "->"
			<< root->left->getId()
			<< "[color = \"red\"]"
			<< ";"
			<< std::endl;
	}

	if (root->right != nullptr)
	{
		out << root->getId()
			<< "->"
			<< root->right->getId()
			<< ";"
			<< std::endl;
	}
	printNodesDotty(out, root->left);
	printNodesDotty(out, root->right);
}



std::ostream& operator << (std::ostream &out, const BTree<int> &t)
{
	out << "digraph G {" << std::endl;
	printNodesDotty(out, t.root);
	out << "}" << std::endl;
	return out;
}

template <class T>
bool BTree<T>::insertElement(std::string trace, const T& x, TreeNode<T> *&crr)
{
	if (trace == "" && crr == nullptr)
	{
		crr = new TreeNode<T>(x, nullptr, nullptr);
		return true;
	}
	if (trace != "" && crr == nullptr)
	{
		return false;
	}
	//=> trace != "" && current != nullptr
	if (trace[0] == 'L')
	{
		trace.erase(0);
		return insertElement(trace, x, crr->left);
	}
	if (trace[0] == 'R')
	{
		trace.erase(0);
		return insertElement(trace, x, crr->right);
	}
	return false;
}


template <class T>
bool BTree<T>::insertElement(std::string trace, const T& x)
{
	return insertElement(trace, x, root);
}

template <class T>
void BTree<T>::insertBOT(const T &x, TreeNode<T> *&crr)
{
	if (crr == nullptr)
	{
		crr = new TreeNode<T>(x, nullptr, nullptr);
		return;
	}

	if (x <= crr->data) {
		insertBOT(x, crr->left);
		return;
	}

	insertBOT(x, crr->right);


}

template <class T>
void BTree<T>::insertBOT(const T& x)
{
	insertBOT(x, root);
}


/*
template <class T>
bool BTree<T>::insertElement (std::string trace, const T& x)
{
if (trace == "")
{
assert (root == nullptr);
root = new TreeNode<T> (x,nullptr,nullptr);
return true;
}
TreeNode<T> *crr = root;
int letter = 0;
assert (root != nullptr);
for (letter = 0; letter < trace.size()-1; letter++)
{
assert (trace[letter] == 'L' || trace[letter] == 'R');
if (trace[letter] == 'L')
{
crr = crr->left;
} else if (trace[letter] == 'R')
{
crr = crr->right;
}
assert (crr != nullptr);
}
assert (trace[letter] == 'L' || trace[letter] == 'R');
//crr сочи родителя на "дупката"
if (trace[letter] == 'L')
{
assert (crr->left == nullptr);
crr->left = new TreeNode<T> (x,nullptr,nullptr);
return true;
}
if (trace[letter] == 'R')
{
assert (crr->right == nullptr);
crr->right = new TreeNode<T> (x,nullptr,nullptr);
return true;
}
return false;
}*/