#ifndef _BASEITERATOR_
#define _BASEITERATOR_

template <typename ElemType>
class BaseIterator {
public:
	virtual ElemType& getNext() = 0;
	virtual bool more() const = 0;
	//virtual bool hasPrevious() = 0;
	//virtual ElemType& getPrevious() = 0;
};

#endif
