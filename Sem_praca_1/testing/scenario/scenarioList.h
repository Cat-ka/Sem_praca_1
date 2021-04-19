#pragma once

#include "../../structures/list/array_list.h"
#include "../../structures/heap_monitor.h"
#include <iostream>

using namespace std;
using namespace structures;

class ScenarioList
{
public:
	ScenarioList();
	ScenarioList(char scenario);
	~ScenarioList();
	int ifCounterAdd(char& scenario);
	int ifCounterRemove(char& scenario);
	int ifCounterSet(char& scenario);
	int ifCounterIndex(char& scenario);
	int getCounterAdd();
	int getCounterRemove();
	int getCounterSet();
	int getCounterIndex();
	char getScenarioList();
private:
	int counterAdd;
	int counterRemove;
	int counterSet;
	int counterIndex;
	int percentPomer;
	char testingScenarioList;
	//Array<int>* setScenarioList;
};
