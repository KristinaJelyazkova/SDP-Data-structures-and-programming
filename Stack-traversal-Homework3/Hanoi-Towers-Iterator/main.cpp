#include"HanoyTowersIterator.h"

void testHanoyPlayer() {
	HanoyPlayer hp(5);
	while (!hp.final()) {
		hp.makeMove();
		hp.printBoard();
	}
}


int main() {
	testHanoyPlayer();
	system("pause");
	return 0;
}
