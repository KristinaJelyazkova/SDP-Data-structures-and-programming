#include<iostream>

template<typename T>
struct box {
	T data;
	box *next;

	box(T, box*);
};

template<typename T>
box<T>::box(T _data, box<T> *_next) : data(_data), next(_next){}

template<typename T>
int count(box<T> *first, T x) {
	int counter = 0;
	while (first != nullptr) {
		if(first->data == x) counter++;
		first = first->next;
	}
	return counter;
}

template<typename T>
box<T>* range(T x, T y) {
	if (x > y) {
		return nullptr;
	}
	box<T> *first = new box<T>(x, range(x + 1, y));
	return first;
}

template<typename T>
void removeAll(box<T> *&first, T x) {
	box<T> *current = first, *parent = nullptr;
	while (current != nullptr) {
		if (current->data == x) {
			if (parent == nullptr) {
				box<T> *save = current;
				first = first->next;
				current = first;
				delete save;
			}
			else {
				box<T> *save = current;
				parent->next = current->next;
				delete save;
				current = parent->next;
			}
		}
		else {
			current = current->next;
			if (parent == nullptr) {
				parent = first;
			}
			else {
				parent = parent->next;
			}
		}
	}
}

template<typename T>
void print(box<T> *first) {
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

template<typename T>
void append(box<T> *&l1, box<T> *l2) {
	if (l2 == nullptr) {
		return;
	}
	if (l1 == nullptr) {
		l1 = new box<T>(l2->data, nullptr);
		box<T> *current = l1;
		l2 = l2->next;
		while (l2 != nullptr) {
			current->next = new box<T>(l2->data, nullptr);
			current = current->next;
			l2 = l2->next;
		}
		return;
	}
	box<T> *current = l1;
	while (current->next != nullptr) {
		current = current->next;
	}
	while (l2 != nullptr) {
		current->next = new box<T>(l2->data, nullptr);
		current = current->next;
		l2 = l2->next;
	}
}

template<typename T>
box<T> *concat(box<T> *l1, box<T> *l2) {
	box<T> *result = nullptr, *current = nullptr;
	while (l1 != nullptr) {
		if (current == nullptr) {
			current = new box<T>(l1->data, nullptr);
			result = current;
			l1 = l1->next;
		}
		else {
			current->next = new box<T>(l1->data, nullptr);
			current = current->next;
			l1 = l1->next;
		}
	}
	while (l2 != nullptr) {
		if (current == nullptr) {
			current = new box<T>(l2->data, nullptr);
			result = current;
			l2 = l2->next;
		}
		else {
			current->next = new box<T>(l2->data, nullptr);
			current = current->next;
			l2 = l2->next;
		}
	}
	return result;
}

void map(box<int> *&l, int(*f) (int)) {
	box<int> *current = l;
	while (current != nullptr) {
		current->data = f(current->data);
		current = current->next;
	}
}

int mult2(int x) {
	return (x * 2);
}

template<typename T>
box<T> *reverse(box<T> *l) {
	if (l == nullptr) {
		return nullptr;
	}
	if (l->next == nullptr) {
		return new box<T>(l->data, nullptr);
	}
	box<T> *last = l->next, *previous = l;
	while (last->next != nullptr) {
		last = last->next;
		previous = previous->next;
	}
	previous->next = nullptr;
	return new box<T>(last->data, reverse(l));
}

template<typename T>
bool duplicates(box<T> *l) {
	if (l == nullptr || l->next == nullptr) {
		return l;
	}
	box<T> *crr;
	while (l->next != nullptr) {
		crr = l->next;
		while (crr != nullptr) {
			if (l->data == crr->data) {
				return true;
			}
			crr = crr->next;
		}
		l = l->next;
	}
	return false;
}

template<typename T>
void removeDuplicates(box<T> *&l) {
	if (l == nullptr || l->next == nullptr) {
		return;
	}
	bool flag = false;
	box<T> *crr = l->next, *par = l;
	while (crr != nullptr) {
		if (l->data == crr->data) {
			/*if (par == l) {
				box<T> *save1 = l, *save2 = l->next;
				l = l->next->next;
				par = l;
				delete save1;
				delete save2;
				if(l != nullptr) crr = l->next;
				else return;
			}
			else {*/
				flag = true;
				box<T> *save2 = crr;
				par->next = crr->next;
				delete save2;
				crr = par->next;
			//}
		}
		else {
			crr = crr->next;
			par = par->next;
		}
	}
	if (flag) {
		box<T> *save1 = l;
		l = l->next;
		delete save1;
		removeDuplicates(l);
	}
	else {
		removeDuplicates(l->next);
	}
}

template<typename T>
bool isAscending(box<T> *l) {
	if (l == nullptr || l->next == nullptr) {
		return true;
	}
	if (l->data > l->next->data) {
		return false;
	}
	return isAscending(l->next);
}

template<typename T>
bool isDescending(box<T> *l) {
	if (l == nullptr || l->next == nullptr) {
		return true;
	}
	if (l->data < l->next->data) {
		return false;
	}
	return isDescending(l->next);
}

template<typename T>
bool isSorted(box<T> *l) {
	if (l == nullptr || l->next == nullptr) {
		return true;
	}
	if (l->data <= l->next->data) {
		return isAscending(l->next);
	}
	if (l->data >= l->next->data) {
		return isDescending(l->next);
	}
}

template<typename T>
bool isPalindrom(box<T> *l) {
	box<T> *copyCrr = nullptr, *crr = l, *save = nullptr;
	while (crr != nullptr) {
		if (save == nullptr) {
			copyCrr = new box<T>(crr->data, nullptr);
			save = copyCrr;
		}
		else {
			copyCrr->next = new box<T>(crr->data, nullptr);
			copyCrr = copyCrr->next;
		}
		crr = crr->next;
	}
	//print<T>(save);
	box<T> *revL = reverse<T>(save);
	//print<T>(save);
	while (l != nullptr) {
		if (l->data != revL->data) {
			return false;
		}
		revL = revL->next;
		l = l->next;
	}
	return true;
}

int main() {
	//print<int>(range<int>(10, 30));

	box<int> *first = new box<int>(10,
		new box<int>(10,
			new box<int>(10,
				new box<int>(30,
					new box<int>(10,
						new box<int>(10,
							new box<int>(20,
								new box<int>(30,
									new box<int>(50, 
										new box<int>(50, 
											new box<int>(10,
												new box<int>(90,
													new box<int>(90,
														nullptr)))))))))))));
	//removeAll<int>(first, 10);
	//print<int>(first);

	box<int> *l2 = new box<int>(-2,
		new box<int>(-3,
			new box<int>(5,
				new box<int>(8,
					new box<int>(-3,
						new box<int>(-2,
							nullptr))))));
	//first = nullptr;
	//l2 = nullptr;

	//append<int>(first, l2);
	//print<int>(first);

	//print<int>(concat<int>(first, l2));

	//map(l2, mult2);
	//print<int>(l2);
	//print<int>(reverse(l2));

	//std::cout << duplicates(l2);

	//removeDuplicates<int>(first);
	//print<int>(first);

	//std::cout << isSorted<int>(l2) << std::endl;

	std::cout << isPalindrom<int>(l2) << std::endl;

	system("pause");
	return 0;
}