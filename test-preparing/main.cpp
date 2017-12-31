#include <iostream>
#include<fstream>

#include "Tree.cpp"


void testBuild()
{
	Tree<int> empty;
	Tree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);


	t7.insertElement("LL", 100);
	//std::cout << t7;
	std::ofstream out("tree.dot");
	out << t7;
}

void testTrace()
{
	Tree<int> t;

	t.insertElement("", 10);
	t.insertElement("L", 20);

	std::cout << t;
}

void testBOT()
{
	Tree<int> t;

	t.insertBOT(10);
	t.insertBOT(20);
	t.insertBOT(5);

	std::cout << t;

}


int main()
{

	testBuild ();
	//testTrace();
	//testBOT();
	system("pause");
	return 0;

}