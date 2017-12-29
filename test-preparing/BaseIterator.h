#pragma once
#ifndef _BASE_IT_
#define _BASE_IT_

template<class ElemType>
class BaseIterator {
public:
	virtual ElemType& getNext() = 0;
	virtual bool more() = 0;
};

#endif