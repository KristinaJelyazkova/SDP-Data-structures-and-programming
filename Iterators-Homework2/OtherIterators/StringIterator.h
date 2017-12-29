#ifndef _STRINGITERATOR_
#define _STRINGITERATOR_

#include"BaseIterator.h"

template <typename ElemType>
class StringIterator : public BaseIterator<ElemType> {
public:
	StringIterator(char *);
	ElemType& getNext();
	bool more() const;
	bool hasPrevious() const;
	ElemType& getPrevious();
private:
	ElemType *str;
	size_t current;
};

#endif