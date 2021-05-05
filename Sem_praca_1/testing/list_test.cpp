#include "list_test.h"
#include <iostream>

using namespace std::chrono;

ListTest::ListTest()
{
	tempAdd = 0;
	tempRemove = 0;
	tempSet = 0;
	tempIndex = 0;
}

ListTest::~ListTest()
{
	delete this->list_;
	this->list_ = nullptr;
	delete this->testing;
	this->testing = nullptr;
	tempAdd = 0;
	tempRemove = 0;
	tempSet = 0;
	tempIndex = 0;
}

List<int>& ListTest::chooseADT(int adt, char scenar)
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
	else if (adt == 3) {
		list_ = new DoubleLinkedList<int>();
		cout << "Chystas sa testovat obojstranne zretazeny LinkedList. \n" << endl;
		fileName = name + "_DoubleLinkedList.txt";
	}
	return *list_;
}

void ListTest::runTesting(char& scenario)
{
	int cAdd = s_.ifCounterAdd(scenario);
	int cRem = s_.ifCounterRemove(scenario);
	int cSet = s_.ifCounterSet(scenario);
	int cInd = s_.ifCounterIndex(scenario);
	for (int i = 0; i < this->numberOfRepeating; i++)
	{
		int pocetOperacii = generating(1, 100);
		if ((pocetOperacii < cAdd) && (tempAdd < (numberOfRepeating / 100 * cAdd))) {
			tempAdd++;
			add();
		}
		else if ((pocetOperacii < (cAdd + cRem)) && (tempRemove < (numberOfRepeating / 100 * cRem))) {
			tempRemove++;
			remove();
		}
		else if ((pocetOperacii < (cAdd + cRem + cSet)) && (tempSet < (numberOfRepeating / 100 * cSet))) {
			tempSet++;
			set();
		}
		else if (tempIndex < (numberOfRepeating / 100 * cInd)) {
			tempIndex++;
			index();
		}
		else
		{
			if (tempAdd < (numberOfRepeating / 100 * cAdd))
			{
				tempAdd++;
				add();
			}
			else if (tempRemove < (numberOfRepeating / 100 * cRem))
			{
				tempRemove++;
				remove();
			}
			else
			{
				tempSet++;
				set();
			}
		}
		//vypis();
	}

}

void ListTest::add()
{
	int temp = this->generating(0, 2);
	int data = this->generating(0, 100);
	int actualSize = this->list_->size();
	switch (temp)
	{
	case 0:
		start = high_resolution_clock::now();
		this->list_->add(data);
		stop = high_resolution_clock::now();
		operation = "add_end";
		break;
	case 1:
		start = high_resolution_clock::now();
		this->list_->insert(data, 0);
		stop = high_resolution_clock::now();
		operation = "add_begin";
		break;
	default:
		int index;
		if (actualSize > 0) {
			index = this->generating(0, actualSize - 1);
		}
		else {
			index = 0;
		}
		start = high_resolution_clock::now();
		this->list_->insert(data, index);
		stop = high_resolution_clock::now();
		operation = "add_on_index";
		break;
	}
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " nanoseconds, S: " << actualSize << endl;
	writeCSV(this->fileName, operation, duration.count(), actualSize);
}

void ListTest::remove()
{
	int temp = this->generating(0, 2);
	int actualSize = this->list_->size();
	switch (temp) {
	case 0:
		start = high_resolution_clock::now();
		this->list_->removeAt(0);
		stop = high_resolution_clock::now();
		operation = "remove_begin";
		break;
	case 1:
		start = high_resolution_clock::now();
		this->list_->removeAt(this->list_->size() - 1);
		stop = high_resolution_clock::now();
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
		start = high_resolution_clock::now();
		this->list_->removeAt(index);
		stop = high_resolution_clock::now();
		operation = "remove_on_index";
		break;
	}	
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " nanoseconds, S: " << actualSize << endl;
	writeCSV(this->fileName, operation, duration.count(), actualSize);
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

	int actualSize = this->list_->size();
	switch (temp) {
	case 0:
		if (actualSize > 0) {
			start = high_resolution_clock::now();
			this->list_[index];
			stop = high_resolution_clock::now();
			operation = "set_[]";
		}
		break;
	default:
		if (actualSize > 0) {
			start = high_resolution_clock::now();
			(*this->list_)[index] = data;
			stop = high_resolution_clock::now();
			operation = "set_=";
		}
		break;
	}
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " nanoseconds, S: " << actualSize << endl;
	writeCSV(this->fileName, operation, duration.count(), actualSize);
}

void ListTest::index()
{
	int data = this->generating(0, 100);
	int index = this->generating(0, this->list_->size());
	int actualSize = this->list_->size();

	//start = high_resolution_clock::now();
	if (actualSize > 0) {
		start = high_resolution_clock::now();
		this->list_->getIndexOf(data);
		stop = high_resolution_clock::now();
		operation = "getIndexOf";
	}
	//stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->list_->size();
	//cout << "F: " << operation << " T: " << duration.count() << " nanoseconds, S: " << actualSize << endl;
	writeCSV(this->fileName, operation, duration.count(), actualSize);

}

void ListTest::print()
{
	for (size_t i = 0; i < this->list_->size(); i++)
	{
		cout << this->list_->operator[](i) << " ";
	}
	cout << endl;
}
