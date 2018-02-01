#include<iostream>

//[�������� ����� ��������� 2014 �.] 
//�������, �� ������������� ������ L1 ���� �� ���� �������" ��� ������� L2 � ������� M, 
//��� ��� ����� A � L1 � ����� B � L2, ���� ��
//A.data � B.data �� ����� �� M
//��� A � �� ���������� X �� �������� �� L1 � �� ���������� Y �� ���� �� L1, 
//�� B � �� ���������� X �� ���� �� L2 ��� �� ���������� Y �� �������� �� L2

struct Node {
	int data;
	Node *previous, *next;
	//Node(int _d, Node *_p, Node *_n) : data(_d), previous(_p), next(_n){}
};

//�� �� ��������� ������� join, ����� �������" ��� ������� L1 � L2, 
//��� ���� � ��������, ����� � �������� �� ���������� ����. 
//� ������, �� ���������� ���� �� �� ������ �� ������� �������� ������, 
//�� �� ������ ����, ��� �����, ������� M � ����������. ���������� ��������� �������� ������� ������".

bool join(Node *&L1, Node *&L2) {
	Node *cur1 = L1, *cur2 = L2;
	while (cur1->next != nullptr) {
		cur1 = cur1->next;
	}

	Node *maxJoin1 = nullptr, *maxJoin2 = nullptr;

	while (cur1 != nullptr && cur2 != nullptr) {
		if (cur1->data == cur2->data) {
			if (maxJoin1 == nullptr || maxJoin1->data < cur1->data) {
				maxJoin1 = cur1;
				maxJoin2 = cur2;
			}
		}
		cur1 = cur1->previous;
		cur2 = cur2->next;
	}

	cur1 = L1;
	while (cur1->next != nullptr) {
		cur1 = cur1->next;
	}

	while (cur1 != nullptr && cur2 != nullptr) {
		if (cur1->data == cur2->data) {
			if (maxJoin1 == nullptr || maxJoin1->data < cur1->data) {
				maxJoin1 = cur1;
				maxJoin2 = cur2;
			}
		}
		cur1 = cur1->next;
		cur2 = cur2->previous;
	}

	if (maxJoin1 == nullptr) {
		return false;
	}

	L2->previous = maxJoin1;
	Node *last1 = L1;
	while (last1->next != nullptr) {
		last1 = last1->next;
	}
	last1->next = maxJoin2;
	return true;
}

//�� �� ��������� ������ ������� isJoined, ����� �� ������ ��������� ��� ������ � 
//���� �� ����������� ������ ��������� ���� �������� � ������ ������.
//���������: �� �� �����, �� � ���������� ������ ���� ���������.

bool isJoined(Node *begin, Node *end) {
	Node *beginningOfSecondList = end;
	bool found = false;
	while (beginningOfSecondList != nullptr && !found) {
		if (beginningOfSecondList->previous != nullptr && beginningOfSecondList->previous->next != beginningOfSecondList) {
			found = true;
		}
		if (!found) {
			beginningOfSecondList = beginningOfSecondList->previous;
		}
	}
	if (!found) {
		return false;
	}

	int Y1 = 0;
	Node *endOfFirstList = beginningOfSecondList->previous;
	bool found2 = false;
	while (endOfFirstList != nullptr && !found2) {
		if (endOfFirstList->next != nullptr && endOfFirstList->next->previous != endOfFirstList) {
			found2 = true;
		}
		if (!found2) {
			endOfFirstList = endOfFirstList->next;
			Y1++;
		}
	}
	if (!found2) {
		return false;
	}

	if (beginningOfSecondList->previous->data != endOfFirstList->next->data) {
		return false;
	}

	Node *cur2 = beginningOfSecondList;
	int Y2 = 0;
	while (cur2 != endOfFirstList->next) {
		Y2++;
		cur2 = cur2->next;
	}

	int X1 = 0;
	Node *cur1 = beginningOfSecondList->previous;
	while (cur1 != nullptr) {
		X1++;
		if (cur1->previous != nullptr && cur1->previous->next != cur1) {
			return false;
		}
		cur1 = cur1->previous;
	}
	
	int X2 = 0;
	while (cur2 != nullptr) {
		X2++;
		if (cur2->next != nullptr && cur2->next->previous != cur2) {
			return false;
		}
		cur2 = cur2->next;
	}

	if (Y1 != Y2 && X1 != X2) {
		return false;
	}

	return true;
}

//�� �� ��������� ������� sum, ����� �� ����� ������ ������ ������ 
//������ �� �������� �� ��������.

int sum(Node *L) {
	if (L == nullptr) {
		return 0;
	}
	int sum = 0;
	Node *begin = L, *end = L;
	while (end->next != nullptr) {
		end = end->next;
	}

	while (begin != nullptr && begin->next != nullptr && begin->next->previous == begin) {
		sum += begin->data;
		begin = begin->next;
	}
	sum += begin->data;

	while (end != nullptr && end->previous != nullptr && end->previous->next == end) {
		sum += end->data;
		end = end->previous;
	}
	sum += end->data;

	return sum;
}

void testJoinIsJoinedSum() {
	Node *L11 = new Node();
	L11->data = 1;
	Node *L12 = new Node();
	L12->data = 3;
	Node *L13 = new Node();
	L13->data = 5;
	Node *L14 = new Node();
	L14->data = 7;
	Node *L15 = new Node();
	L15->data = 9;
	Node *L16 = new Node();
	L16->data = 6;

	L11->next = L12;
	L12->next = L13;
	L13->next = L14;
	L14->next = L15;
	L15->next = L16;
	L16->next = nullptr;

	L16->previous = L15;
	L15->previous = L14;
	L14->previous = L13;
	L13->previous = L12;
	L12->previous = L11;
	L11->previous = nullptr;

	Node *L21 = new Node();
	L21->data = 3;
	Node *L22 = new Node();
	L22->data = 4;
	Node *L23 = new Node();
	L23->data = 8;
	Node *L24 = new Node();
	L24->data = 5;
	Node *L25 = new Node();
	L25->data = 7;

	L21->next = L22;
	L22->next = L23;
	L23->next = L24;
	L24->next = L25;
	L25->next = nullptr;

	L25->previous = L24;
	L24->previous = L23;
	L23->previous = L22;
	L22->previous = L21;
	L21->previous = nullptr;

	std::cout << isJoined(L11, L25) << std::endl;

	join(L11, L21);

	std::cout << L21->previous->data << std::endl;
	std::cout << L16->next->data << std::endl;

	std::cout << isJoined(L11, L25) << std::endl;

	std::cout << sum(L11) << std::endl;
}

int main() {
	testJoinIsJoinedSum();

	system("pause");
	return 0;
}