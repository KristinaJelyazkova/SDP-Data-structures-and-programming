#ifndef _FUNCTIONITERATOR_
#define _FUNCTIONITERATOR_

#include"BaseIterator.h"

template<typename E>
class FunctionIterator {
public:
	FunctionIterator(E(*_function) (unsigned int), int);
	E getNext();
	bool more() const;
	bool hasPrevious() const;
	E getPrevious();
private:
	E(*function) (unsigned int);
	int current, end;
};

#endif