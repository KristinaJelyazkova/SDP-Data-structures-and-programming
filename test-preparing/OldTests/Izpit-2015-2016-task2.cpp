//äà ñå äåôèíèðà ôóíêöèÿ levelIsPrefix, êîÿòî ïîëó÷àâà êàòî ïàðàìåòðè äâîè÷íî äúðâî t 
//è îïàøêà îò ÷èñëà q, êîÿòî ïðîâåðÿâà äàëè ñïèñúêúò îò ÷èñëàòà íà íÿêîå íèâî â äúðâîòî t, 
//÷åòåíè îòëÿâî íàäÿñíî, å ïðåôèêñ íà îïàøêàòà îò ÷èñëà q. 
//Àêî òàêîâà íèâî ñúùåñòâóâà, 
//ôóíêöèÿòà äà âðúùà íîìåðúò ìó, â ïðîòèâåí ñëó÷àé äà âðúùà -1. 
//Ïðè íÿêîëêî âúçìîæíè îòãîâîðà äà ñå âúðíå ïðîèçâîëåí îò òÿõ

#include<iostream>
#include<queue>

struct TreeNode {
	int data;
	TreeNode *left, *right;
	TreeNode(int _i, TreeNode *_l, TreeNode *_r) : data(_i), left(_l), right(_r) {}
};

#define SENTINEL nullptr

int levelIsPrefix(TreeNode *t, std::queue<int> q) {
	std::queue<TreeNode*> q1;
	q1.push(t);
	q1.push(SENTINEL);

	int level = 0;
	std::queue<int> copy = q;
	bool levelIsPref = true;
	
	while (!q1.empty()) {
		TreeNode *crr = q1.front();
		q1.pop();
		if (crr != SENTINEL) {
			if (levelIsPref) {
				if (copy.empty() || copy.front() != crr->data) {
					levelIsPref = false;
				}
				else{
					copy.pop();
				}
			}
			if (crr->left != nullptr) {
				q1.push(crr->left);
			}
			if (crr->right != nullptr) {
				q1.push(crr->right);
			}
		}
		else {
			if (levelIsPref) {
				return level;
			}
			if (!q1.empty()) {
				level++;
				copy = q;
				levelIsPref = true;
				q1.push(SENTINEL);
			}
		}
	}
	return -1;
}

void testLevelIsPrefix() {
	TreeNode *tree = new TreeNode(1,
		new TreeNode(2,
			new TreeNode(3, nullptr, nullptr),
			new TreeNode(2, nullptr, nullptr)),
		new TreeNode(2,
			new TreeNode(1, nullptr, nullptr), nullptr));

	std::queue<int> q;
	q.push(3);
	q.push(2);
	q.push(1);
	q.push(4);

	std::cout << levelIsPrefix(tree, q) << std::endl;
}

/*int main() {
	testLevelIsPrefix();

	system("pause");
	return 0;
}*/
