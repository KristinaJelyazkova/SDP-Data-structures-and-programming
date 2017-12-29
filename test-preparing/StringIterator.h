#pragma once
#ifndef _STR_IT_
#define _STR_IT_

#include<string>

class StringIterator {
public:
	StringIterator(std::string);
	bool more() const;
	char& getNext();
	bool hasPrevious() const;
	char& getPrevious();
private:
	std::string s;
	unsigned int current;
};

#endif