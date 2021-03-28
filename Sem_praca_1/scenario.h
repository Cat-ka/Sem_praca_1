#pragma once

#include "structures/list/array_list.h"
#include <iostream>

using namespace std;
using namespace structures;

class Scenario
{
public:
	//urobiù scenare tak aby mi vracali jednotlivÈ county.... ako returny

	Scenario();
	Scenario(char scenario);
	~Scenario();
	int ifCounterAdd(char& scenario);
	int ifCounterRemove(char& scenario);
	int ifCounterSet(char& scenario);
	int ifCounterIndex(char& scenario);
	int getCounterAdd();
	int getCounterRemove();
	int getCounterSet();
	int getCounterIndex();
	char getScenario();
private:
	int counterAdd;
	int counterRemove;
	int counterSet;
	int counterIndex;
	int percentPomer;
	char testingScenario;
	//Array<int>* setScenario;
};
