#include "list_test.h"

using namespace std::chrono;


ListTest::ListTest(int atd)
{
	if (atd = 1) {
		list_ = new ArrayList<int>();
	}
	else if (atd = 2)
	{
		list_ = new LinkedList<int>();
	}
	//list_ = &list;

}

ListTest::ListTest()
{
	tempAdd = 0;
	tempRemove = 0;
	tempSet = 0;
	tempIndex = 0;
}



ListTest::~ListTest()
{
}


void ListTest::runTesting(char& scenario)
{
	int pocetOpakovani = 100000;
	int cAdd = s.ifCounterAdd(scenario);
	int cRem = s.ifCounterRemove(scenario);
	int cSet = s.ifCounterSet(scenario);
	int cInd = s.ifCounterIndex(scenario);

	for (int i = 0; i < pocetOpakovani; i++)
	{
		int pocetOperacii = generating(1, 100);

		if ((pocetOperacii < cAdd) && (tempAdd <= (pocetOpakovani / 100 * cAdd))) {
			tempAdd++;
			add();
		}
		else if (pocetOperacii < (cAdd + cRem)) {
			tempRemove++;
			if (tempRemove <= (pocetOpakovani / 100 * cRem)) {
				remove();
			}
		}
		else if (pocetOperacii < (cAdd + cRem + cSet)) {
			tempSet++;
			if (tempSet <= (pocetOpakovani / 100 * cSet)) {
				set();
			}
		}
		else {
			tempIndex++;
			if (tempIndex <= (pocetOpakovani / 100 * cInd)) {
				index();
			}
		}

	}

}


void ListTest::add()
{

	int temp = this->generating(0, 2);
	int data = this->generating(0, 100);
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::microseconds duration;
	int actualSize = 0;
	start = high_resolution_clock::now();
	switch (temp)
	{
	case 0:
		this->list_->add(data);
		operation = "add_end";
		break;
	case 1:
		this->list_->insert(data, 0);
		operation = "add_begin";
		break;
	default:
		this->list_->insert(data, this->list_->size());
		operation = "add_on_index";
		break;
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " microseconds, S: " << actualSize << endl;
	zapis(this->fileName, operation, duration.count(), actualSize);
}

void ListTest::remove()
{
	int temp = this->generating(0, 2);
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::microseconds duration;
	int actualSize = this->list_->size();

	start = high_resolution_clock::now();

	switch (temp) {
	case 0:

		this->list_->removeAt(0);
		operation = "remove_begin";
		break;

	case 1:

		this->list_->removeAt(this->list_->size() - 1);
		operation = "remove_end";
		break;
	default:

		int index;
		if (actualSize > 0) {
			index = this->generating(0, actualSize - 1);
		}
		else {
			index = 0;
		}
		this->list_->removeAt(index);
		operation = "remove_on_index";
		break;
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " microseconds, S: " << actualSize << endl;
	zapis(this->fileName, operation, duration.count(), actualSize);
}

void ListTest::set()
{
	int temp = this->generating(0, 1);
	int data = this->generating(0, 100);
	int index;
	if (this->list_->size() > 0) {
		index = this->generating(0, this->list_->size() - 1);
	}
	else {
		index = 0;
	}
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::microseconds duration;
	int actualSize = this->list_->size();

	start = high_resolution_clock::now();

	switch (temp) {
	case 0:
		
		if (actualSize > 0) {
			this->list_[index];
			operation = "set_[]";
		}		
		break;
	default:		
		if (actualSize > 0) {
			(*this->list_)[index] = data;
			operation = "set_=";
		}		
		break;
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " microseconds, S: " << actualSize << endl;
	zapis(this->fileName, operation, duration.count(), actualSize);
}

void ListTest::index()
{
	int data = this->generating(0, 100);
	int index = this->generating(0, this->list_->size());
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::microseconds duration;
	int actualSize = this->list_->size();

	start = high_resolution_clock::now();
	if (actualSize > 0) {
		this->list_->getIndexOf(data);
		operation = "getIndexOf";
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " microseconds, S: " << actualSize << endl;
	zapis(this->fileName, operation, duration.count(), actualSize);

}

List<int>& ListTest::vyberADT(int adt, char scenar)
{
	string name;
	name.append(1, scenar);
	if (adt == 1) {
		list_ = new ArrayList<int>();
		cout << "Chystas sa testovat ArrayList. \n" << endl;
		fileName = name + "_ArrayList.txt";
	}
	else if (adt == 2) {
		list_ = new LinkedList<int>();
		cout << "Chystas sa testovat LinkedList. \n" << endl;
		fileName = name + "_LinkedList.txt";
	}
	return *list_;
}

void ListTest::zapis(string fileName, string operation, int trvanie, int sizeOf)
{
	ofstream file;
	file.open(fileName, ios_base::app);
	file << operation << ", " << trvanie << ", " << sizeOf << endl;
	file.close();

}

