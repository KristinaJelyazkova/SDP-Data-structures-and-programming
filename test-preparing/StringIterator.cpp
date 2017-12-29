#include"StringIterator.h"
#include<cassert>

StringIterator::StringIterator(std::string _s) :
	s(_s), current(0){}

bool StringIterator::more() const {
	return current < s.size();
}

char& StringIterator::getNext() {
	assert(current < s.size());
	return s[current++];
}

bool StringIterator::hasPrevious() const {
	return current > 0;
}

char& StringIterator::getPrevious() {
	assert(current > 0);
	return s[current--];
}