#pragma once

#include "ITest.h"
#include "structures/list/list.h"

using namespace std;
using namespace structures;

class ListTest : public ITest<int>
{
public:
	ListTest(List<int>& list);
	~ListTest();
	int setOperation();
	void setOption(char& scenario);

	void runTesting();
	int generating(int min, int max);

	void add();
	void remove();
	void set();
	void index();

	void mesaureTime();

private:
	List<int>* list_;

	int counterAdd;
	int tempAdd;
	int counterRemove;
	int tempRemove;
	int counterSet;
	int tempSet;
	int counterIndex;
	int tempIndex;
};