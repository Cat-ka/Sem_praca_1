#pragma once

#include "../../structures/priority_queue/heap.h"
#include "../../structures/heap_monitor.h"
#include <iostream>

using namespace std;
using namespace structures;

class ScenarioPriorityQueue
{
public:
	ScenarioPriorityQueue();
	ScenarioPriorityQueue(char scenario);
	~ScenarioPriorityQueue();
	int ifCounterPush(char& scenario);
	int ifCounterPop(char& scenario);
	int ifCounterPeek(char& scenario);
	int getCounterPush();
	int getCounterPop();
	int getCounterPeek();
	char getScenarioPriorityQueue();
private:
	int counterPush;
	int counterPop;
	int counterPeek;
	int percentPomer;
	char testingScenarioPriorityQueue;
};

