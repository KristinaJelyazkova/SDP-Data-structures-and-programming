#include <vector>
#include <map>
#include <iostream>
#include <cassert>
#include "fsa.h"

std::vector<char> DFSA::getSymbolsFrom(unsigned int labelFrom)
{
	unsigned int indexFrom = indexof(labelFrom);

	std::map<char, unsigned int> &transations
		= table[indexFrom].transitions;

	std::vector<char> result;

	for (std::map<char, unsigned int>::iterator it = transations.begin();
		it != transations.end();
		it++)
	{
		result.push_back(it->first);
	}

	return result;
}



DFSA::DFSA(unsigned int _initialState)
{
	initialState = indexof(_initialState);
}


DFSA::transitionProxy::operator unsigned int() const
{
	assert(s->transitions.count(symbol) > 0);
	return s->a->labelof(s->transitions[symbol]);
}

DFSA::transitionProxy::transitionProxy(state *_s, char _symbol)
	:s(_s), symbol(_symbol) {}

void DFSA::transitionProxy::operator = (unsigned int label)
{
	s->a->addTransition(s->label, label, symbol);
}

DFSA::state& DFSA::operator [] (unsigned int label)
{
	return table[indexof(label)];
}


DFSA::state::state(DFSA *_a) :a(_a), isFinal(false), marked(false) {}

DFSA::transitionProxy DFSA::state::operator [] (char symbol)
{
	return transitionProxy(this, symbol);
}

void DFSA::setFinalState(unsigned int s)
{
	unsigned ix = indexof(s);

	table[ix].isFinal = true;
}

unsigned int DFSA::labelof(unsigned int ix)
{
	assert(ix < table.size());
	return table[ix].label;
}


unsigned int DFSA::indexof(unsigned int L)
{
	if (labelToIndex.count(L) == 0)
	{

		//в този момент постъпва ново състояние за автомата
		labelToIndex[L] = table.size();
		state newState(this);
		newState.label = L;
		table.push_back(newState);

	}
	return labelToIndex[L];
}

void DFSA::addTransition(unsigned int from,
	unsigned int to,
	char symbol)
{
	unsigned int ixfrom = indexof(from);
	unsigned int ixto = indexof(to);
	table[ixfrom].transitions[symbol] = ixto;

/*#ifdef _debug
	std::cerr << "Adding "
		<< from
		<< "("
		<< ixfrom
		<< "):"
		<< symbol
		<< ":"
		<< to
		<< "("
		<< ixto
		<< ")"
		<< std::endl;
#endif*/
}

unsigned int DFSA::toState(unsigned int from, char s)
{
	return labelof(table[from].transitions[s]);
}

bool DFSA::hasSymbol(unsigned int label, char symbol)
{
	if (labelToIndex.count(label) == 0)
		return false;
	return table[indexof(label)].transitions.count(symbol) > 0;
}

void DFSA::printDotty(std::ostream& out) {
	printDottyHelp(out, table[0]);
}

void DFSA::printDottyHelp(std::ostream& out, state& crr) {
	if (crr.marked) {
		return;
	}
	out << indexof(crr.label)
		<< "[label=\""
		<< (char)('A' + crr.label)
		<< "\"];"
		<< std::endl;
	crr.marked = true;
	if (getSymbolsFrom(crr.label).size() == 0) {
		return;
	}
	for (int i = 0; i < 26; i++) {
		if (hasSymbol(crr.label,'a' + i)){
			out << indexof(crr.label)
				<< "->"
				<< table[indexof(crr.label)].transitions['a' + i]
				//<< ";"
				<< "[label=\""
				<< (char)('a' + i)
				<< "\"];"
				<< std::endl;
		}
	}
	for (int i = 0; i < 26; i++) {
		if (hasSymbol(crr.label, 'a' + i)) {
			printDottyHelp(out, table[table[indexof(crr.label)].transitions['a' + i]]);
		}
	}
}

bool DFSA::readsWord(std::string word) {
	return readsWordHelp(word, 0, table[0]);
}

bool DFSA::readsWordHelp(std::string word, unsigned int index, state& current) {
	if (word.size() <= index) {
		return current.isFinal;
	}
	if (!hasSymbol(current.label, word[index])) {
		return false;
	}
	return readsWordHelp(word, index + 1, table[table[indexof(current.label)].transitions[word[index]]]);
}