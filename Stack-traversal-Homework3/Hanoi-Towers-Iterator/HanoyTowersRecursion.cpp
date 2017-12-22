#include<iostream>
#include<stack>
#include<iomanip>
#include<algorithm>
#include<string>

std::stack<int> a, b, c;

void printDisk(int size) {
	std::string disk;
	for (int i = 0; i < size; i++) {
		disk += "**";
	}
	int end = (20 - (size * 2)) / 2;
	for (int i = 0; i < end; i++) {
		std::cout << " ";
	}
	std::cout << disk;
	for (int i = 0; i < end; i++) {
		std::cout << " ";
	}
}


void print() {
	std::stack<int> a1 = a, b1 = b, c1 = c;
	int max = std::max(a1.size(), std::max(b1.size(), c1.size()));
	while (max > 0) {
		if (a1.size() == max) {
			printDisk(a1.top());
			a1.pop();
		}
		else {
			printDisk(0);
		}
		if (b1.size() == max) {
			printDisk(b1.top());
			b1.pop();
		}
		else {
			printDisk(0);
		}
		if (c1.size() == max) {
			printDisk(c1.top());
			c1.pop();
		}
		else {
			printDisk(0);
		}
		std::cout << std::endl;
		max--;
	}
}

void move(std::stack<int> &source, std::stack<int> &dest, std::stack<int> &temp, int k) { // the recursive way
	if (k == 1) { // bottom of the recursion - k is pair.second in the info stack
		dest.push(source.top()); // the actual movement happens right here - so this is one step
		source.pop();
		print();
		std::cout << std::endl << std::endl;
		return;
	}
	move(source, temp, dest, k - 1); // the 3 subtasks
	move(source, dest, temp, 1); // the order shows what to push in the info stack as pair.first number
	move(temp, dest, source, k - 1); // the last parameter shows what to push in the info stack as pair.second compared to what was in the previous pair.second - 1 or decremenated
}

/*int main() {
	for (int i = 3; i > 0; i--) {
		a.push(i);
	}
	/for (int i = 5; i > 0; i--) {
	b.push(i);
	}
	for (int i = 7; i > 0; i--) {
	c.push(i);
	}/
	move(a, b, c, 3);
	//print();
	system("pause");
	return 0;
}*/