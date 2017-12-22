#ifndef _HTIterator_
#define _HTIterator_

// for more information on the idea - check the recursive funstion move() from HanoyTowersRecursion.cpp file

#include<iostream>
#include<stack>

class HanoyPlayer {
public:
	HanoyPlayer(int);
	bool final() const;
	void makeMove();
	void printBoard() const;

private:
	std::stack < std::pair <int, int> > info; // stack showing what is the movement we have to make - the pair.first number shows from which to which tower we have to move a disk (these are the first two parameters of the recursive move()) and the pair.second number shows when is the time to move(this is the k parameter of move()) - we have to move when k is 1 - this is the bottom of the recursion
	std::stack<int> source, destination, temp; // the 3 towers
	int numberOfDisks;

	void moving(std::stack<int>&, std::stack<int>&);
	void movingFromTo(int);
	void printDisk(int) const;
	int changeSecondDigit(int) const;
	int changeFirstDigit(int) const;
};

#endif