#ifndef _ARRAYITERATOR_
#define _ARRAYITERATOR_

#include"BaseIterator.h"

template<typename T>
class ArrayIterator : public BaseIterator<T> {
public:
	ArrayIterator(T*, size_t);
	T& getNext();
	bool more() const;
	bool hasPrevious() const;
	T& getPrevious();
private:
	T* arr;
	size_t size;
	size_t current;
};

#endif
