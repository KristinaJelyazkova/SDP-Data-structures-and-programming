#include <cassert>
#include <string>
#include <iostream>

#include "triemap.cpp"

void testTrie()
{
	TrieMap<int> tr;

	tr["t"] = 1;
	tr["te"] = 2;
	tr["tea"] = 3;
	tr["a"] = 4;
	tr["a"] = 5;

	assert(tr["t"] == 1);
	assert(tr["te"] == 2);
	assert(tr["tea"] == 3);
	assert(tr["a"] == 5);

	TrieMap<int> trCopy(tr);

	assert(trCopy["t"] == 1);
	assert(trCopy["te"] == 2);
	assert(trCopy["tea"] == 3);
	assert(trCopy["a"] == 5);

	TrieMap<int> tr2;

	tr2["t"] = 10;
	tr2["tr"] = 20;
	tr2["tree"] = 30;
	tr2["a"] = 40;
	tr2["ah"] = 50;

	trCopy = tr2;

	assert(trCopy["t"] == 10);
	assert(trCopy["tr"] == 20);
	assert(trCopy["tree"] == 30);
	assert(trCopy["a"] == 40);
	assert(trCopy["ah"] == 50);
}

int main()
{
	testTrie();
	std::cout << "Passed!\n";

	system("pause");
	return 0;
}