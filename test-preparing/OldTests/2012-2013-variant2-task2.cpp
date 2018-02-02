//Да се определи дали дадено двоично дърво е с балансирана височина.

#include<iostream>
#include<algorithm>
#include<iomanip>

struct TreeNode {
	int data;
	TreeNode *left, *right;
	TreeNode(int _d, TreeNode *_l, TreeNode *_r) : data(_d), left(_l), right(_r) {}
};

int height(TreeNode *tree) {
	if (tree == nullptr) {
		return 0;
	}
	return 1 + std::max(height(tree->left), height(tree->right));
}

bool isBalanced(TreeNode *tree) {
	if (tree == nullptr) {
		return true;
	}
	if (abs(height(tree->left) - height(tree->right)) > 1) {
		return false;
	}
	return isBalanced(tree->left) && isBalanced(tree->right);
}

void testIsBalanced() {
	TreeNode *tree = new TreeNode(5,
		new TreeNode(2,
			new TreeNode(-3, nullptr, nullptr), nullptr),
		new TreeNode(3,
			new TreeNode(8, nullptr,
				new TreeNode(10, nullptr, nullptr)),
			new TreeNode(1, nullptr,
				new TreeNode(-3, nullptr, nullptr))));
	std::cout << isBalanced(tree) << std::endl;
}

int main() {
	testIsBalanced();

	system("pause");
	return 0;
}
