
#include "structures/structure.h"
#include <iostream>
#include "testing/list_test.h"
#include "testing/PriorityQueueTest.h"
#include "testing/array2D_test.h"
#include "structures/array2D/array2D.h"
#include "structures/array2D/array2Dcontiguous.h"
#include "structures/array2D/array2Dnoncontiguous.h"
#include "structures/heap_monitor.h"
#include "../../AUS/structures/heap_monitor.h"

using namespace structures;
using namespace std;

int main()
{
	initHeapMonitor();

	cout << "Zacinam testovat.  \n \n" << endl;

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

	if (adt == 4 || adt == 5) {
		cout << "Vyberte typ scenara na testovanie: \n";
		cout << "A - sucet matic\n";
		cout << "B - sucin matic \n";
		cout << "Vasa volba: ";
	}
	else
	{
		cout << "Vyberte typ scenara na testovanie: \n";
		cout << "A \n";
		cout << "B \n";
		cout << "C \n";
		cout << "X - vlastny scenar \n";
		cout << "Vasa volba: ";
	}

	cin >> scenar;
	scenar = toupper(scenar);

	if (adt == 1 || adt == 2 || adt == 3)
	{
		ListTest* testuj = new ListTest();
		ScenarioList* vyberScenar = new ScenarioList(scenar);
		testuj->chooseADT(adt, scenar);
		testuj->runTesting(scenar);
		delete vyberScenar;
		delete testuj;
	}
	else if (adt == 6 || adt == 7 || adt == 8)
	{
		PriorityQueueTest* testujQueue = new PriorityQueueTest();
		ScenarioPriorityQueue* vyberScenar = new ScenarioPriorityQueue(scenar);
		testujQueue->chooseADT(adt, scenar);
		testujQueue->runTesting(scenar);
		delete vyberScenar;
		delete testujQueue;
	}
	else if (adt == 4 || adt == 5)
	{
		Array2D_test* testujArray = new Array2D_test();
		testujArray->runTesting(adt, scenar);
		delete testujArray;
	}	
	return 0;
}