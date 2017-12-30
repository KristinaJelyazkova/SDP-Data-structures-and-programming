#include<iostream>
#include<stack>
#include<algorithm>

class HanoyPlayer {
private:
	std::stack<std::pair<int, int>> info;
	int numberOfDisks;
	std::stack<int> source, destination, temp;

	void moving(std::stack<int>&, std::stack<int>&);
	void movingFromTo(int);
	void printDisk(int) const;
	int changeSecondDigit(int) const;
	int changeFirstDigit(int) const;
public:
	HanoyPlayer(int);
	bool final() const;
	void makeMove();
	void printBoard() const;
};

HanoyPlayer::HanoyPlayer(int _numberOfDisks) : numberOfDisks(_numberOfDisks) {
	int k = _numberOfDisks;
	while (k > 0) {
		source.push(k);
		k--;
	}
	info.push({ 12, _numberOfDisks });
}

bool HanoyPlayer::final() const {
	return source.empty() && temp.empty();
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
	std::pair<int, int> crr = info.top();
	info.pop();
	while (crr.second != 1) {
		info.push({ changeFirstDigit(crr.first), crr.second - 1 });
		info.push({ crr.first, 1 });
		info.push({ changeSecondDigit(crr.first), crr.second - 1 });
		crr = info.top();
		info.pop();
	}
	movingFromTo(crr.first);
}

void HanoyPlayer::printDisk(int number) const { // pretty centered print of each disks so that we print them all like a tower
	std::string disk;
	for (int i = 0; i < number; i++) {
		disk += "**";
	}
	int spaces = (20 - (number * 2)) / 2;
	for (int i = 0; i < spaces; i++) {
		std::cout << " ";
	}
	std::cout << disk;
	for (int i = 0; i < spaces; i++) {
		std::cout << " ";
	}
}

void HanoyPlayer::printBoard() const {
	std::cout << "-----------------------------------------------------------\n";
	std::stack<int> a = source, b = destination, c = temp;
	int max = std::max(a.size(), std::max(b.size(), c.size()));
	while (max > 0) {
		if (a.size() == max) {
			printDisk(a.top());
			a.pop();
		}
		else {
			printDisk(0);
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