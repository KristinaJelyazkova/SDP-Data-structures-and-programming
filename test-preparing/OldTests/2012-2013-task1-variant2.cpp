//Run - length encoding(RLE) � ����� �� ��������� �� �������, � ����� ����� �������� 
//�� ������� �������� �� ��������� ���� ������ �� �������� � ���� �� ������������.
//�� �� ������� �������

//1.	������<������<T>> compressRLE(������<T>&), ����� ���������� ������ �� ��������. 
//���������� �� �� ��������� ��� ��� �� ������ �� ������� � �� ��� ��������, 
//�� ����� ������� �� � ��������, � ������� - ����� ������� ��������.

#include<iostream>

struct Node {
	char data;
	Node *next;
	Node(char _data, Node *_next) : data(_data), next(_next) {}
};

struct NodeResult {
	std::pair<char, int> data;
	NodeResult *next;
	NodeResult(std::pair<char, int> _data, NodeResult *_next) : data(_data), next(_next) {}
};

NodeResult* compressRLE(Node *first) {
	if (first == nullptr) {
		return nullptr;
	}
	int count = 0;
	Node *crr = first;
	while (crr != nullptr && crr->data == first->data) {
		count++;
		crr = crr->next;
	}
	std::pair<char, int> pair(first->data, count);
	return new NodeResult(pair, compressRLE(crr));
}

//������<T> extractRLE(������<������<�>>&), ����� ������������ ����� ������, 
//���� � ��������� ����� ������� �� ������� ������� ����, ������� ������ 
//����������� ����� �� �������� � ������� ������ �� �������(��������� �� ������� ��������)

Node* extractRLE(NodeResult *list) {
	if (list == nullptr) {
		return nullptr;
	}
	char data = list->data.first;
	int count = list->data.second;
	Node *result = new Node(data, nullptr);
	count--;
	Node *crr = result;
	while (count > 0) {
		crr->next = new Node(data, nullptr);
		crr = crr->next;
		count--;
	}
	crr->next = extractRLE(list->next);
	return result;
}

//������: ����: [�m�, �i�, �s�, �s�, �i�, �p�, �p�, �i�] 
//= > �����: [[�m�, 1], [�i�, 1], [�s�, 2], �[i�, 1], [�p�, 2], [�i�, 1]]

void testCompressRLE() {
	Node *list = new Node('m',
		new Node('i',
			new Node('s',
				new Node('s',
					new Node('i',
						new Node('p',
							new Node('p',
								new Node('i', nullptr))))))));
	NodeResult *result = compressRLE(list);
	NodeResult *crr = result;
	while (crr != nullptr) {
		std::cout << crr->data.first << " " << crr->data.second << std::endl;
		crr = crr->next;
	}

	Node *res = extractRLE(result);
	Node *crr2 = res;
	while (crr2 != nullptr) {
		std::cout << crr2->data << " ";
		crr2 = crr2->next;
	}
	std::cout << std::endl;
}

int main() {
	testCompressRLE();

	system("pause");
	return 0;
}
