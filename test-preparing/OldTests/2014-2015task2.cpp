#include<iostream>

//Äŕäĺí ĺ äâîéíîńâúđçŕí ńďčńúę ń ÷ĺňĺí íŕ áđîé ĺäíîńâúđçŕíč ńďčńúöč îň ÷čńëŕ.

struct SingleLinkedListNode {
	int data;
	SingleLinkedListNode *next;
	SingleLinkedListNode(int _data, SingleLinkedListNode *_next) 
		: data(_data), next(_next) {}
};

struct DoubleLinkedListNode {
	SingleLinkedListNode *list;
	DoubleLinkedListNode *next;
	DoubleLinkedListNode *previous;
};

//Ńňîéíîńň íŕ äŕäĺí ĺäíîńâúđçŕí ńďčńúę îň ÷čńëŕ íŕđč÷ŕěĺ ÷čńëîňî, ęîĺňî ńĺ ôîđěčđŕ 
//îň ĺëĺěĺíňčňĺ íŕ ńďčńúęŕ, ęîčňî ńŕ öčôđč îň 0 äî 9 â đĺäŕ čě íŕ ńđĺůŕíĺ.
int valueOf(SingleLinkedListNode *first) {
	SingleLinkedListNode *cur = first;
	int value = 0;
	while (cur != nullptr) {
		if (cur->data >= 0 && cur->data <= 9) {
			value = value * 10 + cur->data;
		}
		cur = cur->next;
	}
	return value;
}

bool helper(DoubleLinkedListNode *firstHalf, DoubleLinkedListNode *secondHalf) {
	if (firstHalf->next == secondHalf) {
		return true;
	}
	if (valueOf(firstHalf->list) > valueOf(firstHalf->next->list)) {
		return false;
	}
	if (valueOf(secondHalf->list) > valueOf(secondHalf->previous->list)) {
		return false;
	}
	return helper(firstHalf->next, secondHalf->previous);
}

//Äŕ ńĺ đĺŕëčçčđŕ ôóíęöč˙, ęî˙ňî ďđîâĺđ˙âŕ äŕëč ńňîéíîńňčňĺ íŕ ĺäíîńâúđçŕíčňĺ ńďčńúöč 
//îň ďúđâŕňŕ ďîëîâčíŕ íŕ äâîéíîńâúđçŕíč˙ ńďčńúę îáđŕçóâŕň íŕđŕńňâŕůŕ đĺäčöŕ, ŕ îöĺíęčňĺ 
//íŕ ĺäíîńâúđçŕíčňĺ ńďčńúöč îň âňîđŕňŕ ďîëîâčíŕ íŕ äâîéíîńâúđçŕíč˙ ńďčńúę îáđŕçóâŕň íŕěŕë˙âŕůŕ đĺäčöŕ.
bool isHalfAscendingHalfDescending(DoubleLinkedListNode *first) {
	if (first == nullptr) {
		//std::cout << "g";
		return true;
	}
	DoubleLinkedListNode *last = first;
	while (last->next != nullptr) {
		last = last->next;
	}
	return helper(first, last);
}

void testIsHalfAscendingHalfDescending() {
	SingleLinkedListNode *list1 = new SingleLinkedListNode(1,
		new SingleLinkedListNode(11,
			new SingleLinkedListNode(3, nullptr)));
	SingleLinkedListNode *list2 = new SingleLinkedListNode(10,
		new SingleLinkedListNode(15,
			new SingleLinkedListNode(3, 
				new SingleLinkedListNode(7, nullptr))));
	SingleLinkedListNode *list3 = new SingleLinkedListNode(100,
		new SingleLinkedListNode(8,
			new SingleLinkedListNode(30,
				new SingleLinkedListNode(7, nullptr))));
	SingleLinkedListNode *list4 = new SingleLinkedListNode(1,
		new SingleLinkedListNode(8,
			new SingleLinkedListNode(30,
				new SingleLinkedListNode(70, nullptr))));
	DoubleLinkedListNode *first = new DoubleLinkedListNode();
	first->list = list1;
	DoubleLinkedListNode *second = new DoubleLinkedListNode();
	second->list = list2;
	DoubleLinkedListNode *third = new DoubleLinkedListNode();
	third->list = list3;
	DoubleLinkedListNode *fourth = new DoubleLinkedListNode();
	fourth->list = list4;
	first->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = nullptr;
	fourth->previous = third;
	third->previous = second;
	second->previous = first;
	
	std::cout << isHalfAscendingHalfDescending(first) << std::endl;
}

/*int main() {
	testIsHalfAscendingHalfDescending();

	system("pause");
	return 0;
}*/

