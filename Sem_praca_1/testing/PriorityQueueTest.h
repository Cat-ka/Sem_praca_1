#pragma once

#include "../testing/ITest.h"
#include "../structures/heap_monitor.h"
#include "../testing/scenario/scenarioPriorityQueue.h"
#include "../structures/priority_queue/priority_queue.h"
#include "../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../structures/priority_queue/heap.h"
#include "../structures/priority_queue/priority_queue_two_lists.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace structures;

class PriorityQueueTest
{
public:
	PriorityQueueTest();
	~PriorityQueueTest();

	void runTesting(char& scenario);
	void makeOperation(int number);

	
	PriorityQueue<int>& chooseADT(int adt, char scenar);
	void write();


private:
	PriorityQueue<int>* queue_;
	ITest<int>* testing;
	ScenarioPriorityQueue s_;

	double numberOfRepeating = 100000;
	int tempPush;
	int tempPop;
	int tempPeek;
	string fileName;
	string operationName;
	int operation;
	int actualSize;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::nanoseconds duration;
};