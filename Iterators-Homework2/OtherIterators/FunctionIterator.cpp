#include"FunctionIterator.h"
#include<cassert>

template<typename E>
FunctionIterator<E>::FunctionIterator(E(*_function) (unsigned int), int _end) : current(0), end(_end){
	function = _function;
}

template<typename E>
E FunctionIterator<E>::getNext() {
	assert(current < end);
	int save = current;
	current++;
	return function(save);
}

template<typename E>
bool FunctionIterator<E>::more() const {
	return current < end;
}

template<typename E>
bool FunctionIterator<E>::hasPrevious() const {
	return current > 0;
}

template<typename E>
E FunctionIterator<E>::getPrevious() {
	assert(current > 0);
	int save = current;
	current--;
	return function(save);
}