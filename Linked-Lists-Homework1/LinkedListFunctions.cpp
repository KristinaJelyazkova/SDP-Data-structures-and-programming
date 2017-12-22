#include<iostream>
#include<vector>

typedef int (*function) (int);

template <typename T>
struct box {
	T data;
	box* next;
	box(T _data, box* _next) : data(_data), next(_next){}
};

template <typename T>
int count(box<T>* first, T x) {
	int counter = 0;
	while (first != nullptr) {
		if (first->data == x) counter++;
		first = first->next;
	}
	return counter;
}

box<int>* range(int x, int y) {
	box<int> *first = nullptr, *cur, *par = first;
	if (x < y) {
		first = new box<int>(x, nullptr);
		x++;
		par = first;
	}
	while (x <= y) {
		cur = new box<int>(x, nullptr);
		par->next = cur;
		par = cur;
		x++;
	}
	return first;
}

template <typename T>
void removeAll(box<T> *&first, const T& x) {
	while (first != nullptr && first->data == x) {
		box<T> *save = first;
		first = first->next;
		delete save;
	}
	box<T> *cur = first, *save2;
	if (cur == nullptr) return;
	while (cur->next != nullptr) {
		while (cur->next != nullptr && cur->next->data == x) {
			save2 = cur->next;
			cur->next = cur->next->next;
			delete save2;
		}
		if (cur->next == nullptr) return;
		cur = cur->next;
	}
}

template <typename T>
box<T>* concat(box<T> * b1, box<T> *b2) {
	box<T> *first;
	if (b1 != nullptr) {
		first = new box<T>(b1->data, nullptr);
		b1 = b1->next;
	}
	else if (b2 != nullptr) {
		first = new box<T>(b2->data, nullptr);
		b2 = b2->next;
	}
	else first = nullptr;
	box<T> *par = first, *cur;
	while (b1 != nullptr) {
		cur = new box<T>(b1->data, nullptr);
		b1 = b1->next;
		par->next = cur;
		par = cur;
	}
	while (b2 != nullptr) {
		cur = new box<T>(b2->data, nullptr);
		b2 = b2->next;
		par->next = cur;
		par = cur;
	}
	return first;
}

template <typename T>
void append(box<T> *&b1, box<T> *b2) {
	if (b2 == nullptr) return;
	box<T> *cur = b1;
	if (cur == nullptr) {
		cur = new box<T>(b2->data, nullptr);
		b2 = b2->next;
		box<T> *par = cur;
		while (b2 != nullptr) {
			cur = new box<T>(b2->data, nullptr);
			b2 = b2->next;
			par->next = cur;
			par = cur;
		}
		return;
	}
	while (cur->next != nullptr) cur = cur->next;
	box<T> *par = cur;
	while (b2 != nullptr) {
		cur = new box<T>(b2->data, nullptr);
		b2 = b2->next;
		par->next = cur;
		par = cur;
	}
}

template<typename T>
void map(box<T> *&first, T(*function)(T)) {
	box<T> *cur = first;
	while (cur != nullptr) {
		cur->data = function(cur->data);
		cur = cur->next;
	}
}

template <typename T>
void reverse(box<T> *&first) {			/// 3 POINTERS!!!!!!!!
	if (first == nullptr || first->next == nullptr) return;
	if (first->next->next == nullptr) {
		first->next->next->next = first->next;
		first->next = nullptr;
		first = first->next->next;
		return;
	}
	box<T> *save1 = first, 
		*save2 = first->next, 
		*save3 = first->next->next;
	save1->next = nullptr;
	while (save3 != nullptr) {
		save2->next = save1;
		first = save3;
		save1 = save2;
		save2 = save3;
		if (save3->next == nullptr) {
			save2->next = save1;
			return;
		}
		save3 = save3->next;
		save2->next = save1;
	}
}

template <typename T>
bool duplicates(box<T> *first) {
	if (first == nullptr || first->next == nullptr) return false;
	box<T> *cur = first, *other = first->next;
	while (cur->next != nullptr) {
		other = cur->next;
		while (other != nullptr) {
			if (cur->data == other->data)
				return true;
			other = other->next;
		}
		cur = cur->next;
	}
	return false;
}

template <typename T>
void removeDuplicates(box<T> *&first) {
	if (first == nullptr || first->next == nullptr) return;
	box<T> *cur = first, *other = first->next, *par = cur, *save = cur;
	while (cur != nullptr && cur->next != nullptr) {
		par = cur;
		other = cur->next;
		while (other != nullptr) {
			if (cur->data == other->data) {
				save = other;
				par->next = other->next;
				other = other->next;
				delete save;
			}
			else {
				par = other;
				other = other->next;
			}
		}
		cur = cur->next;
	}
}

template <typename T>
bool isSorted(box<T> *first) {
	if (first == nullptr || first->next == nullptr) return true;
	while(first != nullptr && first->data == first->next->data)
		first = first->next;
	if (first == nullptr) return true;
	if(first->data <= first->next->data) {
		first = first->next;
		while (first->next != nullptr) {
			if (first->data > first->next->data)
				return false;
			first = first->next;
		}
		return true;
	}
	else {
		first = first->next;
		while (first->next != nullptr) {
			if (first->data < first->next->data)
				return false;
			first = first->next;
		}
		return true;
	}
}

template <typename T>
bool isPalindrom(box<T> *first) {
	if (first == nullptr || first->next == nullptr) return true;
	if (first->next->next == nullptr) {
		if (first->data == first->next->data) return true;
		else return false;
	}
	std::vector<T> save;
	box<T> *tmp = first->next;
	save.push_back(first->data);
	while (tmp != nullptr && tmp->next != nullptr) {
		first = first->next;
		save.push_back(first->data);
		tmp = tmp->next->next;
	}
	first = first->next;
	if (tmp == nullptr) {
		save.pop_back();
	}
	while (first != nullptr) {
		if (first->data != save.back()) 
			return false;
		save.pop_back();
		first = first->next;
	}
	return true;
}

void testCount() {
	box<int> *first, *par, *cur;
	first = new box<int>(2, nullptr);
	par = new box<int>(3, nullptr);
	first->next = par;
	cur = new box<int>(4, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	std::cout << count(first, 3) << std::endl;
}

void testRange() {
	box<int> *first = range(5, 20);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

void testRemoveAll() {
	box<int> *first, *par, *cur;
	first = new box<int>(3, nullptr);
	par = new box<int>(3, nullptr);
	first->next = par;
	cur = new box<int>(4, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	removeAll(first, 3);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

void testConcat() {
	box<int> *first = range(5, 20),
		*second = range(21, 40),
		*result = concat(first, second);

	while (result != nullptr) {
		std::cout << result->data << " ";
		result = result->next;
	}
	std::cout << std::endl;
}

void testAppend() {
	box<int> *first = range(5, 20),
		*second = range(21, 40);
	append(first, second);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
	while (second != nullptr) {
		std::cout << second->data << " ";
		second = second->next;
	}
	std::cout << std::endl;
}

int mult2(int x) {
	return x * 2;
}

void testMap() {
	box<int> *first = range(5, 20);
	map(first, mult2);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

void testReverse() {
	box<int> *first = range(10, 20);
	reverse(first);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

void testDuplicates() {
	box<int> *first, *par, *cur;
	first = new box<int>(3, nullptr);
	par = new box<int>(2, nullptr);
	first->next = par;
	cur = new box<int>(7, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(7, nullptr);
	par->next = cur;
	par = cur;
	std::cout << duplicates(first) << std::endl;
}

void testRemoveDuplicates() {
	box<int> *first, *par, *cur;
	first = new box<int>(3, nullptr);
	par = new box<int>(3, nullptr);
	first->next = par;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(7, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(8, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(8, nullptr);
	par->next = cur;
	removeDuplicates(first);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

void testIsSorted() {
	box<int> *first, *par, *cur;
	first = new box<int>(883, nullptr);
	par = new box<int>(883, nullptr);
	first->next = par;
	cur = new box<int>(88, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(84, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(75, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(40, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(40, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(38, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(38, nullptr);
	par->next = cur;
	std::cout << isSorted(first) << std::endl;
}

void testPalindrom() {
	box<int> *first, *par, *cur;
	first = new box<int>(3, nullptr);
	par = new box<int>(4, nullptr);
	first->next = par;
	cur = new box<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(6, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(7, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(6, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(4, nullptr);
	par->next = cur;
	par = cur;
	cur = new box<int>(3, nullptr);
	par->next = cur;
	std::cout << isPalindrom(first) << std::endl;
}

int main() {
	testPalindrom();
	system("pause");
	return 0;
}