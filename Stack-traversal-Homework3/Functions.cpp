#include"LinkedList.h"
#include"ArrayIterator.h"
#include"StringIterator.h"
#include"BaseIterator.h"
#include<iostream>
#include<vector>

//  ¿  ƒ¿ —» —⁄«ƒ¿ƒ≈Ã HELP »“≈–¿“Œ– ¬⁄“–≈ ¬⁄¬ ‘”Õ ÷»ﬂ“¿???

template<typename T>
int count(BaseIterator<T>& it, const T& x) {
	int counter = 0;
	while (it.more()) {
		if (it.getNext() == x) counter++;
	}
	return counter;
}

template<typename T>
void map(BaseIterator<T>& it, T(*function) (const T &)) {
	while (it.more()) {
		T &current = it.getNext();
		current = function(current);
	}
}

template<typename T>
bool duplicates(ListIterator<T> it) {
	while (it.more()) {
		T current = it.getNext();
		ListIterator<T> help = it;
		while (help.more()) {
			if (current == help.getNext()) return true;
		}
	}
	return false;
}

template<typename T>
bool duplicatesArray(ArrayIterator<T> it) {
	while (it.more()) {
		T current = it.getNext();
		ArrayIterator<T> help = it;
		while (help.more()) {
			if (current == help.getNext()) return true;
		}
	}
	return false;
}

template<typename T>
bool duplicatesString(StringIterator<T> it) {
	while (it.more()) {
		T current = it.getNext();
		StringIterator<T> help = it;
		while (help.more()) {
			if (current == help.getNext()) return true;
		}
	}
	return false;
}

template<typename T>
bool isSorted(BaseIterator<T>& it) {
	T current = 0 , next = 0;
	if (it.more())
		current = it.getNext();
	else return true;
	if (it.more())
		next = it.getNext();
	else return true;
	int flag = 0;
	if (current < next) 
		flag = 1;
	if (current > next)
		flag = -1;
	while (it.more()) {
		current = next;
		next = it.getNext();
		if (flag == 0) {
			if (current < next)
				flag = 1;
			if (current > next)
				flag = -1;
		}
		if ( (current > next && flag == 1) || (current < next && flag == -1) )
			return false;
	}
	return true;
}

template<typename T>
bool palindrom(ListIterator<T> it) {
	std::vector<T> save;
	ListIterator<T> help = it;
	bool flag = 0;
	while (help.more()) {
		save.push_back(it.getNext());
		//std::cout << save.back() << " ";
		help.getNext();
		if(help.more()) help.getNext();
		else flag = 1;
	}
	if (flag == 1) save.pop_back();
	while (it.more()) {
		//std::cout << save.back() << " " << it.getNext() << std::endl;
		if (save.back() != it.getNext())
			return false;
		save.pop_back();
	}
	return true;
}

template<typename T>
bool palindromArray(ArrayIterator<T> it) {
	std::vector<T> save;
	ArrayIterator<T> help = it;
	bool flag = 0;
	while (help.more()) {
		save.push_back(it.getNext());
		//std::cout << save.back() << " ";
		help.getNext();
		if (help.more()) help.getNext();
		else flag = 1;
	}
	if (flag == 1) save.pop_back();
	while (it.more()) {
		//std::cout << save.back() << " " << it.getNext() << std::endl;
		if (save.back() != it.getNext())
			return false;
		save.pop_back();
	}
	return true;
}

template<typename T>
bool palindromString(StringIterator<T> it) {
	std::vector<T> save;
	StringIterator<T> help = it;
	bool flag = 0;
	while (help.more()) {
		save.push_back(it.getNext());
		//std::cout << save.back() << " ";
		help.getNext();
		if (help.more()) help.getNext();
		else flag = 1;
	}
	if (flag == 1) save.pop_back();
	while (it.more()) {
		//std::cout << save.back() << " " << it.getNext() << std::endl;
		if (save.back() != it.getNext())
			return false;
		save.pop_back();
	}
	return true;
}