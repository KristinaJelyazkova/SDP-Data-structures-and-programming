#include<assert.h>
#include"ErmitIterator.h"

Ermit::Ermit(double _x, unsigned int _n) : x(_x), n(_n) {
	info.push(std::pair<double, unsigned int>(1, 0));
	info.push(std::pair<double, unsigned int>(2 * x, 1));
}

bool Ermit::foundResult() const {
	return info.top().second > n;
}

double Ermit::getNext() {
	assert(!info.empty());
	std::pair<double, int> pair1 = info.top();
	assert(pair1.second <= n);
	info.pop();
	assert(!info.empty());
	std::pair<double, int> pair2 = info.top();
	info.pop();
	info.push(pair1);
	double nextValue = (2 * x * pair1.first) + (2 * pair1.second * pair2.first);
	info.push(std::pair<double, unsigned int>(nextValue, pair1.second + 1));
	return pair1.first;
}