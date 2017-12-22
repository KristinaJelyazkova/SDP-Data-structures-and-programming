#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

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


void testDelete()
{
	BTree<int> t;

	int save = -1, toInsert = -1;

	for (int i = 0; i < 50; i++)
	{

		toInsert = rand() % 100;
		if (i == 25)
		{
			save = toInsert;
		}
		t.insertBOT(toInsert);
	}

	std::ofstream f1("before.dot");
	t.printDotty(f1);

	assert(t.member(save));

	t.deleteBOT(save);

	std::ofstream f2("after.dot");
	t.printDotty(f2);
	assert(!t.member(save));

	std::cout << save;
}


void testFill()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);



	std::ofstream f1("before.dot");
	t7.printDotty(f1);

	t7.fillGaps(0, 5);

	std::ofstream f2("after.dot");
	t7.printDotty(f2);
}

void testPrintWithStack()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);


	t7.printWithStack(std::cout);

	std::stringstream str;
	t7.printWithStack(str);

	int x, y, z;
	str >> x >> y >> z;
	assert(x == 30);
	assert(y == 90);
	assert(z == 12);

	//или
	assert(str.str() == "30 90 12 7 50 5 ");

}

void testIterator()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);

	LRoRTreeIterator<int> it = t7.begin<LRoRTreeIterator<int>>();

	while (it != t7.end<LRoRTreeIterator<int>>())
	{
		std::cout << *it << " ";
		it++;
	}
}

void testBFS()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);

	t7.levelsPrint(std::cout);
}

void testRootRightLeft() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t18(18, empty, empty),
		t12(12, t90, t18),
		t15(15, empty, empty),
		t30(30, t15, t12),
		t50(50, empty, empty),
		t10(10, empty, empty),
		t5(5, t50, t10),
		t7(7, t30, t5);

	oRLTreeIterator<int> it = t7.begin<oRLTreeIterator<int>>();

	while (it != t7.end<oRLTreeIterator<int>>())
	{
		std::cout << *it << " ";
		it++;
	}
}

void testLeftRightRoot() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t18(18, empty, empty),
		t12(12, t90, t18),
		t15(15, empty, empty),
		t30(30, t15, t12),
		t50(50, empty, empty),
		t10(10, empty, empty),
		t5(5, t50, t10),
		t7(7, t30, t5);

	LRoTreeIterator<int> it = t7.begin<LRoTreeIterator<int>>();

	while (it != t7.end<LRoTreeIterator<int>>())
	{
		std::cout << *it << " ";
		it++;
	}
}

void testLevelIterator() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t18(18, empty, empty),
		t12(12, t90, t18),
		t15(15, empty, empty),
		t30(30, t15, t12),
		t50(50, empty, empty),
		t10(10, empty, empty),
		t5(5, t50, t10),
		t7(7, t30, t5);

	LevelIterator<int> it = t7.begin<LevelIterator<int>>();

	while (it != t7.end<LevelIterator<int>>())
	{
		std::cout << *it << " ";
		it++;
	}
}

void testLeafIterator() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t18(18, empty, empty),
		t12(12, t90, t18),
		t15(15, empty, empty),
		t30(30, t15, t12),
		t50(50, empty, empty),
		t10(10, empty, empty),
		t5(5, t50, t10),
		t7(7, t30, t5);

	LeafIterator<int> it = t7.begin<LeafIterator<int>>();

	while (it != t7.end<LeafIterator<int>>())
	{
		std::cout << *it << " ";
		it++;
	}
}

bool even(const int& x) {
	return (x % 2 == 0);
}

void testPredIterator() {
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t18(18, empty, empty),
		t12(12, t90, t18),
		t15(15, empty, empty),
		t30(30, t15, t12),
		t50(50, empty, empty),
		t10(10, empty, empty),
		t5(5, t50, t10),
		t7(7, t30, t5);

	PredIterator<int> it = t7.begin(even);

	while (it != t7.end(even))
	{
		std::cout << *it << " ";
		it++;
	}
}

int main()
{
	srand(0);

	//  testBuild ();
	//  testTrace();
	//  testBOT();
	//  testMemory();
	//  testDelete ();
	//  testFill();
	//  testSerialize ();
	//  testPrintWithStack();
	 //testIterator();
	//testBFS();

	//testRootRightLeft();
	//testLeftRightRoot();
	//testLevelIterator();
	//testLeafIterator();
	testPredIterator();

	system("pause");
	return 0;
}