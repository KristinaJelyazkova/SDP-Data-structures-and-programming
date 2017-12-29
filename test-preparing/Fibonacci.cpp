class Fibonacci {
public:
	Fibonacci(int);
	bool more();
	int getNext();
private:
	int current, previous, end;
};

Fibonacci::Fibonacci(int _end) : end(_end), current(1), previous(0){}

bool Fibonacci::more() {
	return current < end;
}

int Fibonacci::getNext() {
	int save = current;
	current = current + previous;
	previous = save;
	return save;
}