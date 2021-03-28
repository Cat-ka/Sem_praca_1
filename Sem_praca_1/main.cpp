#include <iostream>
#include "list_test.h"
#include "structures/list/list.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "scenario.h"

using namespace structures;
using namespace std;

int main() {
	cout << "Zacinam testovat.  \n \n" << endl;
	ListTest* testuj = new ListTest();
	
	int adt;
	char scenar;
	cout << "Zvolte cislo ADT pre testovanie: \n";
	cout << "1. ArrayList \n";
	cout << "2. LinkedList \n";
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
	Scenario* vyberScenar = new Scenario(scenar);
	//char temp = vyberScenar->getScenario();
	testuj->vyberADT(adt, scenar);
	testuj->runTesting(scenar);
	
	
	
	
	

	

	
	//testuj->generating(1, 250);
	//(*testuj).generating(1, 250);
	//(*testuj).mesaureTime()
	//testuj.option();
	
	//mame vybrané èo chceme testova a pod¾a akého scénara adt a scenar
	   
	return 0;


}