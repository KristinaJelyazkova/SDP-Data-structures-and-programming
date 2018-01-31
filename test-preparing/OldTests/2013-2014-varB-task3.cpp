//Да се напише функция bool readWord(tree<char> const& t, char const* w), 
//която по дадено двоично дърво от символи t, проверява дали думата w може да 
//бъде прочетена в дървото в посока от корена към листата. 
//Не е задължително първата буква на думата да е корена, нито последната да е някое листо.

#include<iostream>

struct TreeNode {
	char data;
	TreeNode *left, *right;
	TreeNode(int d, TreeNode *l, TreeNode *r) : data(d), left(l), right(r) {}
};

bool readWordHelp(TreeNode *crr, char const *w, bool startedReading, int index) {
	if (w[index] == '\0') {
		return true;
	}
	if (crr == nullptr) {
		return false;
	}
	if (startedReading) {
		if (w[index] != crr->data) {
			return false;
		}
		return readWordHelp(crr->left, w, true, index + 1) ||
			readWordHelp(crr->right, w, true, index + 1);
	}
	if (w[index] == crr->data) {
		return readWordHelp(crr->left, w, true, index + 1) ||
			readWordHelp(crr->right, w, true, index + 1) ||
			readWordHelp(crr->left, w, false, index) ||
			readWordHelp(crr->right, w, false, index);
	}
	return readWordHelp(crr->left, w, false, index) ||
		readWordHelp(crr->right, w, false, index);
}

bool readWord(TreeNode *root, char const *w) {
	return readWordHelp(root, w, false, 0);
}

void testReadWord() {
	TreeNode *tree = new TreeNode('i',
		new TreeNode('v',
			new TreeNode('v',
				new TreeNode('e', nullptr, nullptr),
				new TreeNode('o', nullptr, nullptr)),
			new TreeNode('m', nullptr, nullptr)),
		new TreeNode('i', nullptr,
			new TreeNode('v',
				new TreeNode('o', nullptr, nullptr), nullptr)));

	char *word = new char[4];
	word[0] = 'i';
	word[1] = 'v';
	word[2] = 'o';
	word[3] = '\0';
	std::cout << readWord(tree, word) << std::endl;
}

/*int main() {
	testReadWord();

	system("pause");
	return 0;
}*/