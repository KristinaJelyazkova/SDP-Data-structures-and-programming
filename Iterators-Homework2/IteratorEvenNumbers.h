#ifndef _ITEVENNUM_
#define _ITEVENNUM_

#include"BaseIterator.h"

class IteratorEvenNumbers {
public:
	IteratorEvenNumbers(int);
	int getNext();
	bool more();
private:
	int current;
	int end;
};

#endif

