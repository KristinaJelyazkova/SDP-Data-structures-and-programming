//Äà ñå ñúçäàäå(÷ðåç âêëþ÷âàíå) äâîè÷íî íàðåäåíî äúðâî îò èíòåðâàëè îò ÷èñëà([a, b], a <= b).
//Íàðåäáàòà äà å ïî äúëæèíàòà íà èíòåðâàëà.
//Äà ñå íàìåðè ìèíèìàëíèÿò èíòåðâàë, ñúäúðæàù âñè÷êè èíòåðâàëè íà äâîè÷íî - íàðåäåíîòî äúðâî.

#include<iostream>
#include<queue>

struct TreeNode {
	std::pair<int, int> interval;
	TreeNode *left, *right;
	TreeNode(std::pair<int, int> _i, TreeNode *_l, TreeNode *_r) : interval(_i), left(_l), right(_r){}
};

int length(std::pair<int, int> interval) {
	return abs(interval.second - interval.first);
}

void insertBOT(TreeNode *&crr, std::pair<int, int> interval) {
	if (crr == nullptr) {
		crr = new TreeNode(interval, nullptr, nullptr);
		return;
	}
	if (length(interval) <= length(crr->interval)) {
		insertBOT(crr->left, interval);
	}
	else {
		insertBOT(crr->right, interval);
	}
}

TreeNode* createTree(std::queue<std::pair<int, int>> intervals) {
	if (intervals.empty()) {
		return nullptr;
	}
	TreeNode *result = nullptr;
	while (!intervals.empty()) {
		insertBOT(result, intervals.front());
		intervals.pop();
	}
	return result;
}

void minIntervalHelp(TreeNode *crr, int &min, int &max) {
	if (crr == nullptr) {
		return;
	}
	if (crr->interval.first < min) {
		min = crr->interval.first;
	}
	if (crr->interval.second > max) {
		max = crr->interval.second;
	}
	minIntervalHelp(crr->left, min, max);
	minIntervalHelp(crr->right, min, max);
}

//Äà ñå íàìåðè ìèíèìàëíèÿò èíòåðâàë, ñúäúðæàù âñè÷êè èíòåðâàëè íà äâîè÷íî - íàðåäåíîòî äúðâî.
std::pair<int, int> minInterval(TreeNode *tree) {
	if (tree == nullptr) {
		std::pair<int, int> p;
		return p;
	}
	int min = tree->interval.first,
		max = tree->interval.second;
	minIntervalHelp(tree, min, max);
	return{ min, max };
}

void testCreateTree() {
	std::queue<std::pair<int, int>> intervals;
	intervals.push({ 5,10 });
	intervals.push({ 10,21 });
	intervals.push({ -3,4 });
	intervals.push({ -10,0 });
	intervals.push({ 15,36 });
	intervals.push({ 8,14 });
	intervals.push({ -15,-12 });
	intervals.push({ 12,13 });
	intervals.push({ 1,3 });

	TreeNode *tree = createTree(intervals);
	std::cout << tree->left->left->interval.first << " " << tree->left->left->interval.second << std::endl;
	std::cout << tree->right->left->right->interval.first << " " << tree->right->left->right->interval.second << std::endl;

	std::pair<int, int> minInter = minInterval(tree);
	std::cout << minInter.first << " " << minInter.second << std::endl;
}

/*int main() {
	testCreateTree();

	system("pause");
	return 0;
}*/
