#pragma once
#ifndef _LLIST_
#define _LLIST_

#include "BaseIterator.h"

template<class ElemType>
struct Node {
	ElemType data;
	Node<ElemType> *next;
	Node(const ElemType&, Node<ElemType> *);
};

template<class ElemType>
class ListIterator : public BaseIterator<ElemType> {
public:
	ListIterator(Node<ElemType>*);
	ElemType& getNext();
	bool more();
private:
	Node<ElemType> *nextToBeAccessed;
};

template<class ElemType>
class LList {
public:
	LList();
	LList(const LList&);

	void push(const ElemType&);
	const ElemType& peek() const;
	bool pop();
	bool remove(unsigned int);
	bool addAt(unsigned int, const ElemType&);
	bool empty() const;
	void pushBack(const ElemType&);

	const ElemType& operator [](unsigned int) const;

	LList<ElemType>& operator = (const LList<ElemType> &);

	ListIterator<ElemType> begin();

	~LList();
private:
	Node<ElemType> *first;

	void copy(const LList<ElemType>&);
	void clear();

	Node<ElemType> *locate(unsigned int) const;
};

#endif