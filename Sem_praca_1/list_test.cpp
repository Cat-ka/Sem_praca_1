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
	int pocetOpakovani = 1000;
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
	string operation;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::nanoseconds duration;
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
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->list_->size();
	cout << "F: " << operation << " T: " << duration.count() << " microseconds, S: " << actualSize << endl;
	string nazov = "pridavanie.csv";
	zapis(nazov, operation, duration.count(), actualSize);
}

void ListTest::remove()
{
	int temp = this->generating(0, 2);
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::nanoseconds duration;
	int actualSize = this->list_->size();
	switch (temp) {
	case 0:
		start = high_resolution_clock::now();
		this->list_->removeAt(0);
		stop = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(stop - start);
		actualSize = this->list_->size();
		cout << "F: remove_begin, T: " << duration.count() << " microseconds, S: " << actualSize << endl;
		break;
	case 1:
		start = high_resolution_clock::now();
		//if (actualSize > 0) {
		this->list_->removeAt(this->list_->size() - 1);
		//}
		stop = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(stop - start);
		actualSize = this->list_->size();
		cout << "F: remove_end, T: " << duration.count() << " microseconds, S: " << actualSize << endl;
		break;
	default:
		start = high_resolution_clock::now();
		int index;
		if (actualSize > 0) {
			index = this->generating(0, actualSize - 1);
		}
		else {
			index = 0;
		}
		this->list_->removeAt(index);
		stop = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(stop - start);
		actualSize = this->list_->size();
		cout << "F: remove_on_index, T: " << duration.count() << " microseconds, S: " << actualSize << endl;
		break;
	}
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
	std::chrono::nanoseconds duration;
	int actualSize = this->list_->size();
	switch (temp) {
	case 0:
		start = high_resolution_clock::now();
		if (actualSize > 0) {
			this->list_[index];
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(stop - start);
		actualSize = this->list_->size();
		cout << "F: set_spristupni, T: " << duration.count() << " microseconds, S: " << actualSize << endl;
		break;
	default:
		start = high_resolution_clock::now();
		if (actualSize > 0) {
			(*this->list_)[index] = data;
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<nanoseconds>(stop - start);
		actualSize = this->list_->size();
		cout << "F: set_nastav, T: " << duration.count() << " microseconds, S: " << actualSize << endl;
		break;
	}
}

void ListTest::index()
{
	int data = this->generating(0, 100);
	int index = this->generating(0, this->list_->size());
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::nanoseconds duration;
	int actualSize = this->list_->size();

	start = high_resolution_clock::now();
	if (actualSize > 0) {
		this->list_->getIndexOf(data);
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->list_->size();
	cout << "F: index, T: " << duration.count() << " microseconds, S: " << actualSize << endl;

}

List<int>& ListTest::vyberADT(int adt)
{
	if (adt == 1) {
		list_ = new ArrayList<int>();
		cout << "Chystas sa testovat ArrayList. \n" << endl;
		return *list_;
	}
	else if (adt == 2) {
		list_ = new LinkedList<int>();
		cout << "Chystas sa testovat LinkedList. \n" << endl;
		return *list_;
	}
}

void ListTest::zapis(string fileName, string operation, double trvanie, int sizeOf)
{
	ofstream file;
	file.open(fileName, ios_base::app);
	file << operation << ", " << trvanie << ", " << sizeOf << endl;
	file.close();

}



void ListTest::measureTimeStart()
{
	// Using time point and system_clock 
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

}

void ListTest::measureTimeStop() {
	// Using time point and system_clock 
	std::chrono::time_point<std::chrono::system_clock> start, end;

	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	//std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
