#include"dfsa.cpp"
#include<fstream>
#include<iostream>
#include<sstream>
#include<set>
#include<queue>
#include<vector>

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

void dottyPrint() {
	DFSA a;
	std::ofstream out("automata2.dot");
	out << "digraph G {" << std::endl;
	for (unsigned int state : a) {
		for (char symbol : a[state]) {
			out << state << "->" << a[state][symbol] << "[label=\"" << symbol << "\"];" << std::endl;
		}
		if (a[state].final()) {
			out << state << "[shape=\"doublecircle\"];\n";
		}
	}
	out << "}" << std::endl;
}

std::string* findLongestWord(const DFSA& a, unsigned int fromState, std::set<unsigned int> visited) {
	if (visited.count(fromState) > 0) {
		return nullptr;
	}
	visited.insert(fromState);

	std::string *longest = nullptr;

	for (char c : a[fromState]) {
		std::string *found = findLongestWord(a, a[fromState][c], visited);
		if (found != nullptr) {
			*found = c + *found;
		}
		if ((longest == nullptr && found != nullptr)
			|| (longest != nullptr && longest->size() < found->size())) {
			std::string *tmp = longest;
			longest = found;
			delete tmp;
		}
		else {
			delete found;
		}
	}

	if (longest != nullptr) {
		return longest;
	}

	if (a[fromState].final()) {
		return new std::string;
	}
	else {
		return nullptr;
	}
}

#define SENTINEL INT_MAX

bool hasKLongWords(const DFSA &a, unsigned int k) {
	std::queue<unsigned int> q;
	q.push(0);
	q.push(SENTINEL);
	unsigned int level = 0;
	while (!q.empty() && level < k) {
		unsigned int state = q.front();
		q.pop();
		if (state != SENTINEL) {
			for (char c : a[state]) {
				q.push(a[state][c]);
			}
		}
		else if(!q.empty()){
			level++;
			q.push(SENTINEL);
		}
	}
	while (!q.empty()) {
		unsigned int state = q.front();
		q.pop();
		if (state != SENTINEL && a[state].final()) {
			return true;
		}
	}
	return false;
}

void printLanguage(const DFSA &a, unsigned int k) {
	std::vector<std::pair<unsigned int, std::string>> v;

	v.push_back({ 0,"" });
	v.push_back({ SENTINEL,"" });

	unsigned int level = 0;

	while (!v.empty() && level < k) {
		std::pair<unsigned int, std::string> p = v[0];
		v.erase(v.begin());
		const unsigned int &state = p.first;
		const std::string &word = p.second;
		if (state != SENTINEL) {
			for (char c : a[state]) {
				v.push_back({ a[state][c], word + c });
			}
		}
		else if (!v.empty()) {
			level++;
			for (std::pair<unsigned int, std::string> pair : v) {
				if (pair.first != SENTINEL && a[pair.first].final()) {
					std::cout << pair.second << std::endl;
				}
			}
			v.push_back({ SENTINEL, "" });
		}
	}
}

int main() {
	system("pause");
	return 0;
}