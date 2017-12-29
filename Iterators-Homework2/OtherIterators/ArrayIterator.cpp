#include"ArrayIterator.h"
#include<cassert>

template<typename T>
ArrayIterator<T>::ArrayIterator(T* _arr, size_t _size) : arr(_arr), size(_size), current(0) {}

template<typename T>
T& ArrayIterator<T>::getNext() {
	assert(current < size);
	return arr[current++];
}

template<typename T>
bool ArrayIterator<T>::more() const {
	return current < size;
}

template<typename T>
bool ArrayIterator<T>::hasPrevious() const {
	return current != 0;
}

template<typename T>
T& ArrayIterator<T>::getPrevious() {
	assert(current != 0);
	return arr[--current];
}