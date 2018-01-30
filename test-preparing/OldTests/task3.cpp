//Да се напише функция int sumNodes(tree<int> const& t), 
//която по дадено двоично дърво от цели числа t намира сумата от тези от тях, 
//които са по - малки от родителя си, но са по - големи от децата си.

#include<iostream>

struct TreeNode {
	int data;
	TreeNode *left, *right;
	TreeNode(int d, TreeNode *l, TreeNode *r) : data(d), left(l), right(r){}
};

int sumNodesHelp(TreeNode *crr, TreeNode *par) {
	if (crr == nullptr) {
		return 0;
	}
	int sum = 0;
	bool flag = true;
	if (par != nullptr && crr->data >= par->data) {
		flag = false;
	}
	if (crr->left != nullptr && crr->data <= crr->left->data) {
		flag = false;
	}
	if (crr->right != nullptr && crr->data <= crr->right->data) {
		flag = false;
	}
	if (flag) {
		sum += crr->data;
	}
	int sumLeft = sumNodesHelp(crr->left, crr);
	int sumRight = sumNodesHelp(crr->right, crr);
	sum = sum + sumLeft + sumRight;
	return sum;
}

int sumNodes(TreeNode *root) {
	return sumNodesHelp(root, nullptr);
}

void testSumNodes() {
	TreeNode *tree = new TreeNode(5,
		new TreeNode(2,
			new TreeNode(-3, nullptr, nullptr), nullptr),
		new TreeNode(3,
			new TreeNode(8, nullptr,
				new TreeNode(10, nullptr, nullptr)),
			new TreeNode(1, nullptr,
				new TreeNode(-3, nullptr, nullptr))));

	std::cout << sumNodes(tree) << std::endl;
}

/*int main() {
	testSumNodes();

	system("pause");
	return 0;
}*/