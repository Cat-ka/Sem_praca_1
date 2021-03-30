#pragma once

#include "ITest.h"
#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/list/double_linked_list.h"
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
	//ListTest(int adt);	
	ListTest();
	~ListTest();
	
	void runTesting(char& scenario);	

	void add();
	void remove();
	void set();
	void index();
	List<int>& vyberADT(int adt, char scenar);
	void zapis(string fileName, string operation, int trvanie, int sizeOf);
	void vypis();


private:
	List<int>* list_;
	ITest<int>* testujem;
	Scenario s;
	
	int pocetOpakovani = 100;
	int tempAdd;	
	int tempRemove;	
	int tempSet;	
	int tempIndex;
	string fileName;
	string operation;
};