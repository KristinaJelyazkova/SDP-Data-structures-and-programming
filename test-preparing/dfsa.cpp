#ifndef _DFSA_
#define _DFSA_

#include<vector>
#include<map>
#include<iostream>
#include<fstream>

class DFSA {
private:
	class StatesIterator {
	public:
		StatesIterator(DFSA const*, unsigned int);
		unsigned int operator *() const;
		StatesIterator& operator ++();
		bool operator !=(const StatesIterator&) const;
	private:
		DFSA const *a;
		unsigned int crrStateIndex;
	};
public:
	StatesIterator& begin() const;
	StatesIterator& end() const;
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
		friend class DFSA;
	private:
		unsigned int label;
		bool isFinal;
		bool isMarked;
		std::map<char, unsigned int> transitions;
		DFSA *a;
	public:
		state(DFSA *);
		transitionProxy operator[](char);
		unsigned int operator[](char) const;
		bool final() const;
	public:
		class SymbolsIterator {
		public:
			SymbolsIterator(state const*, bool = false);
			char operator*() const;
			SymbolsIterator& operator++();
			bool operator!=(const SymbolsIterator&) const;
		private:
			state *s;
			std::map<char, unsigned int>::const_iterator transitionsIterator;
		};
		SymbolsIterator& begin() const;
		SymbolsIterator& end() const;
	};
public:
	DFSA(unsigned int = 0);
	std::vector<char> getSymbolsFrom(unsigned int);
	state& operator[](unsigned int);
	const state& operator[](unsigned int) const;
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
	unsigned int labelOf(unsigned int) const;
	unsigned int indexOf(unsigned int) const;

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

const DFSA::state& DFSA::operator[](unsigned int label) const{
	return table[indexOf(label)];
}

DFSA::state::state(DFSA *_a) : a(_a), isFinal(false){}

DFSA::transitionProxy DFSA::state::operator[](char symbol) {
	return transitionProxy(this, symbol);
}

unsigned int DFSA::state::operator[](char symbol) const{
	return a->labelOf(transitions.at(symbol));
}


void DFSA::setFinalState(unsigned int label) {
	table[indexOf(label)].isFinal = true;
}

unsigned int DFSA::labelOf(unsigned int index) const{
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

unsigned int DFSA::indexOf(unsigned int label) const{
	return labelToIndex.at(label);
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

DFSA::StatesIterator::StatesIterator(DFSA const* _a, unsigned int _index)
	: a(_a), crrStateIndex(_index) {}

unsigned int DFSA::StatesIterator::operator *() const {
	return a->table[crrStateIndex].label;
}
		
DFSA::StatesIterator& DFSA::StatesIterator::operator++() {
	crrStateIndex++;
	return (*this);
}
		
bool DFSA::StatesIterator::operator !=(const StatesIterator& other) const {
	return a != other.a || crrStateIndex != other.crrStateIndex;
}

DFSA::StatesIterator& DFSA::begin() const {
	return StatesIterator(this, 0);
}

DFSA::StatesIterator& DFSA::end() const {
	return StatesIterator(this, table.size());
}

DFSA::state::SymbolsIterator::SymbolsIterator(state const*_s, bool end) {
	if (end) {
		s = nullptr;
		transitionsIterator = s->transitions.end();
	}
	else {
		s = _s;
		transitionsIterator = s->transitions.begin();
	}
}

char DFSA::state::SymbolsIterator::operator*() const {
	return transitionsIterator->first;
}

DFSA::state::SymbolsIterator& DFSA::state::SymbolsIterator::operator++() {
	transitionsIterator++;
	return (*this);
}

bool DFSA::state::SymbolsIterator::operator!=(const SymbolsIterator& other) const {
	return s != other.s || transitionsIterator != other.transitionsIterator;
}

DFSA::state::SymbolsIterator& DFSA::state::begin() const {
	return SymbolsIterator(this);
}

DFSA::state::SymbolsIterator& DFSA::state::end() const{
	return SymbolsIterator(this, true);
}

bool DFSA::state::final() const {
	return isFinal;
}

#endif