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
	BTree(const BTree<T>&);
	//TODO: √ŒÀﬂÃ¿ ◊≈“¬Œ– ¿

	BTree<T>& operator = (const BTree<T>&);

	bool operator == (const BTree<T>&) const;

	friend std::ostream& operator << (std::ostream&, const BTree<T>&);

	bool insertElement(std::string, const T&);
	void insertBOT(const T&);

	bool member(const T& x) const;

	void read(std::istream&);

	~BTree();

	void parseExpression(std::string);
	void prettyPrint() const;
	double calculateExpressionTree() const;
	std::vector<T> level(int) const;
	T& operator[](int);
	//const T operator[](int) const;
	int count() const;

private:
	TreeNode<T> *root;
	bool insertElement(std::string, const T&, TreeNode<T>*&);
	void insertBOT(const T&, TreeNode<T>*&);
	void del(TreeNode<T>*);

	bool member(const T& x, const TreeNode<T> *) const;
	TreeNode<T>* readFromStream(std::istream &);

	TreeNode<T>* copyFrom(const TreeNode<T> *);

	bool compare(const TreeNode<T> *t1, const TreeNode<T> *t2) const;

	TreeNode<char>* parseExpressionHelp(std::string&);
	void prettyPrintHelp(TreeNode<T>*, int) const;
	double calculateExpressionTreeHelp(TreeNode<char>*) const;
	void levelHelp(int, TreeNode<T>*, std::vector<T>&) const;
	T& operHelp(int&, TreeNode<T>*);
	//bool operHelp(int&, TreeNode<T>*, T&) const;
	//T& findIEl(TreeNode<T>*, int&);
	int countHelp(TreeNode<T>*) const;


};
template <class T>
std::ostream& operator << (std::ostream&, const BTree<T>&);

#endif#pragma once
