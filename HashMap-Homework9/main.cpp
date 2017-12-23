#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include "HashMap.cpp"
#pragma warning(disable:4996)  
#define _SCL_SECURE_NO_WARNINGS  

unsigned int h(const std::string &s, unsigned int n)
{
	unsigned int sum = 0;
	for (int i = 0; i < s.length(); i++)
	{
		//h("abc") == h("acb");
		sum += s[i];
	}
	return sum % n;
}

void testBasicOp()
{
	HashMap<std::string, int> map(255, h);

	map["John Smith"] = 10;
	map["John Smith"] = 12;
	map["John Simth"] = 15;

	map["Lisa Smith"] = 20;

	assert(map["John Smith"] == 12);
	assert(map["John Simth"] == 15);
	assert(h("John Smith", 255) == h("John Simth", 255));

	assert(map["Lisa Smith"] == 20);

}


void testCompare()
{
	HashMap<std::string, int> map1(255, h);
	HashMap<std::string, int> map2(1, h);

	map1["John Smith"] = 10;
	map1["Lisa Smith"] = 20;

	map2["John Smith"] = 10;
	map2["Lisa Smith"] = 20;

	assert(map1 == map2);

	map2["Sam Doe"] = 20;

	assert(map1 != map2);

}

void testEfficiency() {
	HashMap<std::string, int> map(20, h);
	map["abba"] = 10;
	map["baba"] = 12;
	map["a"] = 15;
	map["ba"] = 20;
	//std::cout << h("abba", 20) << " " << h("baba", 20) << " " << h("a", 20) << " " << h("ba", 20) << std::endl;
	//std::cout << map.efficiency() << std::endl;
	assert(map.efficiency() == 0.5);
}

void testOutput() {
	HashMap<std::string, int> map(255, h);

	map["John Smith"] = 10;
	map["John Smith"] = 12;
	map["John Simth"] = 15;
	map["Lisa Smith"] = 20;

	std::string FILE_NAME = "test.txt";
	std::ofstream out(FILE_NAME);
	out << map;
	//std::cout << map;
}

bool isALetter(char ch) {
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

void testTexts() {
	std::string text1, text2;
	std::getline(std::cin, text1);
	std::getline(std::cin, text2);

	HashMap<std::string, int> map(300, h);
	int start = 0;
	for (int i = 0; i < text1.size(); i++) {
		if (!isALetter(text1[i]) || i == text1.size() - 1) {
			char *word;
			if (i == text1.size() - 1 && isALetter(text1[i])) {
				word = new char[i - start + 2];
				text1.copy(word, i - start + 1, start);
				word[i - start + 1] = '\0';
			}
			else {
				word = new char[i - start + 1];
				text1.copy(word, i - start, start);
				word[i - start] = '\0';
			}
			std::string word1(word);
			std::cout << word1 << std::endl;
			map[word1] = 0;
			while (!isALetter(text1[i]) && i < text1.size()) {
				i++;
			}
			start = i;
		}
	}
	//std::cout << map;
	start = 0;
	for (int i = 0; i < text2.size(); i++) {
		if (!isALetter(text2[i]) || i == text2.size() - 1) {
			char *word;
			if (i == text2.size() - 1 && isALetter(text2[i])) {
				word = new char[i - start + 2];
				text2.copy(word, i - start + 1, start);
				word[i - start + 1] = '\0';
			}
			else {
				word = new char[i - start + 1];
				text2.copy(word, i - start, start);
				word[i - start] = '\0';
			}
			std::string word1(word);
			//std::cout << word1 << std::endl;
			if (map.hasKey(word1)) {
				map[word1] = map[word1] + 1;
			}
			while (!isALetter(text2[i]) && i < text2.size()) {
				i++;
			}
			start = i;
		}
	}
	std::cout << map;
	std::cout << map.sumAllValues() << std::endl;
	std::cout << map.countOfValuesBiggerThanZero() << std::endl;
}

void testText2() {
	std::string text1, text2;
	std::getline(std::cin, text1);

	HashMap<std::string, int> map(300, h);
	int start = 0;
	for (int i = 0; i < text1.size(); i++) {
		if (!isALetter(text1[i]) || i == text1.size() - 1) {
			char *word;
			if (i == text1.size() - 1 && isALetter(text1[i])) {
				word = new char[i - start + 2];
				text1.copy(word, i - start + 1, start);
				word[i - start + 1] = '\0';
			}
			else {
				word = new char[i - start + 1];
				text1.copy(word, i - start, start);
				word[i - start] = '\0';
			}
			std::string word1(word);
			//std::cout << word1 << std::endl;
			if (word1.size() >= 3) {
				if (map.hasKey(word1)) {
					map[word1] = map[word1] + 1;
				}
				else {
					map[word1] = 0;
				}
			}
			while (!isALetter(text1[i]) && i < text1.size()) {
				i++;
			}
			start = i;
		}
	}
	//std::cout << map << std::endl
	std::cout << map.findKeyToBiggestValue() << std::endl;
}

unsigned int h1(const int& n, unsigned int size) {
	return ((n * 200) % 53) % size;
}

void testTask6() {
	//using HashFunction = unsigned int(*)(const KeyType&, unsigned int);
	//HashMap(unsigned _n, HashFunction<KeyType> _h);
	HashMap<int, int> map(200, h1);
	int n;
	std::cin >> n;

	int* key = new int[n];
	int* value = new int[n];

	bool flag = false;
	for (int i = 0; i < n; i++) {
		std::cin >> key[i];
		std::cin >> value[i];
		if (!flag && map.hasKey(key[i])) {
			if (map[key[i]] != value[i]) {
				flag = true;
			}
		}
		map[key[i]] = value[i];
	}
	if (flag) {
		std::cout << "Yes\n";
	}
	else
		std::cout << "No\n";
}

void testOperatorStar() {
	HashMap<std::string, int> a(300, h),
		b(300, h);
	a["Krisi"] = 10;
	a["Ivo"] = 7;
	a["Angel"] = 100;
	a["Todorka"] = 42;

	b["Ivo"] = 18;
	b["Maria"] = 20;
	b["Ivan"] = 50;
	b["Todorka"] = 75;
	b["Kalina"] = 200;

	HashMap<std::string, std::pair<int, int>> c = a * b;
	std::cout << c << std::endl;
}

void testOperatorPlus() {
	HashMap<std::string, int> a(300, h),
		b(300, h);
	a["Krisi"] = 10;
	a["Ivo"] = 7;
	a["Angel"] = 100;
	a["Todorka"] = 42;

	b["Ivo"] = 18;
	b["Maria"] = 20;
	b["Ivan"] = 50;
	b["Todorka"] = 75;
	b["Kalina"] = 200;

	HashMap<std::string, int> c = a + b;
	std::cout << c << std::endl;
}

void f(int &x) {
	x = x * x;
}

void testMap() {
	HashMap<std::string, int> b(300, h);

	b["Ivo"] = 18;
	b["Maria"] = 20;
	b["Ivan"] = 50;
	b["Todorka"] = 75;
	b["Kalina"] = 200;

	b.map(f);
	std::cout << b;
}

std::string f1(const std::string& s) {
	char *res = new char[3];
	s.copy(res, 2);
	res[2] = '\0';
	return res;
}

int f2(const int& x) {
	return 2 * x;
}

void testMapKeys() {
	HashMap<std::string, int> b(300, h);

	b["Ivo"] = 18;
	b["Maria"] = 20;
	b["Ivan"] = 50;
	b["Todorka"] = 75;
	b["Kalina"] = 200;

	b.mapKeys(f1);
	std::cout << b;

	HashMap<int, int> c(300, h1);

	c[1] = 18;
	c[2] = 20;
	c[3] = 50;
	c[4] = 75;
	c[5] = 200;

	c.mapKeys(f2);
	std::cout << c;
}

/*void testTask11() {
	HashMap<std::string, double> m(5, h);
	m["Kalin"] = 1.85; m["Ivan"] = 1.86;
	HashMap<std::string, double> m1(3, h);
	m1["Kalin"] = 2; m1["Petar"] = 2;
	HashMap<std::string, std::vector<double>> mult = m * m1;
	mult = mult * mult;

	assert(mult.hasKey("Kalin"));
	assert(!mult.hasKey("Ivan"));
	assert(!mult.hasKey("Petar"));
	assert(mult["Kalin"].size() == 4);
}*/

void testAppend() {
	std::vector<int> v1;
	for (int i = 0; i < 20; i++) {
		v1.push_back(i);
	}
	std::vector<int> v2;
	for (int i = 30; i < 50; i += 2) {
		v2.push_back(i);
	}
	std::vector<int> v3 = append(v1, v2);
	for (int i = 0; i < v3.size(); i++) {
		std::cout << v3[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	testBasicOp();
	testCompare();
	//std::cout << "Passed!\n";

	testEfficiency();
	//testOutput();

	//testTexts();
	//testText2();

	//testTask6();

	//testOperatorStar();
	//testOperatorPlus();

	//testMap();
	//testMapKeys();

	testAppend();

	system("pause");
	return 0;
}