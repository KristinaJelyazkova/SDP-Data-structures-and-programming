#ifndef _FIBONACHI_
#define _FIBONACHI_

#include"BaseIterator.h"

class FibonachiIterator : public BaseIterator<int> {
public:
	FibonachiIterator(int);
	int& getNext();
	bool more();
private:
	int current, previous, end;
};

#endif;
