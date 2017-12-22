#include <iostream>

#include "btree.cpp"


void testBuild()
{
	BTree<int> empty;
	BTree<int> t90(90, empty, empty),
		t12(12, t90, empty),
		t30(30, empty, t12),
		t50(50, empty, empty),
		t5(5, t50, empty),
		t7(7, t30, t5);


	t7.insertElement("LL", 100);
	//std::cout << t7;

}

void testTrace()
{
	BTree<int> t;

	t.insertElement("", 10);
	t.insertElement("L", 20);

	//std::cout << t;
}

void testBOT()
{
	BTree<int> t;

	t.insertBOT(10);
	t.insertBOT(20);
	t.insertBOT(5);

	//std::cout << t;

}

bool f1(const int& data) {
	return (data % 2) == 0;
}


void testCountHeightLeaves() {
	BTree<int> t;

	t.insertBOT(5);
	t.insertBOT(3);
	t.insertBOT(4);
	t.insertBOT(3);
	t.insertBOT(6);
	t.insertBOT(10);
	t.insertBOT(12);
	t.insertBOT(3);
	t.insertBOT(2);
	t.insertBOT(7);
	t.insertBOT(9);
	t.insertBOT(8);
	
	char *s = "RRL";
	std::cout << t.count() << " " << t.count(3) << " " << t.searchCount(f1) 
		<< " " << t.countEvens() << " " << t.height() 
		<< " " << t.leaves() << " " << t.minNode()  << " " << t.maxLeaf() 
		<< " " << t.getElement(s) << std::endl;

	/*std::vector<int> v = t.allLeaves();

	for (int i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;*/
}

void testPrettyPrint() {
	BTree<int> t;

	t.insertBOT(5);
	t.insertBOT(3);
	t.insertBOT(4);
	t.insertBOT(3);
	t.insertBOT(6);
	t.insertBOT(10);
	t.insertBOT(12);
	t.insertBOT(3);
	t.insertBOT(2);
	t.insertBOT(7);
	t.insertBOT(9);
	t.insertBOT(8);
	t.insertBOT(6);

	t.prettyPrint();
}


int main()
{
	//testBuild ();
	//testTrace();
	//testCountHeightLeaves();
	testPrettyPrint();
	system("pause");
	testBOT();

}