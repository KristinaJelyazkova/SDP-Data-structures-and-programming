#include"ArrayIterator.h"

template<class ElemType>
ArrayIterator<ElemType>::ArrayIterator(ElemType *_arr, size_t _size) :
	arr(_arr), size(_size), current(0) {}

template<class ElemType>
ElemType& ArrayIterator<ElemType>::getNext() {
	assert(current < size);
	return arr[current++];
}

template<class ElemType>
bool ArrayIterator<ElemType>::more() {
	return current < size;
}