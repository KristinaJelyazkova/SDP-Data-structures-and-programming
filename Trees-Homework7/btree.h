#ifndef __BTREE_H
#define __BTREE_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>

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
struct task
{
	task() {}
	task(TreeNode<T> *_n, bool _p) : node(_n), toPrintNow(_p) {}
	TreeNode<T> *node;
	bool toPrintNow;
};

template <class T>
class PredIterator // обхожда само тези елементи от дървото, които изпълняват предиката
{
public:
	PredIterator(TreeNode<T> *root, bool (*_pred) (const T&));

	T operator * ();
	bool operator == (const PredIterator<T>&);
	bool operator != (const PredIterator<T>&);
	PredIterator<T>& operator ++ (int);


private:
	std::stack<task<T>> s;
	bool (*pred) (const T&);

	void windStack();
};

template <class T>
class LeafIterator // обхожда листата на дървото отляво надясно
{
public:
	LeafIterator(TreeNode<T> *root);

	T operator * ();
	bool operator == (const LeafIterator<T>&);
	bool operator != (const LeafIterator<T>&);
	LeafIterator<T>& operator ++ (int);


private:
	std::stack<task<T>> s;

	void windStack();
};

template <class T>
class LevelIterator { // BFS- обхождане в широчина
public:
	LevelIterator(TreeNode<T> *root);

	T operator * ();
	bool operator == (const LevelIterator<T>&);
	bool operator != (const LevelIterator<T>&);
	LevelIterator<T>& operator ++ (int);

private:
	std::queue< TreeNode<T> * > q;
};

template <class T>
class LRoTreeIterator // обхожда първото лявото поддърво, после дясното и накрая корена
{
public:
	LRoTreeIterator(TreeNode<T> *root);

	T operator * ();
	bool operator == (const LRoTreeIterator<T>&);
	bool operator != (const LRoTreeIterator<T>&);
	LRoTreeIterator<T>& operator ++ (int);


private:
	std::stack<task<T>> s;

	void windStack();
};

template <class T>
class oRLTreeIterator // обхожда първото корена, после дясното поддърво и накрая лявото
{
public:
	oRLTreeIterator(TreeNode<T> *root);

	T operator * ();
	bool operator == (const oRLTreeIterator<T>&);
	bool operator != (const oRLTreeIterator<T>&);
	oRLTreeIterator<T>& operator ++ (int);


private:
	std::stack<task<T>> s;

	void windStack();
};


template <class T>
class LRoRTreeIterator // обхожда първо лявото поддърво, после корена и накрая дясното
{
public:
	LRoRTreeIterator(TreeNode<T> *root);

	T operator * ();
	bool operator == (const LRoRTreeIterator<T>&);
	bool operator != (const LRoRTreeIterator<T>&);
	LRoRTreeIterator<T>& operator ++ (int);


private:
	std::stack<task<T>> s;

	void windStack();
};


template <class T>
class BTree
{
public:


	void levelsPrint(std::ostream&);

	template <class I> // връща различни итератори според това как извикаме begin< iterator_name<T> >
	I begin();

	template <class I>
	I end();

	PredIterator<T> begin(bool(*pred) (const T&));
	PredIterator<T> end(bool(*pred) (const T&));

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


	void printWithStack(std::ostream &out);

	~BTree();

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

};
template <class T>
std::ostream& operator << (std::ostream&, const BTree<T>&);

#endif
