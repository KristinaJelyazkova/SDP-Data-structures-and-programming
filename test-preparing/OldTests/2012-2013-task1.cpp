//Да се напишат следните функции, работещи с линеен едносвързан списък.
//hist(списък), която по даден списък отпечатва на екрана двойки с 
//честотата на срещанията на всеки негов елемент

#include<iostream>
#include<map>

struct Node {
	int data;
	Node *next;
	Node(int _data, Node *_next) : data(_data), next(_next) {}
};

void hist(Node *first) {
	std::map<int, int> map;
	Node *crr = first;
	while (crr != nullptr) {
		if (map.count(crr->data) == 0) {
			map[crr->data] = 1;
		}
		else {
			++map[crr->data];
		}
		crr = crr->next;
	}
	for (std::map<int, int>::const_iterator it = map.begin(); it != map.end(); it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
}

//Пример : hist[1, 2, 3, 1, 5, 3] ~> 1, 2 \ 2, 1 \ 3, 2 \ 5, 1
void testHist() {
	Node *list = new Node(1,
		new Node(2,
			new Node(3,
				new Node(1,
					new Node(5,
						new Node(3, nullptr))))));
	hist(list);
}

/*int main() {
	testHist();

	system("pause");
	return 0;
}*/

