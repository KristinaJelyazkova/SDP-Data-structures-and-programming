//Нека са дадени стек и дърво. Да се дефинира функцията 
//bool levelCheck(дърво t, стек s, int level), 
//която проверява дали всички елементи от стека s могат да бъдат прочетени 
//от ляво на дясно в нивото level на дървото t, в реда, в който са достъпни от стека

#include<iostream>
#include<stack>
#include<queue>

struct TreeNode {
	int data;
	TreeNode *left, *right;
	TreeNode(int d, TreeNode *l, TreeNode *r) : data(d), left(l), right(r) {}
};

bool levelCheck(TreeNode *tree, std::stack<int> s, int level) {
	if (tree == nullptr) {
		return level == 0 && s.empty();
	}
	std::queue<TreeNode*> q;
	q.push(tree);
	q.push(nullptr);
	while (!q.empty() && level > 1) {
		TreeNode *crr = q.front();
		q.pop();
		if (crr != nullptr) {
			if (crr->left != nullptr) {
				q.push(crr->left);
			}
			if (crr->right != nullptr) {
				q.push(crr->right);
			}
		}
		else {
			level--;
			if (!q.empty()) {
				q.push(nullptr);
			}
		}
	}
	if (level > 1) {
		return false; // no such level
	}
	while (q.size() > 1) {
		if (s.empty()) {
			return true;
		}
		if (q.front()->data != s.top()) {
			return false;
		}
		q.pop();
		s.pop();
	}
	return s.empty();
}

void testLevelCheck() {
	TreeNode *tree = new TreeNode(4,
		new TreeNode(5,
			new TreeNode(1,
				new TreeNode(2, nullptr, nullptr),
				new TreeNode(3, nullptr, nullptr)),
			new TreeNode(7, nullptr, nullptr)),
		new TreeNode(4,
			new TreeNode(8,
				new TreeNode(2, nullptr, nullptr),
				new TreeNode(3, nullptr, nullptr)),
			new TreeNode(9, nullptr, nullptr)));

	std::stack<int> s;
	s.push(9);
	s.push(8);
	s.push(7);
	s.push(1);

	std::cout << levelCheck(tree, s, 3) << std::endl;
}

/*int main() {
	testLevelCheck();

	system("pause");
	return 0;
}*/
