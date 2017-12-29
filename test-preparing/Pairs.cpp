#include<iostream>

class Pairs {
public:
	Pairs(int);
	bool more();
	std::pair<int, int> getNext();
private:
	std::pair<int, int> current;
	int max;
};

std::ostream& operator<< (std::ostream&, std::pair<int, int>);

Pairs::Pairs(int _max) : max(_max) {
	current = { 0,0 };
}

bool Pairs::more() {
	return current.first <= max;
}

std::pair<int, int> Pairs::getNext() {
	std::pair<int, int> save = current;
	if (current.first + current.second < max) {
		current.second++;
	}
	else {
		current.first++;
		current.second = 0;
	}
	return save;
}