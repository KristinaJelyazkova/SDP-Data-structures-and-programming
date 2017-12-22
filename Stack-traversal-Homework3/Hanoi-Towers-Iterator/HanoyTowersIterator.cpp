#include<assert.h>
#include<algorithm>
#include<string>
#include"HanoyTowersIterator.h"

// for more information on the idea - check the recursive funstion move() from HanoyTowersRecursion.cpp file

HanoyPlayer::HanoyPlayer(int _numberOfDisks) : numberOfDisks(_numberOfDisks) {
	int k = _numberOfDisks;
	while (k > 0) { // we put the disks on the first tower, the other towers are empty for now
		source.push(k);
		k--;
	}
	info.push(std::pair<int, int>(12, _numberOfDisks)); // we put the first pair in the information stack which represents the parameters of the recursive function move() - source, destination, temp, k (we mark source and destination with 1 and 2 - so 12, and k is the number of disks)
}

bool HanoyPlayer::final() const { // if the source and temp stack are empty, all of the disks are on the destination stack which is our goal
	return (source.empty()) && (temp.empty());
}


void HanoyPlayer::moving(std::stack<int> &from, std::stack<int> &to) { // the actual movement from one tower(stack) to another
	to.push(from.top());
	from.pop();
}


void HanoyPlayer::movingFromTo(int numberFromTo) { // the first part of each pair is a number(12, 13, 23...) that shows from which to which tower we are moving the top disk - for example if pair.first = 31 this means we are moving a disk from the 3rd tower(the temp stack) to the first(the source stack)
	switch (numberFromTo) {
	case 12: {moving(source, destination); break; }
	case 13: {moving(source, temp); break; }
	case 21: {moving(destination, source); break; }
	case 23: {moving(destination, temp); break; }
	case 31: {moving(temp, source); break; }
	case 32: {moving(temp, destination); break; }
	}
}

int HanoyPlayer::changeSecondDigit(int number) const {// the first call of move() in move() we change the order - (source, dest, temp) becomes (temp, dest, source)
	switch (number) {
	case 12: {return 13; break; }
	case 13: {return 12; break; }
	case 21: {return 23; break; }
	case 23: {return 21; break; }
	case 31: {return 32; break; }
	case 32: {return 31; break; }
	}
}

int HanoyPlayer::changeFirstDigit(int number) const { // the last (3rd) call of move() in move() we change the order - (source, dest, temp) becomes (dest, temp, source)
	switch (number) {
	case 12: {return 32; break; }
	case 13: {return 23; break; }
	case 21: {return 31; break; }
	case 23: {return 13; break; }
	case 31: {return 21; break; }
	case 32: {return 12; break; }
	}
}

void HanoyPlayer::makeMove() {
	assert(!info.empty());
	std::pair<int, int> pair = info.top();
	info.pop();

	while(pair.second != 1) { // we actually move something when the k parameter of move() is 1 - the bottom of the recursion
		int fromTo = pair.first;
		info.push(std::pair<int, int>(changeFirstDigit(fromTo), pair.second - 1)); //we change the top of the stack with its 3 subtasks in their reverse order;
		info.push(std::pair<int, int>(fromTo, 1)); //the subtasks are the 3 calls of move() in the recursive function move
		info.push(std::pair<int, int>(changeSecondDigit(fromTo), pair.second - 1)); //look move() in the HanoyTowersRecursion.cpp
		pair = info.top(); 
		info.pop();
	}

	movingFromTo(pair.first); // the first part of each pair is a number(12, 13, 23...) that shows from which to which tower we are moving the top disk - for example if pair.first = 31 this means we are moving a disk from the 3rd tower(the temp stack) to the first(the source stack)
}

void HanoyPlayer::printDisk(int number) const { // pretty centered print of each disks so that we print them all like a tower
	std::string disk;
	for (int i = 0; i < number; i++) {
		disk += "**";
	}
	int spaces = (20 - (number * 2) ) / 2;
	for (int i = 0; i < spaces; i++) {
		std::cout << " ";
	}
	std::cout << disk;
	for (int i = 0; i < spaces; i++) {
		std::cout << " ";
	}
}

void HanoyPlayer::printBoard() const {
	std::cout << "-----------------------------------------------------------\n"; // a line between each step
	std::stack<int> a = source, b = destination, c = temp; // we copy the stacks so we don't lose the information from them after printing each step
	int max = std::max(a.size(), std::max(b.size(), c.size()));
	while (max > 0) { // we print a row with disks from the 3 towers
		if (a.size() == max) {
			printDisk(a.top());
			a.pop();
		}
		else {
			printDisk(0); // we print only spaces
		}
		if (b.size() == max) {
			printDisk(b.top());
			b.pop();
		}
		else {
			printDisk(0);
		}
		if (c.size() == max) {
			printDisk(c.top());
			c.pop();
		}
		else {
			printDisk(0);
		}
		std::cout << std::endl;
		max--;
	}
}