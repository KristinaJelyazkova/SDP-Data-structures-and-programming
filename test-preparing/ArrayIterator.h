#pragma once
#ifndef _ARRAY_IT_
#define _ARRAY_IT_

#include "BaseIterator.h"

template<class ElemType>
class ArrayIterator : public BaseIterator<ElemType> {
public:
	ArrayIterator(ElemType *, size_t);
	ElemType& getNext();
	bool more();
private:
	ElemType *arr;
	size_t size;
	size_t current;
};

#endif