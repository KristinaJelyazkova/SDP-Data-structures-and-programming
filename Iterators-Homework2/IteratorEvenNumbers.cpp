#include"IteratorEvenNumbers.h"

IteratorEvenNumbers::IteratorEvenNumbers(int _end) : current(0), end(_end) {}

int IteratorEvenNumbers::getNext() {

	current = current + 2;
	
	return current;
}

bool IteratorEvenNumbers::more() {
	return (current <= end);
}

