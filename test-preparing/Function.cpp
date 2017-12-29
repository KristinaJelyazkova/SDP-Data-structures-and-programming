template<class E>
class FunctionIterator {
public:
	FunctionIterator(unsigned int, E(*)(unsigned int));
	bool more();
	E& getNext();
private:
	unsigned int current;
	unsigned int end;
	E(*function) (unsigned int);
};

template<class E>
FunctionIterator::FunctionIterator(unsigned int _end, E(*_f)(unsigned int)) :
	current(0), end(_end), function(_f){}

template<class E>
bool FunctionIterator::more() {
	return current < end;
}

template<class E>
E& FunctionIterator::getNext() {
	E& save = f(current);
	current++;
	return save;
}