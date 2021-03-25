#include <iostream>
#include "list_test.h"

using namespace structures;
using namespace std;

int main() {


	cout << "Zaciatok" << endl;

	int adt;
	char scenar;
	cout << "Zvolte cislo ADT pre testovanie: \n";
	cout << "1. ArrayList \n";
	cout << "2. LinkedList \n";
	cout << "Vasa volba: ";
	cin >> adt;
	if (adt == 1) {
		cout << "Chystas sa testovat ArrayList. \n";
	}
	else {
		cout << "Chystas sa testovat LinkedList. \n";
	}

	cout << "Vyberte typ scenara na testovanie: \n";
	cout << "A \n";
	cout << "B \n";
	cout << "C \n";
	cout << "Vasa volba: ";
	cin >> scenar;
	scenar = tolower(scenar);
	if (scenar == 'a' || scenar == 'b' || scenar == 'c') {
		cout << "Pre testovanie ste vybrali scenar " << scenar << endl;
	}
	else {
		do
		{
			cout << "Zadali ste nespravnu volbu. Zadajte hodnotu A, B alebo C pre vyber scenara " << scenar << endl;
			cin >> scenar;
			scenar = tolower(scenar);
		} while (scenar != 'a' && scenar != 'b');
		//nende to. while mi nikdy nešiel.... :(
	}

	//ListTest(List<int>* list)

	ListTest* testuj = new ListTest(new ArrayList<int>&);

	testuj->generating(1, 250);
	//(*testuj).generating(1, 250);
	//(*testuj).mesaureTime()
	//testuj.option();
	
	//mame vybrané èo chceme testova a pod¾a akého scénara adt a scenar
	   
	return 0;
}