#include"StringIterator.h"
#include<cassert>
#include<iostream>
#include<string>

template <class ElemType>
StringIterator<ElemType>::StringIterator(char *_str) : current(0) {
	str = new ElemType[strlen(_str) + 1];
	int i = 0;
	while (_str[i] != '\0') {
		str[i] = _str[i];
		i++;
	}
	str[i] = '\0';
}

template <class ElemType>
ElemType& StringIterator<ElemType>::getNext() {
	assert(str[current] != '\0');
	return str[current++];
}

template <class ElemType>
bool StringIterator<ElemType>::more() const {
	return str[current] != '\0';
}

template <class ElemType>
bool StringIterator<ElemType>::hasPrevious() const {
	return current > 0;
}

template <class ElemType>
ElemType& StringIterator<ElemType>::getPrevious() {
	assert(current > 0);
	return str[current--];
}