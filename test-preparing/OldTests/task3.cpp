#include<iostream>
#include<queue>
#include<string>
#include<vector>

//Дадено е двоично дърво от символи.
struct TreeNode {
	char symbol;
	TreeNode *left, *right;
	TreeNode(char _symbol, TreeNode *_left, TreeNode *_right)
		: symbol(_symbol), left(_left), right(_right){}
};

std::vector<std::string> findAllLevelWords(TreeNode *root) {
	if (root == nullptr){
		std::vector<std::string> empty;
		return empty;
	}

	std::vector<std::string> words;

	std::vector<TreeNode*> q;
	q.push_back(root);
	q.push_back(nullptr); //  SENTINEL

	char *c = new char[2];
	c[0] = root->symbol;
	c[1] = '\0';
	std::string word(c);
	words.push_back(word);

	while (!q.empty()) {
		TreeNode *crr = q[0];
		q.erase(q.begin());
		if (crr != nullptr) {// not a SENTINEL
			if (crr->left != nullptr) {
				q.push_back(crr->left);
			}
			if (crr->right != nullptr) {
				q.push_back(crr->right);
			}
		}
		else {
			std::string word = "";
			for (TreeNode *node : q) {
				char *c = new char[2];
				c[0] = node->symbol;
				c[1] = '\0';
				word.append(c);
			}
			words.push_back(word);
			if (!q.empty()) {
				q.push_back(nullptr); // SENTINEL
			}
		}
	}
	return words;
}

void helper(TreeNode *crr, std::vector<std::string> &v, int level) {
	if (crr == nullptr) {
		return;
	}
	if (level == v.size()) {
		v.push_back("");
	}

	v[level].append(1, crr->symbol);

	helper(crr->left, v, level + 1);
	helper(crr->right, v, level + 1);
}

std::vector<std::string> findAllLevelWordsRecursion(TreeNode *root) {
	std::vector<std::string> v;
	helper(root, v, 0);
	return v;
}

void testFindAllLevelWords() {
	TreeNode *root = new TreeNode('a',
		new TreeNode('m',
			new TreeNode('t', nullptr,
				new TreeNode('l', nullptr, nullptr)), nullptr),
		new TreeNode('e',
			new TreeNode('h',
				new TreeNode('o', nullptr, nullptr), nullptr),
			new TreeNode('e',
				new TreeNode('v', nullptr, nullptr),
				new TreeNode('e', nullptr, nullptr))));

	std::vector<std::string> words = findAllLevelWords(root); 
	std::vector<std::string> words2 = findAllLevelWordsRecursion(root);
	for (std::string word : words) {
		std::cout << word << std::endl;
	}
	for (std::string word : words2) {
		std::cout << word << std::endl;
	}
}

bool isFromLevelWords(std::string word, std::vector<std::string> levelWords) {
	for (std::string levelWord : levelWords) {
		if (levelWord == word) {
			return true;
		}
	}
	return false;
}

//Да се напише функция, която проверява дали съществува път от корена на дървото 
//до негово листо, за който е изпълнено следното условие : 
//думата, която се формира при конкатенация на символите в пътя в посока от 
//корена на дървото към листото, съвпада с дума, която се формира от елементите 
//на някое ниво X в същото дърво, разглеждани отляво - надясно.

bool pathHelp(TreeNode *crr, std::string &crrWord, std::vector<std::string> levelWords) {
	if (crr->left == nullptr && crr->right == nullptr) {
		crrWord.append(1, crr->symbol);
		if (isFromLevelWords(crrWord, levelWords)) {
			return true;
		}
		crrWord.pop_back();
		return false;
	}
	crrWord.append(1, crr->symbol);
	if (crr->left != nullptr) {
		if (pathHelp(crr->left, crrWord, levelWords)) {
			return true;
		}
	}
	if (crr->right != nullptr) {
		if (pathHelp(crr->right, crrWord, levelWords)) {
			return true;
		}
	}
	crrWord.pop_back();
	return false;
}

bool pathLikeLevelWord(TreeNode *root) {
	if (root == nullptr) {
		return false;
	}
	std::vector<std::string> levelWords = findAllLevelWordsRecursion(root);
	std::string word = "";
	return pathHelp(root, word, levelWords);
}

void testPathLikeLevelWord() {
	TreeNode *root = new TreeNode('l',
		new TreeNode('m',
			new TreeNode('t', nullptr,
				new TreeNode('l', nullptr, nullptr)), nullptr),
		new TreeNode('o',
			new TreeNode('h',
				new TreeNode('o', nullptr, nullptr), nullptr),
			new TreeNode('v',
				new TreeNode('v', nullptr, nullptr),
				new TreeNode('e', nullptr, nullptr))));

	std::cout << pathLikeLevelWord(root) << std::endl; // love => true

	TreeNode *root2 = new TreeNode('l',
		new TreeNode('m',
			new TreeNode('t', nullptr,
				new TreeNode('l', nullptr, nullptr)), nullptr),
		new TreeNode('o',
			new TreeNode('k',
				new TreeNode('o', nullptr, nullptr), nullptr),
			new TreeNode('v',
				new TreeNode('k', nullptr, nullptr),
				new TreeNode('o', nullptr, nullptr))));

	std::cout << pathLikeLevelWord(root2) << std::endl; // loko => true
}

/*int main() {
	//testFindAllLevelWords();
	testPathLikeLevelWord();

	system("pause");
	return 0;
}*/
