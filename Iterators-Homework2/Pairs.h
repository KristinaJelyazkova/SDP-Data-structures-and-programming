#ifndef _PAIRS_
#define _PAIRS_

#include<iostream>
#include"BaseIterator.h"

class PairsIterator {
public:
	PairsIterator(int);
	std::pair<int,int> getNext();
	bool more();
private:
	std::pair<int, int> current;
	int max;
};

std::ostream& operator << (std::ostream&, std::pair<int, int>);

#endif;

