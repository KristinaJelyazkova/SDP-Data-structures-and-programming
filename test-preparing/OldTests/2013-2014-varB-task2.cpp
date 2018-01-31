//������ �� ��e ������ �� �����, ��������� � �������� ��� �� �������� ��� ���� �� ��������.
//�� �� ������ ������� mergeQueues, ����� ���� ���������� InsertElem � DeleteElem ��������� ���� 
//������, ����� �� ������ �� ������ �������� �� �������� ��� ������, ��������� � ��������� ��� �� 
//�������� ��� ����.

#include<iostream>
#include<queue>

void mergeQueues(std::queue<int> q1, std::queue<int> q2, std::queue<int> &result) {
	if (q1.empty()) {
		while (!q2.empty()) {
			result.push(q2.front());
			q2.pop();
		}
		return;
	}
	if (q2.empty()) {
		while (!q1.empty()) {
			result.push(q1.front());
			q1.pop();
		}
		return;
	}
	int min1 = q1.front(), min2 = q2.front();
	if (min1 < min2) {
		result.push(min1);
		q1.pop();
		mergeQueues(q1, q2, result);
	}
	else {
		result.push(min2);
		q2.pop();
		mergeQueues(q1, q2, result);
	}
}

//������: ��� ������� ������ ������� 1, 3, 5, � ������� ������ ������� ������� 1, 2, 6, 
//���������� ������ ������ �� ������� ������� 1, 1, 2, 3, 5, 6.

void testMergeQueues() {
	std::queue<int> q1;
	q1.push(1);
	q1.push(3);
	q1.push(5);
	std::queue<int> q2;
	q2.push(1);
	q2.push(2);
	q2.push(6);
	std::queue<int> result;
	mergeQueues(q1, q2, result);
	while (!result.empty()) {
		std::cout << result.front() << " ";
		result.pop();
	}
	std::cout << std::endl;
}

/*int main() {
	testMergeQueues();

	system("pause");
	return 0;
}*/