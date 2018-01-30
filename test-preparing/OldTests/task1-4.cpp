#include<iostream>
#include<stack>
#include<vector>

template<class T>
struct ListNode {
	T data;
	ListNode<T> *next;
	ListNode(T _data, ListNode<T> *_next) : data(_data), next(_next) {}
};

template<class T>
void removeDuplicates(ListNode<T> *&first) {
	if (first == nullptr || first->next == nullptr) {
		return;
	}
	ListNode<T> *crr = first->next, *par = first;
	bool flag = false;
	while (crr != nullptr) {
		if (crr->data == first->data) {
			ListNode<T> *tmp = crr;
			par->next = crr->next;
			delete tmp;
			crr = par->next;
			flag = true;
		}
		else {
			crr = crr->next;
			par = par->next;
		}
	}
	if (flag) {
		ListNode<T> *tmp = first;
		first = first->next;
		removeDuplicates(first);
	}
	else {
		removeDuplicates(first->next);
	}
}

void testRemoveDuplicates() {
	ListNode<int> *first, *par, *cur;
	first = new ListNode<int>(3, nullptr);
	par = new ListNode<int>(3, nullptr);
	first->next = par;
	cur = new ListNode<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new ListNode<int>(7, nullptr);
	par->next = cur;
	par = cur;
	cur = new ListNode<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new ListNode<int>(3, nullptr);
	par->next = cur;
	par = cur;
	cur = new ListNode<int>(5, nullptr);
	par->next = cur;
	par = cur;
	cur = new ListNode<int>(8, nullptr);
	par->next = cur;
	par = cur;
	cur = new ListNode<int>(3, nullptr);
	par->next = cur;
	removeDuplicates(first);
	while (first != nullptr) {
		std::cout << first->data << " ";
		first = first->next;
	}
	std::cout << std::endl;
}

template<class T>
struct TreeNode {
	T data;
	std::vector<TreeNode<T>*> children;
	TreeNode(const T& _data) : data(_data) {}
	void add_child(const T& child_data) {
		children.push_back(new TreeNode<T>(child_data));
	}
	void add_children(const std::vector<T>& _children) {
		for (T child : _children) {
			add_child(child);
		}
	}
};

template<class T>
void printLeaves(TreeNode<T> *root) {
	if (root == nullptr) {
		return;
	}
	std::stack<std::pair<TreeNode<T>*, bool>> s;
	s.push({ root, false });
	while (!s.empty()) {
		TreeNode<T> *crrNode = s.top().first;
		bool isLeaf = s.top().second;
		s.pop();
		if (isLeaf) {
			std::cout << crrNode->data << " ";
		}
		else {
			if (crrNode->children.empty()) {
				s.push({ crrNode, true });
			}
			else {
				for (TreeNode<T> *child : crrNode->children) {
					if (child != nullptr) {
						s.push({ child, false });
					}
				}
			}
		}
	}
}

void testPrintLeaves() {
	TreeNode<int>* tree = new TreeNode<int>(1);

	tree->add_children({ 2, 3, 4 });         //   1 -> 2, 3, 4               // 
											 // The whole tree:
	tree->children[1]->add_child(100);       //   3 -> 100                   //       
											 //                                       1                       
	tree->children[1]                                                        //     / | \      
		->children[0]                                                        //    2  3  4                                
		->add_children({ 200, 300, 400 });   // 100 -> 200 300 400           //       |    \   
											 //                                      100    5
	tree->children[1]                        // children[1] of 1 is 3        //    /  |  \ 
		->children[0]                        // children[0] of 3 is 100      // 200  300  400
		->children[2]                        // children[2] of 100 is 400    //            |
		->add_child(500);                    // 400 -> 500                   //           500 
											 //
	tree->children[2]->add_child(5);         // 4 -> 5                       //
	printLeaves(tree);
}

const int N = 6;                

bool G[N][N] = {
	1, 1, 0, 0, 1, 1,   
	0, 1, 0, 1, 0, 1,          
	1, 1, 0, 0, 1, 1,        
	1, 1, 0, 0, 1, 0,      
	1, 0, 1, 0, 1, 1,         
	0, 0, 0, 0, 0, 0,           
};

bool hasLadder(int start, int k) {
	if (k <= 0) {
		return true;
	}
	for (int nextVertex = 0; nextVertex < N; nextVertex++) {
		if (G[start][nextVertex] && start < nextVertex && hasLadder(nextVertex, k - 1)) {
			return true;
		}
	}
	return false;
}

void printAllLaddersShorterThanK(int k) {
	std::vector<std::vector<int>> paths;
	for (int vertex = 0; vertex < N; vertex++) {
		std::vector<int> path;
		path.push_back(vertex);
		paths.push_back(path);
	}
	for (std::vector<int> &path : paths) {
		for (int vertex : path) {
			std::cout << vertex << " ";
		}
		std::cout << std::endl;
	}
	paths.push_back(std::vector<int>());

	int length = 1;
	while (!paths.empty() && length < k) {
		std::vector<int> path = paths[0];
		paths.erase(paths.begin());
		if (!path.empty()) {
			int lastVertex = path[path.size() - 1];
			for (int nextVertex = 0; nextVertex < N; nextVertex++) {
				if (G[lastVertex][nextVertex] && lastVertex < nextVertex) {
					std::vector<int> newPath = path;
					newPath.push_back(nextVertex);
					paths.push_back(newPath);
				}
			}
		}
		else {
			for (std::vector<int> &path : paths) {
				for (int vertex : path) {
					std::cout << vertex << " ";
				}
				std::cout << std::endl;
			}
			length++;
			paths.push_back(std::vector<int>());
		}
	}
}

void testHasLadder() {
	std::cout << hasLadder(5, 3) << std::endl;
	std::cout << hasLadder(1, 3) << std::endl;
	std::cout << hasLadder(1, 4) << std::endl;
	std::cout << hasLadder(0, 1) << std::endl;
	std::cout << hasLadder(2, 5) << std::endl;
	std::cout << hasLadder(2, 2) << std::endl;
	std::cout << hasLadder(4, 1) << std::endl;
	std::cout << hasLadder(4, 2) << std::endl << std::endl;
	printAllLaddersShorterThanK(5);
}

int main() {
	//testRemoveDuplicates();
	//testPrintLeaves();
	testHasLadder();

	system("pause");
	return 0;
}
