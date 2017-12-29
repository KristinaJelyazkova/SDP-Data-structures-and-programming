class IteratorEvenNumbers {
public:
	IteratorEvenNumbers(int);
	bool more();
	int getNext();
private:
	int current;
	int end;
};

IteratorEvenNumbers::IteratorEvenNumbers(int _end) : current(0), end(_end){}

bool IteratorEvenNumbers::more() {
	return current < end;
}

int IteratorEvenNumbers::getNext() {
	int save = current;
	current += 2;
	return save;
}