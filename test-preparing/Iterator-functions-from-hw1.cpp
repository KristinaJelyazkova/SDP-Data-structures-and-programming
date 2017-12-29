template<class Iterator, class T>
int count(Iterator it, T x) {
	int counter = 0;
	while (it.more()) {
		if (it.getNext() == x) {
			counter++;
		}
	}
	return counter;
}

template<class Iterator, class T>
void map(Iterator it, T(*f) (T&)) {
	while (it.more()) {
		T& tmp = it.getNext();
		tmp = f(tmp);
	}
}

template<class Iterator, class T>
bool duplicates(Iterator it) {
	while (it.more()) {
		T current = it.getNext();
		Iterator help = it;
		while (help.more()) {
			if (current == help.getNext()) {
				return true;
			}
		}
	}
	return false;
}

template<class Iterator, class T>
bool isSorted(Iterator it) {
	T current, next;
	int flag = 0;
	if (!it.more()) {
		return true;
	}
	else {
		current = it.getNext();
	}
	if (!it.more()) {
		return true;
	}
	else {
		next = it.getNext();
	}
	if (current < next) {
		flag = -1;
	}
	if (current > next) {
		flag = 1;
	}
	while (it.more()) {
		current = next;
		next = it.getNext();
		if (flag == 0) {
			if (current < next) {
				flag = -1;
			}
			if (current > next) {
				flag = 1;
			}
		}
		if ((current > next && flag == -1) || (current < next && flag == 1)) {
			return false;
		}
	}
	return true;
}

template<class Iterator, class T>
bool palindrom(Iterator it) {
	std::vector<T> save;
	Iterator help = it;
	while (help.more()) {
		save.push_back(help.getNext());
	}
	while (it.more()) {
		if (save.back() != it.getNext()) {
			return false;
		}
		save.pop_back();
	}
	return true;
}