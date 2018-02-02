//���������� ��� �������� ��� � ���������� ����, � ����� ����� ����� ��� �������, 
//�.�.����������� ����� �� ���� ���� � ��� � �����.�� �� ������� �����a�a ������q :
//int maxTwoWayFrom(int n, IntGraph& g, int length), 
//����� ��������� ���� �� ������ n ������� ��������� ��� � ������� ��� - ����� length.

#include<iostream>

bool maxTwoWayFrom(int vertex, bool G[5][5], int n, int length) {
	if (length == 0) {
		return true;
	}
	for (int nextVertex = 0; nextVertex < n; nextVertex++) {
		if (G[vertex][nextVertex] && G[nextVertex][vertex] &&
			maxTwoWayFrom(nextVertex, G, n, length - 1)) {
			return true;
		}
	}
	return false;
}

void testMaxTwoWayFrom() {
	bool G[5][5] = {
		0, 0, 1, 0, 0,
		1, 1, 0, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0
	};
	std::cout << maxTwoWayFrom(4, G, 5, 2) << std::endl;
	std::cout << maxTwoWayFrom(4, G, 5, 100) << std::endl;
	std::cout << maxTwoWayFrom(0, G, 5, 100) << std::endl;
}

/*int main() {
	testMaxTwoWayFrom();

	system("pause");
	return 0;
}*/

