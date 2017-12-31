#pragma once
#include<iostream>
#include<string>
#include<vector>

template<class T>
struct TreeNode {
	T data;
	TreeNode<T> *left, *right;
	TreeNode(const T&, TreeNode<T>*, TreeNode<T>*);
	int getID();
private:
	static int maxID;
	int id;
};

template<class T>
class Tree {
public:
	Tree();
	Tree(const T, Tree<T>, Tree<T>);
	
	//friend std::ostream& operator<<(std::ostream&, const Tree<T>&);
	void print(std::ostream&);

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

private:
	TreeNode<T> *root;

	bool insertElement(std::string, const T&, TreeNode<T>*&);
	void insertBOT(const T&, TreeNode<T>*);
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

template<class T>
std::ostream& operator<<(std::ostream&, Tree<T>&);
