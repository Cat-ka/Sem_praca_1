#pragma once

#include "ITest.h"
#include "../structures/heap_monitor.h"
#include "../structures/list/list.h"
#include "../structures/list/array_list.h"
#include "../structures/list/linked_list.h"
#include "../structures/list/double_linked_list.h"
#include "../testing/scenario/scenarioList.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace structures;

class ListTest : public ITest<int>
{
public:	
	ListTest();
	~ListTest();
	
	void runTesting(char& scenario);	

	void add();
	void remove();
	void set();
	void index();
	List<int>& vyberADT(int adt, char scenar);
	void vypis();


private:
	List<int>* list_;
	ITest<int>* testujem;
	ScenarioList s_;
	
	double pocetOpakovani = 1000;
	double tempAdd;
	double tempRemove;
	double tempSet;
	double tempIndex;
	string fileName;
	string operation;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::nanoseconds duration;
};