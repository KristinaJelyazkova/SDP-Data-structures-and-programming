#include"dfsa.cpp"
#include<fstream>
#include<iostream>
#include<sstream>

void testGrammar() {
	std::ifstream in("grammar.txt");
	std::string rule;
	char initialState = in.peek();
	DFSA a(initialState - 'A');
	a.setFinalState('Z' - 'A' + 1);
	while (!in.eof()) {
		std::getline(in, rule);
		if (rule.length() == 6) {
			a.addTransition(rule[0] - 'A', rule[5], 'Z' - 'A' + 1);
		}
		if (rule.length() == 7) {
			a.addTransition(rule[0] - 'A', rule[5], rule[6] - 'A');
		}
	}
}

void testPrintDotty(){
	DFSA a;
	std::ofstream out("automata.dot");
	out << "digraph G {" << std::endl;
	a.printDotty(out);
	out << "}" << std::endl;
}

int main() {
	system("pause");
	return 0;
}