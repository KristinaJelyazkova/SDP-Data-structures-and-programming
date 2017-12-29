#include"LinkedList-Iterator.h"

template<class ElemType>
Node<ElemType>::Node(const ElemType& _data, Node<ElemType> *_next) :
	data(_data), next(_next) {}

template<class ElemType>
LList<ElemType>::LList() : first(nullptr) {}

template<class ElemType>
void LList<ElemType>::copy(const LList<ElemType>& other) {
	first = nullptr;
	if (other.first == nullptr) {
		return;
	}

	Node<ElemType> *otherCurrent = other.first, *current;
	first = new Node<ElemType>(otherCurrent->data, nullptr);
	otherCurrent = otherCurrent->next;
	current = first;

	while (otherCurrent != nullptr) {
		current->next = new Node<ElemType>(otherCurrent->data, nullptr);
		current = current->next;
		otherCurrent = otherCurrent->next;
	}
}

template<class ElemType>
void LList<ElemType>::clear() {
	while (first != nullptr) {
		Node<ElemType> *save = first;
		first = first->next;
		delete save;
	}
}

template<class ElemType>
LList<ElemType>::LList(const LList<ElemType> &other) {
	copy(other);
}

template<class ElemType>
LList<ElemType>::~LList() {
	clear();
}

template<class ElemType>
LList<ElemType>& LList<ElemType>::operator=(const LList<ElemType> &other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

template<class ElemType>
Node<ElemType>* LList<ElemType>::locate(unsigned int index) const {
	Node<ElemType> *current = first;
	while (current != nullptr && index > 0) {
		current = current->next;
		index--;
	}
	return current;
}

template<class ElemType>
void LList<ElemType>::push(const ElemType& data) {
	first = new Node<ElemType>(data, first);
}

template<class ElemType>
const ElemType& LList<ElemType>::peek() const {
	return first->data;
}

template<class ElemType>
bool LList<ElemType>::pop() {
	if (first == nullptr) {
		return false;
	}
	Node<ElemType> *save = first;
	first = first->next;
	delete save;

	return true;
}

template<class ElemType>
bool LList<ElemType>::remove(unsigned int index) {
	if (index == 0) {
		return pop();
	}
	Node<ElemType> *previous = locate(index - 1);

	if (previous == nullptr || previous->next == nullptr) {
		return false;
	}

	Node<ElemType> *save = previous->next;
	previous->next = save->next;
	delete save;

	return true;
}

template<class ElemType>
bool LList<ElemType>::addAt(unsigned int index, const ElemType& x) {
	if (index == 0) {
		push(x);
		return true;
	}

	Node<ElemType> *tmp = locate(index - 1);
	if (tmp == nullptr) {
		return false;
	}

	tmp->next = new Node<ElemType>(x, tmp->next);
	return true;
}

template<class ElemType>
bool LList<ElemType>::empty() const{
	return first == nullptr;
}

template<class ElemType>
void LList<ElemType>::pushBack(const ElemType& data) {
	if (first == nullptr) {
		push(data);
		return;
	}

	Node<ElemType> *current = first;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new Node<ElemType>(data, nullptr);
}

template<class ElemType>
const ElemType& LList<ElemType>::operator[] (unsigned int index) const{
	Node<ElemType> *tmp = locate(index);
	assert(tmp != nullptr);
	return tmp->data;
}

template<class ElemType>
ListIterator<ElemType> LList<ElemType>::begin() {
	ListIterator<ElemType> li(first);
	return li;
}

template<class ElemType>
ListIterator<ElemType>::ListIterator(Node<ElemType> *first) {
	nextToBeAccessed = first;
}

template<class ElemType>
ElemType& ListIterator<ElemType>::getNext() {
	assert(nextToBeAccessed != nullptr);
	ElemType& data = nextToBeAccessed->data;
	nextToBeAccessed = nextToBeAccessed->next;
	return data;
}

template<class ElemType>
bool ListIterator<ElemType>::more() {
	return nextToBeAccessed != nullptr;
}

