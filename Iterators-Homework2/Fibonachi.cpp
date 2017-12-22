#include"Fibonachi.h"
FibonachiIterator :: FibonachiIterator(int _end) : current(1), previous(0), end(_end){}

int& FibonachiIterator :: getNext() {
	int save = current;
	current = current + previous;
	previous = save;
	return current;
}

bool FibonachiIterator :: more() {
	return (current + previous <= end);
}