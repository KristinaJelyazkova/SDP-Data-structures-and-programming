#include<iostream>

//����� � ������������� ������ � ����� �� ���� ������������ ������� �� �����.

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

//�������� �� ����� ����������� ������ �� ����� �������� �������, ����� �� ������� 
//�� ���������� �� �������, ����� �� ����� �� 0 �� 9 � ���� �� �� �������.
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

//�� �� ��������� �������, ����� ��������� ���� ����������� �� �������������� ������� 
//�� ������� �������� �� ��������������� ������ ��������� ���������� ������, � �������� 
//�� �������������� ������� �� ������� �������� �� ��������������� ������ ��������� ���������� ������.
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

