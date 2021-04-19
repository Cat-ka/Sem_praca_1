#include <iostream>
#include "testing/list_test.h"
#include "testing/PriorityQueueTest.h"
#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "structures/list/double_linked_list.h"
#include "testing/array2D_test.h"

#include "testing/scenario/scenarioList.h"

using namespace structures;
using namespace std;

int main() {
	initHeapMonitor();

	cout << "Zacinam testovat.  \n \n" << endl;
	ListTest* testuj = new ListTest();
	PriorityQueueTest* testujQueue = new PriorityQueueTest();

	int adt;
	char scenar;
	cout << "Zvolte cislo ADT pre testovanie: \n";
	cout << "1. ArrayList \n";
	cout << "2. LinkedList \n";
	cout << "3. DoubleLinkedList \n";
	cout << "4. Suvisla matica \n";
	cout << "5. Nesuvisla matica \n";
	cout << "6. Prioritny utriedeny front \n";
	cout << "7. Lavostrannu haldu \n";
	cout << "8. Dvojzoznam \n";
	cout << "Vasa volba: ";
	cin >> adt;



	cout << "Vyberte typ scenara na testovanie: \n";
	cout << "A \n";
	cout << "B \n";
	cout << "C \n";
	cout << "X - vlastny scenar \n";
	cout << "Vasa volba: ";
	cin >> scenar;
	scenar = toupper(scenar);

	if (adt == 1 || adt == 2 || adt == 3)
	{
		ScenarioList* vyberScenar = new ScenarioList(scenar);
		testuj->vyberADT(adt, scenar);
		testuj->runTesting(scenar);
		delete testuj;
		delete vyberScenar;
	}
	else if (adt == 6 || adt == 7 || adt == 8)
	{
		ScenarioPriorityQueue* vyberScenar = new ScenarioPriorityQueue(scenar);
		testujQueue->vyberADT(adt, scenar);
		testujQueue->runTesting(scenar);
	}

	return 0;


}