//Дадено е двоично наредено дърво с върхове - цели числа.Да се напише функция, която разменя левия и десния наследник /
//на всеки от върховете на дървото и заменя всяка стойност x на връх на дървото с –x.

#include<iostream>
#include<iomanip>

struct TreeNode {
	int data;
	TreeNode *left, *right;
	TreeNode(int _d, TreeNode *_l, TreeNode *_r) : data(_d), left(_l), right(_r) {}
};

void changeTree(TreeNode *&crr) {
	if (crr == nullptr) {
		return;
	}
	crr->data = -crr->data;
	TreeNode *save = crr->left;
	crr->left = crr->right;
	crr->right = save;
	changeTree(crr->left);
	changeTree(crr->right);
}

void printTree(TreeNode *tree, int height) {
	if (tree == nullptr) {
		return;
	}
	printTree(tree->right, height + 1);
	std::cout << std::setw(3 * height) << tree->data << std::endl;
	printTree(tree->left, height + 1);
}

void testChangeTree(){
	TreeNode *tree = new TreeNode(5,
		new TreeNode(2,
			new TreeNode(-3, nullptr, nullptr), nullptr),
		new TreeNode(3,
			new TreeNode(8, nullptr,
				new TreeNode(10, nullptr, nullptr)),
			new TreeNode(1, nullptr,
				new TreeNode(-3, nullptr, nullptr))));
	printTree(tree, 0);
	changeTree(tree);
	printTree(tree, 0);
}

/*int main() {
	testChangeTree();

	system("pause");
	return 0;
}*/
