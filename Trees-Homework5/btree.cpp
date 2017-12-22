#include "btree.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <vector>

// OPERATOR[] !!!

template <class T>
int BTree<T>::countHelp(TreeNode<T> *current) const {
	if (current == nullptr) return 0;
	return 1 + countHelp(current->left) + countHelp(current->right);
}


template <class T>
int BTree<T>::count() const {
	return countHelp(root);
}

template <class T> // !!! ������ ������� �& ������ ����� ��� �� ����� �& p = ������, ����� ������ �� ������ � ���� ���� ��� return p !!!!!
T& BTree<T>::operHelp(int& i, TreeNode<T>* current) {
	if (i == 0) { // �� ����� ������ �������� i � 1 � ������ ������� i = 0, �� ��� �������� ������
		T& p = current->data;
		return p;
	}
	if (i > 0) { // ��� ���� ��� �� ��������, �� ������������
		if (current->left != nullptr) { // ������ ������ ���� ��� ��� ������� ������
			T& q = operHelp(--i, current->left); // ���� ������ ���� �� ������� �� current = nullptr (�������� �� ����� ���� i + 1 �������� � �������)
			if (i == 0) { // ��� ��� �� �������� � ������ �������� �� �������
				return q; // q e �& !!!
			}
		}
	}
	if (i > 0) {  // ��� ���� ��� �� ��������, �� ������������
		if (current->right != nullptr) { // ������ ������� ���� ��� ��� ������� �������
			T& r = operHelp(--i, current->right);
			if (i == 0) { // ��� ��� �� �������� � ������� �������� �� �������
				return r; // r e �& !!!
			}
		}
	}
}

template <class T>
T& BTree<T>::operator[](int i) {
	return operHelp(i, root);
}


template <class T>
void BTree<T>::levelHelp(int k, TreeNode<T>* current, std::vector<T>& list) const {//vector&, �� �� �� �������� ����������� �������� � ����
	if (current == nullptr) {
		return;
	}
	if (k == 0) {
		list.push_back(current->data); // ��� ���� �� ����� ������ ��� ����� �������� �������� k � 1, �� ������ �� � 0, �� ��� �������� �� ������� �� ���� k � ������ �� �� ������� ��� �������
		return;
	}
	levelHelp(k - 1, current->left, list); // ������� ���� ���� ������ � �������� ���� �� ���� k �� ������ ��������
	levelHelp(k - 1, current->right, list);// ������� ���� ���� ������ � �������� ���� �� ���� k �� ������� ��������
}

template <class T>
std::vector<T> BTree<T>::level(int k) const {
	std::vector<T> list;
	levelHelp(k, root, list);
	return list;
}

double BTree<char>::calculateExpressionTreeHelp(TreeNode<char>* current) const {
	if (current == nullptr) { // ��� ������� � ������
		return 0;
	}
	char c = current->data;
	if (c != '+' && c != '-' && c != '/' && c != '*') { // ��� ������� �� � �������� => � ����� � ���� � ������ �����
		return c - '0'; // -'0' �� �� ������ ������ �����, � �� �������
	}
	// => ������� � ��������
	double left = calculateExpressionTreeHelp(current->left); // ����������� ���������� ������� � ������ ��������
	double right = calculateExpressionTreeHelp(current->right); // ����������� ���������� ������� � ������� ��������
	switch (c) { // ��������� ����������(� ������) ����� ��������� �� ������ � ������� ��������
	case '+': return left + right;
	case '-': return left - right;
	case '*': return left * right;
	case '/': return left / right;
	}
}

double BTree<char>::calculateExpressionTree() const {
	return calculateExpressionTreeHelp(root);
}

template <class T>
void BTree<T>::prettyPrint() const {
	prettyPrintHelp(root, 0);
}

template <class T>
void BTree<T>::prettyPrintHelp(TreeNode<T>* current, int height) const { // height �� ������� �� ����� �������� ��� � ������� � ������ ��� ������ �������� ������ ������������ ����� �������
	if (current == nullptr) return;
	prettyPrintHelp(current->right, height + 1); // ������ ������� ��������
	std::cout << std::setw(height * 3) << current->data; // ������ ������
	std::cout << std::endl;
	prettyPrintHelp(current->left, height + 1); // ������ ������ ��������
}

TreeNode<char>* BTree<char>::parseExpressionHelp(std::string& s) {
	if (s == "") {
		return nullptr;
	}
	// �����, �� s �� � ������
	char c;
	c = s[0]; // ������� �������� ������ �� s - ��� � ( ��� �����
	s.erase(0, 1); // ���� ������ ������� (0 - �������, �� ����� ����� �� ����, 1 - ����� ������� ����;
	// ������� ��� ������� ��� ������� �� �������
	if (c != '(') { // => ��� �������, �� � ����� � ���� � ������ �����
		return new TreeNode<char>(c, nullptr, nullptr);
	}
	assert(c == '(');
	// c � ����� => ������ <�����><��><�����>)
	TreeNode<char> *left = parseExpressionHelp(s); // ������� ����� ����� ����������
	char op;
	op = s[0]; // ���� � ����������
	assert(op == '+' || op == '-' || op == '*' || op == '/');
	s.erase(0, 1); // ������ ������� �� ���������� �� �������
	TreeNode<char> *right = parseExpressionHelp(s); // ������� ������ ����� ����������
	c = s[0]; // ������� ����������� ����� )
	s.erase(0, 1); // ���� ������� ������ �� � ������;
	assert(c == ')');
	return new TreeNode<char>(op, left, right);
}

void BTree<char>::parseExpression(std::string s) {
	root = parseExpressionHelp(s);
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
	//TODO: �� ����!!!
	root = new TreeNode<T>(data, copyFrom(lt.root), copyFrom(rt.root));

}

template <class T>
void printNodesLISP(std::ostream& out, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		out << "()";
		return;
	}

	out << "( " << root->data << " ";
	printNodesLISP(out, root->left);
	out << " ";
	printNodesLISP(out, root->right);
	out << " )";
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
	/*  out << "digraph G {" << std::endl;
	printNodesDotty (out, t.root);
	out << "}" << std::endl;*/

	printNodesLISP(out, t.root);

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
		trace.erase(trace.begin());
		return insertElement(trace, x, crr->left);
	}
	if (trace[0] == 'R')
	{
		trace.erase(trace.begin());
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

template <class T>
bool BTree<T>::member(const T& y) const
{
	return member(y, root);
}


template <class T>
bool BTree<T>::member(const T& y, const TreeNode<T> *crr) const
{
	if (crr == nullptr)
	{
		return false;
	}

	return crr->data == y ||
		member(y, crr->left) ||
		member(y, crr->right);
}


template <class T>
void BTree<T>::read(std::istream &in)
{
	//��������, �� ������� � ������
	root = readFromStream(in);
}


template <class T>
TreeNode<T>* BTree<T>::readFromStream(std::istream &in)
{ //()..............
  //( 7 ( 30 () ( 12 ( 90 () () ) () ) ) ( 5 ( 50 () () ) () ) )

	char nextChar;
	nextChar = in.get();
	assert(nextChar == '(');

	nextChar = in.get();
	assert(nextChar == ' ' || nextChar == ')');

	if (nextChar == ')')
	{
		return nullptr;
	}
	//������� ���, �� � ������ ������� �������� ����:
	//1. �������� �� ������. ��������, �� �������� >>T �������� �� � ������

	T rootValue;
	in >> rootValue;

	//2. ��������

	nextChar = in.get();
	assert(nextChar == ' ');

	//3. ���� ��������

	TreeNode<T> *leftSubTree;
	leftSubTree = readFromStream(in);

	//4. ��������

	nextChar = in.get();
	assert(nextChar == ' ');

	//5. ����� ��������

	TreeNode<T> *rightSubTree;
	rightSubTree = readFromStream(in);

	//6. ��������

	nextChar = in.get();
	assert(nextChar == ' ');

	//7. ��������� �����

	nextChar = in.get();
	assert(nextChar == ')');

	return new TreeNode<T>(rootValue, leftSubTree, rightSubTree);

}


template <class T>
void BTree<T>::del(TreeNode<T> *crr)
{
	if (crr == nullptr)
	{
		return;
	}

	del(crr->left);
	del(crr->right);
	delete crr;
}


template <class T>
BTree<T>::~BTree()
{
	del(root);
}

template <class T>
TreeNode<T>* BTree<T>::copyFrom(const TreeNode<T> *crr)
{
	if (crr == nullptr)
	{
		return nullptr;
	}

	return new TreeNode<T>(crr->data,
		copyFrom(crr->left),
		copyFrom(crr->right));
}


template <class T>
BTree<T>::BTree(const BTree<T> &other)
{
	root = copyFrom(other.root);
}

template <class T>
BTree<T>& BTree<T>::operator = (const BTree<T> &other)
{
	if (this != &other)
	{
		del(root);
		root = copyFrom(other.root);
	}
	return *this;
}

template <class T>
bool BTree<T>::operator == (const BTree<T> &other) const
{
	return compare(root, other.root);
}

template <class T>
bool BTree<T>::compare(const TreeNode<T> *t1, const TreeNode<T> *t2) const
{
	if (t1 == nullptr)
		return t2 == nullptr;

	if (t2 == nullptr)
		return t1 == nullptr;

	return t1->data == t2->data &&
		compare(t1->left, t2->left) &&
		compare(t1->right, t2->right);
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
//crr ���� �������� �� "�������"
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