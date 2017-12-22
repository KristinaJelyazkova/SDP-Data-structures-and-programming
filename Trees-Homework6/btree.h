#ifndef __BTREE_H
#define __BTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

const int matrixWidth = 5,
matrixHeight = 5;

int mainMatrix[matrixWidth][matrixHeight] = {
	10, 20, 20, 10, 20,
	20, 30, 40, 35, 35,
	20, 40, 50, 35, 35,
	8, 5, 50, 60, 60,
	8, 5, 10, 10, 10
};

struct Matrix {
	Matrix(std::pair<int, int>, std::pair<int, int>);
	bool findBiggestSubmatrix(Matrix&, char);
	int elements();
	void allSubmatrixes(std::vector<Matrix>&, char);
	bool isLeft(int);
	bool isRight(int);

	std::pair<int, int> first;
	std::pair<int, int> size;
};

std::ostream& operator<<(std::ostream&, Matrix);

template <class T>
struct TreeNode
{
	TreeNode(const T& data, TreeNode<T> *_left, TreeNode<T> *_right);
	TreeNode<T> *left, *right;
	T data;

	int getId();

private:
	static int maxid;
	int id;
};


template <class T>
class BTree
{
public:
	BTree();
	BTree(const T, const BTree<T>&, const BTree<T>&);
	BTree(const BTree<T>&);

	BTree<T>& operator = (const BTree<T>&);

	bool operator == (const BTree<T>&) const;

	friend std::ostream& operator << (std::ostream&, const BTree<T>&);

	bool insertElement(std::string, const T&);
	void insertBOT(const T&);
	void deleteBOT(const T&);

	void fillGaps(const T&, unsigned int);

	TreeNode<T>* removeFromSubtree(const T&, TreeNode<T> *);
	void removeFromSubtreeProc(const T&, TreeNode<T> *&);


	bool member(const T& x) const;

	void read(std::istream&);
	void printDotty(std::ostream&);

	~BTree();
	bool areSame();
	bool isBOT();
	void replaceWithNumberOfChildren();
	void balanceStringTree();
	int height() const;
	void printNodesLISP(std::ostream&) const;
	void makeMatrixTree();

private:
	TreeNode<T> *root;

	void fillGaps(const T&, TreeNode<T> *&, unsigned int);

	bool insertElement(std::string, const T&, TreeNode<T>*&);
	void insertBOT(const T&, TreeNode<T>*&);
	void del(TreeNode<T>*);
	T& findmin(TreeNode<T> *);

	bool member(const T& x, const TreeNode<T> *) const;
	TreeNode<T>* readFromStream(std::istream &);

	TreeNode<T>* copyFrom(const TreeNode<T> *);

	bool compare(const TreeNode<T> *t1, const TreeNode<T> *t2) const;
	void printNodesLISP(std::ostream&, TreeNode<T> *) const;

	void createVectorOfSets(TreeNode<T> *, int, std::vector<std::set<T>> &);
	bool isBOTHelp(TreeNode<T> *, int, int);
	int replaceWithNumberOfChildren(TreeNode<T> *);
	void createVectorOfStringsOnLevels(TreeNode<std::string> *, std::vector<std::string>&, int);
	void balanceStringTree(TreeNode<std::string> *&, std::vector<std::string>&, int, std::vector<std::string>);
	int heightHelp(TreeNode<T>*) const;
	void makeMatrixTree(TreeNode<Matrix> *&, char, TreeNode<Matrix> *);

};
template <class T>
std::ostream& operator << (std::ostream&, const BTree<T>&);

#endif
