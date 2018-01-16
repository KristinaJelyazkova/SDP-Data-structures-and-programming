#ifndef _DFSA_
#define _DFSA_

#include<vector>
#include<map>
#include<iostream>
#include<fstream>

class DFSA {
private:
	struct state;
	struct transitionProxy {
	private:
		state *s;
		char symbol;
	public:
		transitionProxy(state*, char);
		void operator=(unsigned int);
		operator unsigned int() const;
	};
	struct state {
		unsigned int label;
		bool isFinal;
		bool isMarked;
		std::map<char, unsigned int> transitions;
		DFSA *a;

		state(DFSA *);
		transitionProxy operator[](char);
	};
public:
	DFSA(unsigned int = 0);
	std::vector<char> getSymbolsFrom(unsigned int);
	state& operator[](unsigned int);
	void addTransition(unsigned int, char, unsigned int);
	void setFinalState(unsigned int);
	unsigned int toState(unsigned int, char);
	bool hasSymbol(unsigned int, char);

	void printDotty(std::ostream&);
	bool readsWord(std::string);
private:
	std::vector<state> table;
	unsigned int initialState;
	std::map<unsigned int, unsigned int> labelToIndex;

	unsigned int indexOf(unsigned int);
	unsigned int labelOf(unsigned int);

	void printDotty(std::ostream&, state&);
	bool readsWord(std::string, state&, int);
};

std::vector<char> DFSA::getSymbolsFrom(unsigned int labelFrom) {
	unsigned int indexFrom = indexOf(labelFrom);
	std::map<char, unsigned int> transitions = table[indexFrom].transitions;
	std::vector<char> result;
	for (std::map<char, unsigned int>::iterator it = transitions.begin(); it != transitions.end(); it++) {
		result.push_back(it->first);
	}
	return result;
}

DFSA::DFSA(unsigned int _initialState = 0) {
	initialState = indexOf(_initialState);
}

DFSA::transitionProxy::operator unsigned int() const{
	return s->a->labelOf(s->transitions[symbol]);
}

DFSA::transitionProxy::transitionProxy(state *_s, char _symbol) 
	: s(_s), symbol(_symbol){}

void DFSA::transitionProxy::operator=(unsigned int labelTo) {
	s->a->addTransition(s->label, labelTo, symbol);
}

DFSA::state& DFSA::operator[](unsigned int label) {
	return table[indexOf(label)];
}

DFSA::state::state(DFSA *_a) : a(_a), isFinal(false){}

DFSA::transitionProxy DFSA::state::operator[](char symbol) {
	return transitionProxy(this, symbol);
}

void DFSA::setFinalState(unsigned int label) {
	table[indexOf(label)].isFinal = true;
}

unsigned int DFSA::labelOf(unsigned int index) {
	return table[index].label;
}

unsigned int DFSA::indexOf(unsigned int label) {
	if (labelToIndex.count(label) == 0) {
		labelToIndex[label] = table.size();
		state newState(this);
		newState.label = label;
		table.push_back(newState);
	}
	return labelToIndex[label];
}

void DFSA::addTransition(unsigned int labelFrom, char symbol, unsigned int labelTo) {
	table[indexOf(labelFrom)].transitions[symbol] = indexOf(labelTo);
}

unsigned int DFSA::toState(unsigned int labelFrom, char symbol) {
	return labelOf(table[indexOf(labelFrom)].transitions[symbol]);
}

bool DFSA::hasSymbol(unsigned int labelFrom, char symbol) {
	if (labelToIndex.count(labelFrom) == 0) {
		return false;
	}
	return table[indexOf(labelFrom)].transitions.count(symbol) > 0;
}

void DFSA::printDotty(std::ostream& out){
	printDotty(out, table[0]);
}

void DFSA::printDotty(std::ostream& out, state& crr){
	if (crr.isMarked || getSymbolsFrom(crr.label).empty()) {
		return;
	}
	out << crr.label << "[label=\"" << (char) ('A' + crr.label) << "\"];" << std::endl;
	crr.isMarked = true;
	for (char c : getSymbolsFrom(crr.label)) {
		out << crr.label << "->" << crr.transitions[c] << "[label=\"" << c << "\"];" << std::endl;
	}
	for (char c : getSymbolsFrom(crr.label)) {
		printDotty(out, table[crr.transitions[c]]);
	}
}

bool DFSA::readsWord(std::string s) {
	return readsWord(s, table[0], 0);
}

bool DFSA::readsWord(std::string s, state& crr, int index) {
	if (index >= s.length()) {
		return crr.isFinal;
	}
	if (!hasSymbol(crr.label, s[index])) {
		return false;
	}
	return readsWord(s, table[crr.transitions[s[index]]], index + 1);
}

#endif