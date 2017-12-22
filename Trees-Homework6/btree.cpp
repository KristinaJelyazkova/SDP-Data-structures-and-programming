#include "btree.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

std::ostream& operator<<(std::ostream& out, Matrix matrix) {
	/*out << "[ {" << matrix.first.first << "," << matrix.first.second << "} "
		<< ", {" << matrix.size.first << "," << matrix.size.second << "} ]";*/
	out << "\n";
	for (int i = matrix.first.first; i < matrix.first.first + matrix.size.first; i++) {
		for (int j = matrix.first.second; j < matrix.first.second + matrix.size.second; j++) {
			out << mainMatrix[i][j] << " ";
		}
		out << "\n";
	}
	return out;
}

bool Matrix::isLeft(int max) { // if the matrix is left compared to the max value
	for (int i = first.first; i < first.first + size.first; i++) {
		for (int j = first.second; j < first.second + size.second; j++) {
			if (mainMatrix[i][j] >= max) { // all elements of the matrix should be less than the max value
				return false;
			}
		}
	}
	return true;
}

bool Matrix::isRight(int min) {
	for (int i = first.first; i < first.first + size.first; i++) {
		for (int j = first.second; j < first.second + size.second; j++) {
			if (mainMatrix[i][j] <= min) {
				return false;
			}
		}
	}
	return true;
}

void Matrix::allSubmatrixes(std::vector<Matrix>& subm, char symbol) { // subm is empty and we fill it with all the left/right submatrixes of the current matrix
	for (int i = first.first; i < first.first + size.first - 1; i++) { // we go trough all submatrixes with the 4 for-s which are bigger than 2x2
		for (int j = first.second; j < first.second + size.second - 1; j++) {
			for (int x = 2; x <= size.first - (i - first.first); x++) { // the maximum possible size changes according to i
				for (int y = 2; y <= size.second - (j - first.second); y++) {
					Matrix newMatrix({ i,j }, { x,y });
					if ((symbol == 'L' && // the symbol shows wether we look for left or right submatrixes
							newMatrix.isLeft( mainMatrix[first.first][first.second] )) || // we compare the elements of the new matrix with the first element of the current matrix
						(symbol == 'R' &&
							newMatrix.isRight( mainMatrix[first.first][first.second] ))) {

						//std::cout << mainMatrix[first.first][first.second] << std::endl;

						subm.push_back(newMatrix);
					}
				}
			}
		}
	}
}

int Matrix::elements() { // finds the number of elements in the matrix - how big it is
	return size.first * size.second;
}

bool Matrix::findBiggestSubmatrix(Matrix& result, char symbol) { // result is assigned with the biggest(has most elements) left/right submatrix which are put in the vector by allSubmatrixes()
	std::vector<Matrix> submatrix;
	allSubmatrixes(submatrix, symbol);
	if (submatrix.empty()) { // if the vector is empty, there are no left/right submatrixes
		return false;
	}
	int max = submatrix[0].elements();
	int maxPos = 0;
	for (int i = 1; i < submatrix.size(); i++) {
		int crr = submatrix[i].elements();
		if (crr > max) {
			max = crr;
			maxPos = i;
		}
	}
	result = submatrix[maxPos]; // result is & because we use the value in makeMatrixTree
	return true;
}

template<>
void BTree<Matrix>::makeMatrixTree() {
	root = new TreeNode<Matrix>(Matrix({ 0,0 }, { matrixWidth, matrixHeight }), nullptr, nullptr); // the root is the global matrix from btree.h file
	makeMatrixTree(root->left, 'L', root); // building the left subtree
	makeMatrixTree(root->right, 'R', root); // building the right subtree
}

template<>
void BTree<Matrix>::makeMatrixTree(TreeNode<Matrix> *&crr, char symbol, TreeNode<Matrix> *par) { // we need a parent pointer to find the parent matrix from which we find the needed submatrix
	Matrix submatrix({0,0}, {0,0}); // creating an empty matrix
	if ( par->data.findBiggestSubmatrix(submatrix, symbol) ) // if there is a left/right(according to the symbol) matrix, it is memorised in the submatrix parameter
	{ // par->data is the parent matrix
		crr = new TreeNode<Matrix>(submatrix, nullptr, nullptr); // crr is & => with this line we create a new node and connect its parent with it
		makeMatrixTree(crr->left, 'L', crr); // we need two different tree node pointers - in order to create new nodes and connect them and on the other hand, to access the parent matrix
		makeMatrixTree(crr->right, 'R', crr); // creating the right subtree and 'R' shows it is the right so we know that we are looking for a right submatrix
	}
}

Matrix::Matrix(std::pair<int, int> _first, std::pair<int, int> _size) :
first(_first), size(_size) {}

template<> // when we have a concrete T we have to write this - template<>
void BTree<std::string>::balanceStringTree() {
	std::vector<std::string> v;
	createVectorOfStringsOnLevels(root, v, 0); // we union the strings on each level into one string
	balanceStringTree(root, v, 0, v); 
}

template<>
void BTree<std::string>::createVectorOfStringsOnLevels(TreeNode<std::string> *crr, std::vector<std::string> &v, int level) {
	if (crr == nullptr) {
		return;
	}
	if (v.size() == level) { // => we are on a new level
		v.push_back(std::string()); // we create a new empty string for each new level
	}
	v[level] += crr->data; // concat the data to the current string on the current level
	createVectorOfStringsOnLevels(crr->left, v, level + 1); // left subtree
	createVectorOfStringsOnLevels(crr->right, v, level + 1); // right subtree
}

template<> // here we use a copy of the vector because we need the whole length of the string on each level, but we have to erase letters from the strings
void BTree<std::string>::balanceStringTree(TreeNode<std::string> *&crr, std::vector<std::string> &v, int level, std::vector<std::string> copy) {
	if (crr == nullptr) {
		if (level >= height()) { // if the level is more than the height we don't have to add a new node
			return;
		}
		crr = new TreeNode<std::string>("", nullptr, nullptr); // else => to balance the tree, we add a new node, its data is set in the code below
	}
	int length = ceil(copy[level].length() / pow(2, level)); // the lengths of the new strings on each level have to be equal
	std::string newData; 
	newData.assign(v[level], 0, length); // ASSIGN!!! copying the first <length> elements of the string on this level
	v[level].erase(0, length); // erasing the elements we already used, so the neighbour node would start from the next letter in the string
	crr->data = newData;
	balanceStringTree(crr->left, v, level + 1, copy); // left sub tree, the level is the next => +1
	balanceStringTree(crr->right, v, level + 1, copy);
}

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
void BTree<T>::replaceWithNumberOfChildren() {
	replaceWithNumberOfChildren(root);
}

template <class T>
int BTree<T>::replaceWithNumberOfChildren(TreeNode<T> *crr) {
	if (crr == nullptr) {
		return 0;
	}
	int x = replaceWithNumberOfChildren(crr->left),
		y = replaceWithNumberOfChildren(crr->right);
	crr->data = 1 + x + y;
	return crr->data;
}

template <class T>
bool BTree<T>::isBOT() {
	return isBOTHelp(root, INT32_MIN, INT32_MAX); // these are the lowest and highest ints, so we have the largest range possible
}

template <class T>
bool BTree<T>::isBOTHelp(TreeNode<T> *crr, int minVal, int maxVal) { // [minval, maxVal] is the current range that is allowed for the elements in order to be a BOT
	if (crr == nullptr) {
		return true;
	}
	return (crr->data >= minVal && crr->data <= maxVal) &&
		isBOTHelp(crr->left, minVal, crr->data) && // the left subtree should have only elements that are less than its root => we change the maxVal to cur->data
		isBOTHelp(crr->right, crr->data, maxVal);// the right subtree should have only elements that are more than its root => we change the minVal to cur->data
}

template <class T>
bool BTree<T>::areSame() {
	std::vector<std::set<T>> v;
	createVectorOfSets(root, 0, v); // creating a vector with the set of the elements on each level
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (v[i] == v[j]) { // if there are two sets with the same elements
				return true;
			}
		}
	}
	return false;
}

template <class T>
void BTree<T>::createVectorOfSets(TreeNode<T> *crr, int h, std::vector<std::set<T>> &v) {
	if (crr == nullptr) {
		return;
	}
	if (v.size() <= h) v.push_back(std::set<T>()); // on a new level => pushing an empty set;
	v[h].insert(crr->data); // INSERT!!! - inserting the current data in the set of the level we are on
	createVectorOfSets(crr->left, h + 1, v); // going left on the next level
	createVectorOfSets(crr->right, h + 1, v); // going right on the next level
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
	root = new TreeNode<T>(data, copyFrom(lt.root), copyFrom(rt.root));

}

template <class T>
void BTree<T>::printNodesLISP(std::ostream& out) const {
	printNodesLISP(out, root);
}

template <class T>
void BTree<T>::printNodesLISP(std::ostream& out, TreeNode<T> *root) const
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

	t.printNodesLISP(out, t.root);

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

	if (x < crr->data) {
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
	//приемаме, че дървото е празно
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
	//уверени сме, че в потока следват следните неща:
	//1. СТОЙНОСТ НА КОРЕНА. ПРИЕМАМЕ, ЧЕ ОПЕРАТОР >>T КОРЕКТНО ЩЕ Я ИЗЧЕТЕ

	T rootValue;
	in >> rootValue;

	//2. интервал

	nextChar = in.get();
	assert(nextChar == ' ');

	//3. ЛЯВО ПОДДЪРВО

	TreeNode<T> *leftSubTree;
	leftSubTree = readFromStream(in);

	//4. интервал

	nextChar = in.get();
	assert(nextChar == ' ');

	//5. ДЯСНО ПОДДЪРВО

	TreeNode<T> *rightSubTree;
	rightSubTree = readFromStream(in);

	//6. интервал

	nextChar = in.get();
	assert(nextChar == ' ');

	//7. затваряща скоба

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

template <class T>
void BTree<T>::deleteBOT(const T &x)
{

	removeFromSubtreeProc(x, root);

}

template <class T>
T& BTree<T>::findmin(TreeNode<T> *crr)
{
	assert(crr != nullptr);

	while (crr->left != nullptr)
	{
		crr = crr->left;
	}

	return crr->data;

}

template <class T>
TreeNode<T>* BTree<T>::removeFromSubtree(const T &x, TreeNode<T> *crr)
{
	//1
	if (crr == nullptr)
		return nullptr;

	//2
	if (crr->data == x && crr->left == nullptr)
	{
		TreeNode <T> *save = crr->right;
		delete crr;
		return save;
	}
	//3
	if (crr->data == x && crr->right == nullptr)
	{
		TreeNode <T> *save = crr->left;
		delete crr;
		return save;
	}
	//4
	if (crr->data == x)
	{
		T rightmin = findmin(crr->right);
		crr->data = rightmin;
		crr->right = removeFromSubtree(rightmin, crr->right);
		crr = removeFromSubtree(x, crr);
		return crr;

	}
	//5, 6
	if (crr->data < x)
	{
		crr->right = removeFromSubtree(x, crr->right);
	}
	else {
		crr->left = removeFromSubtree(x, crr->left);
	}

	return crr;

}


template <class T>
void BTree<T>::removeFromSubtreeProc(const T &x, TreeNode<T> *&crr)
{
	//1
	if (crr == nullptr)
		return;

	//2
	if (crr->data == x && crr->left == nullptr)
	{
		TreeNode <T> *save = crr->right;
		delete crr;
		crr = save;
		return;
	}
	//3
	if (crr->data == x && crr->right == nullptr)
	{
		TreeNode <T> *save = crr->left;
		delete crr;
		crr = save;
		return;
	}
	//4
	if (crr->data == x)
	{
		T rightmin = findmin(crr->right);
		crr->data = rightmin;
		removeFromSubtreeProc(rightmin, crr->right);
		removeFromSubtreeProc(x, crr);
		return;

	}
	//5, 6
	if (crr->data < x)
	{
		removeFromSubtreeProc(x, crr->right);
	}
	else {
		removeFromSubtreeProc(x, crr->left);
	}

	return;

}


template <class T>
void BTree<T>::printDotty(std::ostream &out)
{
	out << "digraph G{" << std::endl;
	printNodesDotty(out, root);
	out << "}" << std::endl;
}

template <class T>
void BTree<T>::fillGaps(const T& x, unsigned int h)
{
	fillGaps(x, root, h);
}


template <class T>
void BTree<T>::fillGaps(const T &x, TreeNode<T> *&crr, unsigned int h)
{
	if (h == 0)
	{
		return;
	}

	if (crr == nullptr)
	{
		crr = new TreeNode<T>(x, nullptr, nullptr);
	}

	fillGaps(x, crr->left, h - 1);
	fillGaps(x, crr->right, h - 1);

}