#include "scenarioList.h"
#include "../../structures/array/array.h"
#include <ostream>

using namespace std;
using namespace structures;


ScenarioList::ScenarioList()
{
}


ScenarioList::ScenarioList(char scenario)
{
	testingScenarioList = scenario;
}

ScenarioList::~ScenarioList()
{
	testingScenarioList = 0;
}

int ScenarioList::ifCounterAdd(char& scenario)
{
	if (scenario == 'A') {
		return this->counterAdd = 20;
	}
	else if (scenario == 'B') {
		return this->counterAdd = 35;
	}
	else if (scenario == 'C') {
		return this->counterAdd = 45;
	}
	else if (scenario == 'X') {
		percentPomer = 100;
		cout << "Zadaj pomer operacii pre vkladanie v rozsahu od 0 - " << percentPomer << ": " << endl;
		cin >> counterAdd;
		DSRoutines::rangeCheckExcept(counterAdd, percentPomer + 1, "Nauc sa pocitat. Uz si v zapornych cislach.");
		return this->counterAdd;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}

int ScenarioList::ifCounterRemove(char& scenario)
{
	if (scenario == 'A') {
		return this->counterRemove = 20;
	}
	else if (scenario == 'B') {
		return this->counterRemove = 35;
	}
	else if (scenario == 'C') {
		return this->counterRemove = 45;
	}
	else if (scenario == 'X') {
		percentPomer -= getCounterAdd();
		cout << "Zadaj pomer operacii pre rusenie v rozsahu od 0 - " << percentPomer << ": " << endl;
		cin >> counterRemove;
		DSRoutines::rangeCheckExcept(counterRemove, percentPomer + 1, "Nauc sa pocitat. Uz si v zapornych cislach.");
		return this->counterRemove;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}

int ScenarioList::ifCounterSet(char& scenario)
{
	if (scenario == 'A') {
		return this->counterSet = 50;
	}
	else if (scenario == 'B') {
		return this->counterSet = 20;
	}
	else if (scenario == 'C') {
		return this->counterSet = 5;
	}
	else if (scenario == 'X') {
		percentPomer -= getCounterRemove();
		cout << "Zadaj pomer operacii pre spristupenie v rozsahu od 0 - " << percentPomer << ": " << endl;
		cin >> counterSet;
		DSRoutines::rangeCheckExcept(counterSet, percentPomer + 1, "Nauc sa pocitat. Uz si v zapornych cislach.");
		return this->counterSet;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}

int ScenarioList::ifCounterIndex(char& scenario)
{
	if (scenario == 'A') {
		return this->counterIndex = 10;
	}
	else if (scenario == 'B') {
		return this->counterIndex = 10;
	}
	else if (scenario == 'C') {
		return this->counterIndex = 5;
	}
	else if (scenario == 'X') {
		percentPomer -= getCounterSet();
		cout << "Pre Index prvku ostal pomer " << percentPomer << " operacii" << endl;
		this->counterIndex = percentPomer;
		return this->counterIndex;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}

int ScenarioList::getCounterAdd()
{
	return counterAdd;
}

int ScenarioList::getCounterRemove()
{
	return counterRemove;
}

int ScenarioList::getCounterSet()
{
	return counterSet;
}

int ScenarioList::getCounterIndex()
{
	return counterIndex;
}

char ScenarioList::getScenarioList()
{
	return testingScenarioList;
}
