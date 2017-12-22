#ifndef __BTREE_H
#define __BTREE_H

#include <iostream>
#include <string>
#include <vector>

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
	//TODO: √ŒÀﬂÃ¿ ◊≈“¬Œ– ¿

	friend std::ostream& operator << (std::ostream&, const BTree<T>&);

	bool insertElement(std::string, const T&);
	void insertBOT(const T&);

	int count() const;
	int count(const T&) const;
	int searchCount(bool(*pred)(const T&)) const;
	int countEvens() const;
	int height() const;
	int leaves() const;
	std::vector<T> allLeaves() const;
	T maxLeaf() const;
	T minNode() const;
	T& getElement(const char *);

	void prettyPrint() const;
	std::string findTrace(const T&) const;
	void parseExpression(std::string);

private:
	TreeNode<T> *root;
	bool insertElement(std::string, const T&, TreeNode<T>*&);
	void insertBOT(const T&, TreeNode<T>*&);
	int countHelp(TreeNode<T>*) const;
	int countHelp(TreeNode<T>*, const T&) const;
	int searchCountHelp(TreeNode<T>*, bool(*pred)(const T&)) const;
	int heightHelp(TreeNode<T>*) const;
	int leavesHelp(TreeNode<T>*) const;
	void allLeavesHelp(TreeNode<T>*, std::vector<T>&) const;
	T& getElementHelp(TreeNode<T>*, const char *);

	std::string findTraceHelp(const T&, TreeNode<T>*) const;
	void prettyPrintHelp(TreeNode<T>*, int) const;
};

template <class T>
std::ostream& operator << (std::ostream&, const BTree<T>&);

#endif
