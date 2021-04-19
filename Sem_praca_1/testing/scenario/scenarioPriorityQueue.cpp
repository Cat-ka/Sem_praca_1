#include "scenarioPriorityQueue.h"
#include <ostream>

using namespace std;
using namespace structures;


ScenarioPriorityQueue::ScenarioPriorityQueue()
{
}


ScenarioPriorityQueue::ScenarioPriorityQueue(char scenario)
{
	testingScenarioPriorityQueue = scenario;
}

ScenarioPriorityQueue::~ScenarioPriorityQueue()
{
	testingScenarioPriorityQueue = 0;
}

char ScenarioPriorityQueue::getScenarioPriorityQueue()
{
	return testingScenarioPriorityQueue;
}

int ScenarioPriorityQueue::ifCounterPush(char& scenario)
{
	if (scenario == 'A') {
		return this->counterPush = 35;
	}
	else if (scenario == 'B') {
		return this->counterPush = 50;
	}
	else if (scenario == 'C') {
		return this->counterPush = 70;
	}
	else if (scenario == 'X') {
		percentPomer = 100;
		cout << "Zadaj pomer operacii pre operáciu push v rozsahu od 0 - " << percentPomer << ": " << endl;
		cin >> counterPush;
		DSRoutines::rangeCheckExcept(counterPush, percentPomer + 1, "Nauc sa pocitat. Uz si v zapornych cislach.");
		return this->counterPush;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}
	
	int ScenarioPriorityQueue::ifCounterPop(char& scenario)
{
	if (scenario == 'A') {
		return this->counterPop = 35;
	}
	else if (scenario == 'B') {
		return this->counterPop = 30;
	}
	else if (scenario == 'C') {
		return this->counterPop = 25;
	}
	else if (scenario == 'X') {
		percentPomer -= getCounterPush();
		cout << "Zadaj pomer operacii pre rusenie v rozsahu od 0 - " << percentPomer << ": " << endl;
		cin >> counterPop;
		DSRoutines::rangeCheckExcept(counterPop, percentPomer + 1, "Nauc sa pocitat. Uz si v zapornych cislach.");
		return this->counterPop;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}

int ScenarioPriorityQueue::ifCounterPeek(char& scenario)
{
	if (scenario == 'A') {
		return this->counterPeek = 30;
	}
	else if (scenario == 'B') {
		return this->counterPeek = 20;
	}
	else if (scenario == 'C') {
		return this->counterPeek = 5;
	}
	else if (scenario == 'X') {
		percentPomer -= getCounterPop();
		cout << "Pre Index prvku ostal pomer " << percentPomer << " operacii" << endl;
		this->counterPeek = percentPomer;
		return this->counterPeek;
	}
	else
	{
		cout << "Zadal si nespravny parameter." << endl;
		return 0;
	}
}

int ScenarioPriorityQueue::getCounterPush()
{
	return counterPush;
}

int ScenarioPriorityQueue::getCounterPop()
{
	return counterPop;
}

int ScenarioPriorityQueue::getCounterPeek()
{
	return counterPeek;
}
