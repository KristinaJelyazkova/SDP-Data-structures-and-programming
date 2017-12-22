#include<iostream>
#include"IteratorEvenNumbers.h"
#include"Fibonachi.h"
#include"Pairs.h"

void testIteratorEvenNumbers() {
	IteratorEvenNumbers t(20);
	while (t.more()) {
		std::cout << t.getNext() << " ";
	}
	std::cout << std::endl;
}

void testFibonachiIterator() {
	FibonachiIterator t(100);
	while (t.more()) {
		std::cout << t.getNext() << " ";
	}
	std::cout << std::endl;
}

void testPairsIterator() {
	PairsIterator t(100);
	while (t.more()) {
		std::cout << t.getNext() << " ";
	}
	std::cout << std::endl;
}

int main() {
	testIteratorEvenNumbers();
	testFibonachiIterator();
	testPairsIterator();
	system("pause");
	return 0;
}