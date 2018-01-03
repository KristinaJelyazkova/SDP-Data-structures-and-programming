#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<set>

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

	Tree(const Tree<T>&);
	Tree<T>& operator = (const Tree<T>&);
	~Tree();

	bool operator == (const Tree<T>&) const;
	bool member(const T& x) const;
	void read(std::istream&);

	void parseExpression(std::string);
	double calculateExpressionTree() const;
	T& operator[](int);
	std::vector<T> level(int) const;

	void deleteBOT(const T&);
	void fillGaps(const T&, unsigned int);
	TreeNode<T>* removeFromSubtree(const T&, TreeNode<T> *);
	void removeFromSubtreeProc(const T&, TreeNode<T> *&);

	bool hasSameLevels();
	bool isBOT();
	void replaceWithSizeOfSubtree();

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

	TreeNode<T>* copyFrom(const TreeNode<T> *);
	void del(TreeNode<T>*);

	bool compare(const TreeNode<T> *, const TreeNode<T> *) const;
	bool member(const T&, const TreeNode<T> *) const;
	TreeNode<T>* readFromStream(std::istream &);

	TreeNode<char>* parseExpressionHelp(std::string&);
	double calculateExpressionTree(TreeNode<char> *) const;
	T& operHelp(int&, TreeNode<T>*);
	void levelHelp(int, std::vector<T>&, TreeNode<T>*) const;

	void fillGaps(const T&, TreeNode<T> *&, unsigned int);
	T& findmin(TreeNode<T> *);

	void findAllLevels(std::vector<std::set<T>>&, TreeNode<T> *, int);
	bool isBOT(TreeNode<T>*, int, int);
	T replaceWithSizeOfSubtree(TreeNode<T>*);
};

template<class T>
std::ostream& operator<<(std::ostream&, Tree<T>&);
