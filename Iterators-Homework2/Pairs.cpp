#include<iostream>
#include"Pairs.h"

std::ostream& operator << (std::ostream& out, std::pair<int, int> p) {
	return out << "(" << p.first << "," << p.second << ")";
}

PairsIterator::PairsIterator(int _max) : max(_max) {}

std::pair<int, int> PairsIterator::getNext() {
	std::pair<int, int> save = current;
	if (current.first == current.second) {
		current.first = 0;
		current.second++;
	}
	else {
		current.first++;
	}
	return save;
}

bool PairsIterator::more() {
	return current.first + current.second <= max;
}