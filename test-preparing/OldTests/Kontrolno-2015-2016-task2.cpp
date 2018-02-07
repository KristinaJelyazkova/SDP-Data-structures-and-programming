// Дадено е двоично дърво от различни елементи от фиксиран тип Т. 
//Да се напише функция, която по дадени 2 елемента извежда най-краткия път 
//между съответните им възли.

#include<iostream>
#include<queue>
#include<stack>

template<class T>
struct TreeNode {
	T data;
	TreeNode *left, *right;
	TreeNode(T _data, TreeNode *_left, TreeNode *_right) 
		: data(_data), left(_left), right(_right){}
};

template<class T>
bool findPathFromCrrToElement(TreeNode<T> *crr, T element, std::queue<T> &path) {
	if (crr == nullptr) {
		return false;
	}
	if (crr->data == element) {
		path.push(element);
		return true;
	}
	path.push(crr->data);
	std::queue<T> copy = path;
	bool left = findPathFromCrrToElement(crr->left, element, path);
	if (left) {
		return true;
	}
	path = copy;
	bool right = findPathFromCrrToElement(crr->right, element, path);
	return right;
}

template<class T>
void shortestPath(TreeNode<T> *tree, T node1, T node2) {
	std::queue<T> path1;
	findPathFromCrrToElement(tree, node1, path1);
	std::queue<T> path2;
	findPathFromCrrToElement(tree, node2, path2);
	T parentOfBoth = tree->data;
	while (!path1.empty() && !path2.empty() && path1.front() == path2.front()) {
		parentOfBoth = path1.front();
		path1.pop();
		path2.pop();
	}
	std::stack<T> s;
	while (!path1.empty()) {
		s.push(path1.front());
		path1.pop();
	}
	while (!s.empty()) {
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << parentOfBoth << " ";
	while (!path2.empty()) {
		std::cout << path2.front() << " ";
		path2.pop();
	}
}

void testFindPath() {
	TreeNode<int> *tree = new TreeNode<int>(4,
		new TreeNode<int>(5,
			new TreeNode<int>(1,
				new TreeNode<int>(2, nullptr, nullptr),
				new TreeNode<int>(3, nullptr, nullptr)),
			new TreeNode<int>(7, nullptr, nullptr)),
		new TreeNode<int>(10,
			new TreeNode<int>(8,
				new TreeNode<int>(12, nullptr, nullptr),
				new TreeNode<int>(13, nullptr, nullptr)),
			new TreeNode<int>(9, nullptr, nullptr)));

	/*std::queue<int> q;
	bool elemExists = findPathFromCrrToElement<int>(tree, 12, q);
	if (!elemExists) {
		std::cout << "No such element in the tree.";
	}
	else {
		std::queue<int> copy = q;
		while (!copy.empty()) {
			std::cout << copy.front() << " ";
			copy.pop();
		}
	}
	std::cout << std::endl;*/

	shortestPath(tree, 3, 12);
	std::cout << std::endl;
	shortestPath(tree, 2, 7);
	std::cout << std::endl;
	shortestPath(tree, 12, 13);
	std::cout << std::endl;
}

int main() {
	testFindPath();

	system("pause");
	return 0;
}