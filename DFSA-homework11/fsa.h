#pragma once
#ifndef __DFSA_
#define __DFSA_

#include <vector>
#include <map>
#include <iostream>
#include <cassert>

class DFSA
{

private:
	struct state;
	struct transitionProxy
	{
		transitionProxy(state*, char);
		void operator = (unsigned int);
		operator unsigned int() const;
	private:
		state *s;
		char symbol;
	};

	struct state
	{
		bool isFinal;
		int label;
		bool marked;
		//table[i] -> редът на състоянието i в таблицата
		//table[i]['a'] -> целево състояние при преход от i с 'a'
		std::map<char, unsigned int> transitions;

		transitionProxy operator [] (char);
		state(DFSA *);

		DFSA *a;
	};

public:

	DFSA(unsigned int = 0);

	std::vector<char> getSymbolsFrom(unsigned int);

	void setFinalState(unsigned int);
	void addTransition(unsigned int, unsigned int, char);

	state& operator [] (unsigned int);

	unsigned int toState(unsigned int, char);

	bool hasSymbol(unsigned int, char);
	void printDotty(std::ostream&);
	bool readsWord(std::string);

private:

	std::vector<state> table;
	//label[L] е пореден номер (индекс) на състоянието с
	//етикет L
	std::map<int, int> labelToIndex;
	unsigned int initialState;

	unsigned int indexof(unsigned int);
	unsigned int labelof(unsigned int);
	void printDottyHelp(std::ostream&, state&);
	bool readsWordHelp(std::string, unsigned int, state&);
};

#endif