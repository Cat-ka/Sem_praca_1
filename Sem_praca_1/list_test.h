#pragma once

#include "ITest.h"
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "scenario.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace structures;

class ListTest : public ITest<int>
{
public:
	ListTest(int adt);	
	ListTest();
	~ListTest();
	
	void runTesting(char& scenario);	

	void add();
	void remove();
	void set();
	void index();
	List<int>& vyberADT(int adt);
	void zapis(string fileName, string operation, double trvanie, int sizeOf);

	void ListTest::measureTimeStart();
	void ListTest::measureTimeStop();

private:
	List<int>* list_;
	ITest<int>* testujem;
	Scenario s;
	
	int tempAdd;	
	int tempRemove;	
	int tempSet;	
	int tempIndex;
};