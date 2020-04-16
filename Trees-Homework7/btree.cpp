#include "btree.h"
#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

// погледни windstack на различните итератори и begin и end на BTree
// използваме опашка само ако искаме да обхождаме в широчина
// в стекът трябва да се внимава за реда - наобратно е

template <class T>
PredIterator<T>::PredIterator(TreeNode<T> *root, bool (*_pred) (const T&))
{
	if (root != nullptr) // ако дървото е празно, ще имаме празен стек
	{
		s.push(task<T>(root, false)); // в началото винаги слагаме false при root
		pred = _pred;
		windStack(); //!!!
	}
}

template <class T>
void PredIterator<T>::windStack()
{
	//!!! s.top().toPrintNow == false
	while (!s.empty() && s.top().toPrintNow == false) // стекът е направил стъпката си, когато на върха има елемент, готов за взимане (принтене)
	{

		task<T> currentTask = s.top(); // взимаме върха на стека
		s.pop(); // махаме го

		if (currentTask.node->right != nullptr)
			s.push(task<T>(currentTask.node->right, false)); // добавяме дясното дете само ако има такова

		if (pred(currentTask.node->data)) {
			s.push(task<T>(currentTask.node, true)); // добавяме настоящето (това, което сме махнали) само ако изпълнява предиката, иначе ще зациклим!!!!
		}

		if (currentTask.node->left != nullptr)
			s.push(task<T>(currentTask.node->left, false)); // добавяме лявото дете само ако има такова


	}
}

template <class T>
T PredIterator<T>::operator * ()
{
	assert(!s.empty());

	task<T> topTask = s.top(); // не махаме елемента, за да можем да го достъпваме колкото си искаме пъти
	return topTask.node->data;
}

template <class T>
bool PredIterator<T>::operator != (const PredIterator<T> &other)
{
	return !(*this == other);
}


template <class T>
bool PredIterator<T>::operator == (const PredIterator<T> &other) // равни са ако стековете им са празни или са пълни и върховете им имат равни неща (приемаме, че обхождат едно и също дърво)
{
	//!!***!!!***!!
	//s == other.s следва от това нещо:

	return (s.empty() && other.s.empty()) ||
		(!s.empty() && !other.s.empty() &&
		(s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));

}

template <class T>
PredIterator<T>& PredIterator<T>::operator ++ (int)
{
	assert(!s.empty());
	s.pop(); // елементът е прочетен, значи го махаме
	windStack(); //!!! изпълняваме една стъпка за стека

	return *this;
}

template <class T>
LeafIterator<T>::LeafIterator(TreeNode<T> *root)
{
	if (root != nullptr)
	{
		s.push(task<T>(root, false));
		windStack(); //!!!
	}
}

template <class T>
void LeafIterator<T>::windStack()
{
	//!!! s.top().toPrintNow == false
	while (!s.empty() && s.top().toPrintNow == false)
	{

		task<T> currentTask = s.top();
		s.pop();

		if (currentTask.node->right != nullptr)
			s.push(task<T>(currentTask.node->right, false));

		if (currentTask.node->left != nullptr)
			s.push(task<T>(currentTask.node->left, false));

		if (currentTask.node->left == nullptr && currentTask.node->right == nullptr)
			s.push(task<T>(currentTask.node, true)); // слагаме настоящия елемент само ако е листо


	}
}

template <class T>
T LeafIterator<T>::operator * ()
{
	assert(!s.empty());

	task<T> topTask = s.top();
	return topTask.node->data;
}

template <class T>
bool LeafIterator<T>::operator != (const LeafIterator<T> &other)
{
	return !(*this == other);
}


template <class T>
bool LeafIterator<T>::operator == (const LeafIterator<T> &other)
{
	//!!***!!!***!!
	//s == other.s следва от това нещо:

	return (s.empty() && other.s.empty()) ||
		(!s.empty() && !other.s.empty() &&
		(s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));

}

template <class T>
LeafIterator<T>& LeafIterator<T>::operator ++ (int)
{
	assert(!s.empty());
	s.pop();
	windStack(); //!!!

	return *this;
}

template <class T>
LevelIterator<T>::LevelIterator(TreeNode<T> *root) { // използваме опашка
	if(root != nullptr)
		q.push(root);
}

template <class T>
T LevelIterator<T>::operator * () {
	TreeNode<T>* current = q.front();
	return current->data;
}

template <class T>
bool LevelIterator<T>::operator == (const LevelIterator<T>& other) {
	return ((q.empty() && other.q.empty()) ||
		(!q.empty() && !other.q.empty() && q.front()->data == other.q.front()->data));
}

template <class T>
bool LevelIterator<T>::operator != (const LevelIterator<T>& other) {
	return !(*this == other);
}

template <class T>
LevelIterator<T>& LevelIterator<T>::operator ++ (int) {
	assert(!q.empty());
	TreeNode<T> * current = q.front();
	q.pop(); // в опашката всичко си се подрежда както ни трябва, затова нямаме toPrintNow, а директно си принтим
	if (current->left != nullptr) { // слагаме децата на настоящият възел на дървото
		q.push(current->left);
	}
	if (current->right != nullptr) {
		q.push(current->right);
	}
	return (*this);
}

template <class T>
LRoTreeIterator<T>::LRoTreeIterator(TreeNode<T> *root)
{
	if (root != nullptr)
	{
		s.push(task<T>(root, false));
		windStack(); //!!!
	}
}

template <class T>
void LRoTreeIterator<T>::windStack()
{
	//!!! s.top().toPrintNow == false
	while (!s.empty() && s.top().toPrintNow == false)
	{

		task<T> currentTask = s.top(); s.pop();

		// за поредността на обхождане на лявото, дясното поддърво и корена има значение само реда на следващите 3:
		s.push(task<T>(currentTask.node, true)); // 1
		// тук искаме да обходим всички елементи, затова слагаме и настоящия

		if (currentTask.node->right != nullptr)
			s.push(task<T>(currentTask.node->right, false)); // 2

		if (currentTask.node->left != nullptr)
			s.push(task<T>(currentTask.node->left, false));  // 3


	}
}

template <class T>
T LRoTreeIterator<T>::operator * ()
{
	assert(!s.empty());

	task<T> topTask = s.top();
	return topTask.node->data;
}

template <class T>
bool LRoTreeIterator<T>::operator != (const LRoTreeIterator<T> &other)
{
	return !(*this == other);
}


template <class T>
bool LRoTreeIterator<T>::operator == (const LRoTreeIterator<T> &other)
{
	//!!***!!!***!!
	//s == other.s следва от това нещо:

	return (s.empty() && other.s.empty()) ||
		(!s.empty() && !other.s.empty() &&
		(s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));

}

template <class T>
LRoTreeIterator<T>& LRoTreeIterator<T>::operator ++ (int)
{
	assert(!s.empty());
	s.pop();
	windStack(); //!!!

	return *this;
}


template <class T>
oRLTreeIterator<T>::oRLTreeIterator(TreeNode<T> *root)
{
	if (root != nullptr)
	{
		s.push(task<T>(root, false));
		windStack(); //!!!
	}
}

template <class T>
void oRLTreeIterator<T>::windStack()
{
	//!!! s.top().toPrintNow == false
	while (!s.empty() && s.top().toPrintNow == false)
	{

		task<T> currentTask = s.top(); s.pop();

		if (currentTask.node->left != nullptr)
			s.push(task<T>(currentTask.node->left, false));

		if (currentTask.node->right != nullptr)
			s.push(task<T>(currentTask.node->right, false));

		s.push(task<T>(currentTask.node, true));


	}
}

template <class T>
T oRLTreeIterator<T>::operator * ()
{
	assert(!s.empty());

	task<T> topTask = s.top();
	return topTask.node->data;
}

template <class T>
bool oRLTreeIterator<T>::operator != (const oRLTreeIterator<T> &other)
{
	return !(*this == other);
}


template <class T>
bool oRLTreeIterator<T>::operator == (const oRLTreeIterator<T> &other)
{
	//!!***!!!***!!
	//s == other.s следва от това нещо:

	return (s.empty() && other.s.empty()) ||
		(!s.empty() && !other.s.empty() &&
		(s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));

}

template <class T>
oRLTreeIterator<T>& oRLTreeIterator<T>::operator ++ (int)
{
	assert(!s.empty());
	s.pop();
	windStack(); //!!!

	return *this;
}

template <class T>
TreeNode<T>::TreeNode(const T& _data,
	TreeNode<T> *_left,
	TreeNode<T> *_right) :data(_data),
	left(_left),
	right(_right)
{
	id = maxid;
	maxid++;
}

template <class T>
int TreeNode<T>::getId()
{
	return id;
}

template <class T>
int TreeNode<T>::maxid = 0;


template <class T>
BTree<T>::BTree() :root(nullptr)
{

}

template <class T>
BTree<T>::BTree(const T data, const BTree<T> &lt, const BTree<T> &rt)
{
	root = new TreeNode<T>(data, copyFrom(lt.root), copyFrom(rt.root));

}

template <class T>
void printNodesLISP(std::ostream& out, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		out << "()";
		return;
	}

	out << "( " << root->data << " ";
	printNodesLISP(out, root->left);
	out << " ";
	printNodesLISP(out, root->right);
	out << " )";
}

template <class T>
void printNodesDotty(std::ostream& out, TreeNode<T> *root)
{
	if (root == nullptr)
	{
		return;
	}

	out << root->getId()
		<< "[label=\""
		<< root->data
		<< "\"];"
		<< std::endl;

	if (root->left != nullptr)
	{
		out << root->getId()
			<< "->"
			<< root->left->getId()
			<< "[color = \"red\"]"
			<< ";"
			<< std::endl;
	}

	if (root->right != nullptr)
	{
		out << root->getId()
			<< "->"
			<< root->right->getId()
			<< ";"
			<< std::endl;
	}
	printNodesDotty(out, root->left);
	printNodesDotty(out, root->right);
}



std::ostream& operator << (std::ostream &out, const BTree<int> &t)
{
	/*  out << "digraph G {" << std::endl;
	printNodesDotty (out, t.root);
	out << "}" << std::endl;*/

	printNodesLISP(out, t.root);

	return out;
}

template <class T>
bool BTree<T>::insertElement(std::string trace, const T& x, TreeNode<T> *&crr)
{
	if (trace == "" && crr == nullptr)
	{
		crr = new TreeNode<T>(x, nullptr, nullptr);
		return true;
	}
	if (trace != "" && crr == nullptr)
	{
		return false;
	}
	//=> trace != "" && current != nullptr
	if (trace[0] == 'L')
	{
		trace.erase(trace.begin());
		return insertElement(trace, x, crr->left);
	}
	if (trace[0] == 'R')
	{
		trace.erase(trace.begin());
		return insertElement(trace, x, crr->right);
	}
	return false;
}


template <class T>
bool BTree<T>::insertElement(std::string trace, const T& x)
{
	return insertElement(trace, x, root);
}

template <class T>
void BTree<T>::insertBOT(const T &x, TreeNode<T> *&crr)
{
	if (crr == nullptr)
	{
		crr = new TreeNode<T>(x, nullptr, nullptr);
		return;
	}

	if (x < crr->data) {
		insertBOT(x, crr->left);
		return;
	}

	insertBOT(x, crr->right);


}

template <class T>
void BTree<T>::insertBOT(const T& x)
{
	insertBOT(x, root);
}

template <class T>
bool BTree<T>::member(const T& y) const
{
	return member(y, root);
}


template <class T>
bool BTree<T>::member(const T& y, const TreeNode<T> *crr) const
{
	if (crr == nullptr)
	{
		return false;
	}

	return crr->data == y ||
		member(y, crr->left) ||
		member(y, crr->right);
}


template <class T>
void BTree<T>::read(std::istream &in)
{
	//приемаме, че дървото е празно
	root = readFromStream(in);
}


template <class T>
TreeNode<T>* BTree<T>::readFromStream(std::istream &in)
{ //()..............
  //( 7 ( 30 () ( 12 ( 90 () () ) () ) ) ( 5 ( 50 () () ) () ) )

	char nextChar;
	nextChar = in.get();
	assert(nextChar == '(');

	nextChar = in.get();
	assert(nextChar == ' ' || nextChar == ')');

	if (nextChar == ')')
	{
		return nullptr;
	}
	//уверени сме, че в потока следват следните неща:
	//1. СТОЙНОСТ НА КОРЕНА. ПРИЕМАМЕ, ЧЕ ОПЕРАТОР >>T КОРЕКТНО ЩЕ Я ИЗЧЕТЕ

	T rootValue;
	in >> rootValue;

	//2. интервал

	nextChar = in.get();
	assert(nextChar == ' ');

	//3. ЛЯВО ПОДДЪРВО

	TreeNode<T> *leftSubTree;
	leftSubTree = readFromStream(in);

	//4. интервал

	nextChar = in.get();
	assert(nextChar == ' ');

	//5. ДЯСНО ПОДДЪРВО

	TreeNode<T> *rightSubTree;
	rightSubTree = readFromStream(in);

	//6. интервал

	nextChar = in.get();
	assert(nextChar == ' ');

	//7. затваряща скоба

	nextChar = in.get();
	assert(nextChar == ')');

	return new TreeNode<T>(rootValue, leftSubTree, rightSubTree);

}


template <class T>
void BTree<T>::del(TreeNode<T> *crr)
{
	if (crr == nullptr)
	{
		return;
	}

	del(crr->left);
	del(crr->right);
	delete crr;
}


template <class T>
BTree<T>::~BTree()
{
	del(root);
}

template <class T>
TreeNode<T>* BTree<T>::copyFrom(const TreeNode<T> *crr)
{
	if (crr == nullptr)
	{
		return nullptr;
	}

	return new TreeNode<T>(crr->data,
		copyFrom(crr->left),
		copyFrom(crr->right));
}


template <class T>
BTree<T>::BTree(const BTree<T> &other)
{
	root = copyFrom(other.root);
}

template <class T>
BTree<T>& BTree<T>::operator = (const BTree<T> &other)
{
	if (this != &other)
	{
		del(root);
		root = copyFrom(other.root);
	}
	return *this;
}

template <class T>
bool BTree<T>::operator == (const BTree<T> &other) const
{
	return compare(root, other.root);
}

template <class T>
bool BTree<T>::compare(const TreeNode<T> *t1, const TreeNode<T> *t2) const
{
	if (t1 == nullptr)
		return t2 == nullptr;

	if (t2 == nullptr)
		return t1 == nullptr;

	return t1->data == t2->data &&
		compare(t1->left, t2->left) &&
		compare(t1->right, t2->right);
}

template <class T>
void BTree<T>::deleteBOT(const T &x)
{

	removeFromSubtreeProc(x, root);

}

template <class T>
T& BTree<T>::findmin(TreeNode<T> *crr)
{
	assert(crr != nullptr);

	while (crr->left != nullptr)
	{
		crr = crr->left;
	}

	return crr->data;

}

template <class T>
TreeNode<T>* BTree<T>::removeFromSubtree(const T &x, TreeNode<T> *crr)
{
	//1
	if (crr == nullptr)
		return nullptr;

	//2
	if (crr->data == x && crr->left == nullptr)
	{
		TreeNode <T> *save = crr->right;
		delete crr;
		return save;
	}
	//3
	if (crr->data == x && crr->right == nullptr)
	{
		TreeNode <T> *save = crr->left;
		delete crr;
		return save;
	}
	//4
	if (crr->data == x)
	{
		T rightmin = findmin(crr->right);
		crr->data = rightmin;
		crr->right = removeFromSubtree(rightmin, crr->right);
		crr = removeFromSubtree(x, crr);
		return crr;

	}
	//5, 6
	if (crr->data < x)
	{
		crr->right = removeFromSubtree(x, crr->right);
	}
	else {
		crr->left = removeFromSubtree(x, crr->left);
	}

	return crr;

}


template <class T>
void BTree<T>::removeFromSubtreeProc(const T &x, TreeNode<T> *&crr)
{
	//1
	if (crr == nullptr)
		return;

	//2
	if (crr->data == x && crr->left == nullptr)
	{
		TreeNode <T> *save = crr->right;
		delete crr;
		crr = save;
		return;
	}
	//3
	if (crr->data == x && crr->right == nullptr)
	{
		TreeNode <T> *save = crr->left;
		delete crr;
		crr = save;
		return;
	}
	//4
	if (crr->data == x)
	{
		T rightmin = findmin(crr->right);
		crr->data = rightmin;
		removeFromSubtreeProc(rightmin, crr->right);
		removeFromSubtreeProc(x, crr);
		return;

	}
	//5, 6
	if (crr->data < x)
	{
		removeFromSubtreeProc(x, crr->right);
	}
	else {
		removeFromSubtreeProc(x, crr->left);
	}

	return;

}


template <class T>
void BTree<T>::printDotty(std::ostream &out)
{
	out << "digraph G{" << std::endl;
	printNodesDotty(out, root);
	out << "}" << std::endl;
}

template <class T>
void BTree<T>::fillGaps(const T& x, unsigned int h)
{
	fillGaps(x, root, h);
}


template <class T>
void BTree<T>::fillGaps(const T &x, TreeNode<T> *&crr, unsigned int h)
{
	if (h == 0)
	{
		return;
	}

	if (crr == nullptr)
	{
		crr = new TreeNode<T>(x, nullptr, nullptr);
	}

	fillGaps(x, crr->left, h - 1);
	fillGaps(x, crr->right, h - 1);

}

template <class T>
void BTree<T>::printWithStack(std::ostream &out)
{
	std::stack<task<T>> s;

	s.push(task<T>(root, false));

	task<T> currentTask;

	while (!s.empty())
	{
		currentTask = s.top(); s.pop();
		if (currentTask.node != nullptr)
		{
			if (currentTask.toPrintNow)
			{
				out << currentTask.node->data << " ";
			}
			else {
				s.push(task<T>(currentTask.node->right, false));
				s.push(task<T>(currentTask.node, true));
				s.push(task<T>(currentTask.node->left, false));
			}
		}
	}
}

template <class T>
LRoRTreeIterator<T>::LRoRTreeIterator(TreeNode<T> *root)
{
	if (root != nullptr)
	{
		s.push(task<T>(root, false));
		windStack(); //!!!
	}
}

template <class T>
void LRoRTreeIterator<T>::windStack()
{
	//!!! s.top().toPrintNow == false
	while (!s.empty() && s.top().toPrintNow == false)
	{

		task<T> currentTask = s.top(); s.pop();

		if (currentTask.node->right != nullptr)
			s.push(task<T>(currentTask.node->right, false));

		s.push(task<T>(currentTask.node, true));

		if (currentTask.node->left != nullptr)
			s.push(task<T>(currentTask.node->left, false));

	}
}

template <class T>
T LRoRTreeIterator<T>::operator * ()
{
	assert(!s.empty());

	task<T> topTask = s.top();
	return topTask.node->data;
}

template <class T>
bool LRoRTreeIterator<T>::operator != (const LRoRTreeIterator<T> &other)
{
	return !(*this == other);
}


template <class T>
bool LRoRTreeIterator<T>::operator == (const LRoRTreeIterator<T> &other)
{
	//!!***!!!***!!
	//s == other.s следва от това нещо:

	return (s.empty() && other.s.empty()) ||
		(!s.empty() && !other.s.empty() &&
		(s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));

}

template <class T>
LRoRTreeIterator<T>& LRoRTreeIterator<T>::operator ++ (int)
{
	assert(!s.empty());
	s.pop();
	windStack(); //!!!

	return *this;
}

template <class T>
template <class I>
I BTree<T>::begin() // връща всякакви итератори => още един template заради името на съответния итератор
{
	return I(root);
}

template <class T>
template <class I>
I BTree<T>::end()
{
	return I(nullptr);
}

template <class T>
PredIterator<T> BTree<T>::begin(bool (*pred) (const T &))
{
	return PredIterator<T>(root, pred);
}

template <class T>
PredIterator<T> BTree<T>::end(bool(*pred) (const T &))
{
	return PredIterator<T>(nullptr, pred);
}

template <class T>
void BTree<T>::levelsPrint(std::ostream &out)
{
	std::queue<TreeNode<T>*> q;

	if (root == nullptr)
		return;

	q.push(root);
	q.push(nullptr);

	while (q.size() > 1)
	{
		TreeNode<T>* currentNode = q.front();
		q.pop();

		if (currentNode != nullptr)
		{
			out << currentNode->data << " ";

			if (currentNode->left != nullptr)
				q.push(currentNode->left);
			if (currentNode->right != nullptr)
				q.push(currentNode->right);
		}
		else {
			out << std::endl;
			q.push(nullptr);
		}
	}
}
