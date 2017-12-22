#include <iostream>
#include <fstream>

#include "btree.cpp"


void testSerialize()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);


	std::ofstream f("tree.txt");

	f << t7;

	f.close();

	BTree<int> newTree;
	std::ifstream fin("tree.txt");

	newTree.read(fin);

	//assert (t7==newTree);

	std::cout << std::endl << newTree;
}

void testBuild()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);


	t7.insertElement("RR", 100);
	std::cout << t7;

}

void testTrace()
{
	BTree<int> t;

	t.insertElement("", 10);
	t.insertElement("L", 20);

	std::cout << t;
}

void testBOT()
{
	BTree<int> t;

	t.insertBOT(10);
	t.insertBOT(20);
	t.insertBOT(5);

	std::cout << t;

	assert(t.member(5));
	assert(!t.member(6));

}

void testMemory()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);

	BTree<int> *tmp = new BTree<int>(t7);

	assert(tmp->member(90));
	assert(tmp->member(7));
	assert(*tmp == t7);

	delete tmp;
	assert(t7.member(90));
	assert(t7.member(7));

	t90 = t7;
	assert(t90 == t7);
	t7 = t7;
	assert(t90 == t7);
	assert(t7 == t7);

}

void testParseExpression() {
	std::string s = "((1*(9+3))/((7+1)-2))";
	BTree<char> t;
	t.parseExpression(s);
	t.prettyPrint();
	std::cout << "Expression = " << t.calculateExpressionTree() << std::endl;
}

void testLevel() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t1(1, empty, empty),
		t30(30, t1, t12),
		t50(50, empty, empty),
		t8(8, empty, empty),
		t5(5, t50, t8),
		t7(7, t30, t5);
	std::vector<int> list = t7.level(3);
	for (int i = 0; i < list.size(); i++) {
		std::cout << list[i] << " ";
	}
	std::cout << std::endl;
}

void testOperator() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t1(1, empty, empty),
		t30(30, t1, t12),
		t50(50, empty, empty),
		t8(8, empty, empty),
		t5(5, t50, t8),
		t7(7, t30, t5);
	for (int i = 0; i < t7.count(); i++) {
		std::cout << t7[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < t7.count(); i++) {
		t7[i] = (i * 4);
	}
	for (int i = 0; i < t7.count(); i++) {
		std::cout << t7[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	//testBuild();
	//testTrace();
	//testBOT();
	//testMemory();
	//testSerialize();

	//testParseExpression();
	//testLevel();
	testOperator();
	system("pause");
	return 0;
}