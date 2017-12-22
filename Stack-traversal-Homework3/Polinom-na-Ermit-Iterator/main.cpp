#include"ErmitIterator.h"
//#include"Recursion.cpp"

void testErmitIterator() {
	Ermit it(2, 10);
	int i = 1;
	while (!it.foundResult()) {
		std::cout << "H" << i << "(2) = " << it.getNext() << std::endl;
		i++;
	}
}

int main() {
	testErmitIterator();
	system("pause");
	return 0;
}