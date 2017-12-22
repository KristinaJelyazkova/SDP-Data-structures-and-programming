#include<iostream>

#include"ArrayIterator.cpp"
#include"LinkedList.cpp"
#include"Functions.cpp"
#include"StringIterator.cpp"
#include"FunctionIterator.cpp"

void testListCount() {
	LList<int> list;
	list.push(20);
	list.push(0);
	list.push(0);
	list.push(0);
	list.push(3);
	ListIterator<int> it = list.begin();
	std::cout << count<int>(it, 3) << std::endl;
}

void testListDuplicates() {
	LList<int> list;
	list.push(8);
	list.push(1);
	list.push(5);
	list.push(3);
	list.push(11);
	list.push(111);
	list.push(21);
	list.push(0);
	list.push(12);
	list.push(11);
	ListIterator<int> it = list.begin();
	std::cout << duplicates<int>(it) << std::endl;
}

void testListIsSorted() {
	LList<int> list;
	list.push(1);
	list.push(9);
	list.push(18);
	list.push(27);
	list.push(34);
	list.push(43);
	ListIterator<int> it = list.begin();
	std::cout << isSorted<int>(it) << std::endl;
}

void testListPalindrom() {
	LList<int> list;
	list.push(1);
	list.push(9);
	list.push(18);
	list.push(11);
	list.push(18);
	list.push(9);
	list.push(1);
	ListIterator<int> it = list.begin();
	std::cout << palindrom(it) << std::endl;
}

void testArrayCount() {
	int arr[4] = { 3, 2, 3, 3 };
	ArrayIterator<int> it(arr, 4);
	std::cout << count<int>(it, 3) << std::endl;
}

void testArrayDuplicates() {
	int arr[10] = { 0, 2, 1, 8, 5, 1, 6, 3 };
	ArrayIterator<int> it(arr, 8);
	std::cout << duplicatesArray<int>(it) << std::endl;
}

void testArrayIsSorted() {
	int arr[4] = { 3, 5, 6, 7 };
	ArrayIterator<int> it(arr, 4);
	std::cout << isSorted<int>(it) << std::endl;
}

void testArrayPalindrom() {
	int arr[10] = { 3, 5, 6, 7 , 10,  10,  7, 6, 5, 3};
	ArrayIterator<int> it(arr, 10);
	std::cout << palindromArray<int>(it) << std::endl;
}

void testStringCount() {
	char *str = "baklava";
	StringIterator<char> it(str);
	std::cout << count<char>(it, 'a') << std::endl;
}

void testStringDuplicates() {
	char *str = "baklava";
	StringIterator<char> it(str);
	std::cout << duplicatesString<char>(it) << std::endl;
}

void testStringIsSorted() {
	char *str = "ponmkgfedcbt";
	StringIterator<char> it(str);
	std::cout << isSorted<char>(it) << std::endl;
}

void testStringPalindrom() {
	char *str = "babaabab";
	StringIterator<char> it(str);
	std::cout << palindromString<char>(it) << std::endl;
}

char function(unsigned int x) {
	if (x < 26)
		return 'a' + x;
	else return 'z';
}

int function2(unsigned int x) {
	return x * x;
}

void testFunctionIterator() {
	FunctionIterator<char> it(function, 26);
	while (it.more()) {
		std::cout << it.getNext() << " ";
	}
	std::cout << std::endl;

	FunctionIterator<int> it2(function2, 50);
	while (it2.more()) {
		std::cout << it2.getNext() << " ";
	}
	std::cout << std::endl;
}

int main() {
	//testListCount();
	//testListDuplicates();
	//testListIsSorted();
	//testListPalindrom();

	//testArrayCount();
	//testArrayDuplicates();
	//testArrayIsSorted();
	//testArrayPalindrom();

	//testStringCount();
	//testStringDuplicates();
	//testStringIsSorted();
	//testStringPalindrom();

	testFunctionIterator();

	system("pause");
	return 0;
}