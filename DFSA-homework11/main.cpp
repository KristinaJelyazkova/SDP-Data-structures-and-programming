#include <cassert>
#include<iostream>
#include<fstream>
#include<sstream>
#include "fsa.h"


void testSimple()
{
	DFSA a;

	a.setFinalState(0);
	a.setFinalState(1000);
	a.setFinalState(500);

	a[0]['a'] = 1000;
	a[0]['b'] = 500;
	a[0]['c'] = 5000;

	assert(a[0]['a'] == 1000);
	assert(a[0]['b'] == 500);
	assert(a[0]['c'] == 5000);

	assert(a.hasSymbol(0, 'a'));
	assert(!a.hasSymbol(0, 'z'));

	std::vector<char> symbols = a.getSymbolsFrom(0);

	assert(std::find(symbols.begin(), symbols.end(), 'a') != symbols.end());
	assert(std::find(symbols.begin(), symbols.end(), 'z') == symbols.end());

	std::cout << "Symbols from 0:";
	for (char c : a.getSymbolsFrom(0))
	{
		std::cout << c;
	}
	std::cout << std::endl;

}

void testGrammar() {
	const char* FILE_NAME = "grammar.txt";
	std::ifstream in(FILE_NAME);
	bool flag1 = true;
	std::string s;
	char c = in.peek();
	DFSA a(c - 'A');
	while (!in.eof()) {	//!in.endOfFile()
		if (in.peek() == '\n') in.ignore();
		std::getline(in, s);
		//std::cout << s << std::endl;
		/*if (in.eof()) {
			break;
		}*/
		if (s.size() == 7) {
			//std::cout << "seven";
			a.addTransition(s[0] - 'A', s[6] - 'A', s[5]);
		}
		if (s.size() == 6) {
			//std::cout << "six";
			if (flag1) {
				a.setFinalState('Z' - 'A' + 1);
				flag1 = false;
			}
			a.addTransition(s[0] - 'A', 'Z' - 'A' + 1, s[5]);
		}
	}
	/*	A := aB
		B := vC
		C := z
		A := dD
		D := f	
	assert(a['A' - 'A']['a'] == 'B' - 'A');
	assert(a['B' - 'A']['v'] == 'C' - 'A');
	assert(a['C' - 'A']['z'] == 'Z' - 'A' + 1);
	assert(a['D' - 'A']['f'] == 'Z' - 'A' + 1);
	assert(a['A' - 'A']['d'] == 'D' - 'A');*/

	std::ofstream out("automata.dot");
	out << "digraph G {" << std::endl;
	a.printDotty(out);
	out << "}" << std::endl;
}



int main()
{
	//testSimple();
	testGrammar();
	system("pause");
	return 0;
}