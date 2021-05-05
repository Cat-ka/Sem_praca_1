#include "PriorityQueueTest.h"

using namespace std::chrono;

PriorityQueueTest::PriorityQueueTest()
{
	tempPush = 0;
	tempPop = 0;
	tempPeek = 0;
}

PriorityQueueTest::~PriorityQueueTest()
{
	delete this->queue_;
	this->queue_ = nullptr;
	tempPush = 0;
	tempPop = 0;
	tempPeek = 0;
}

void PriorityQueueTest::runTesting(char& scenario)
{
	int cPush = s_.ifCounterPush(scenario);
	int cPop = s_.ifCounterPop(scenario);
	int cPeek = s_.ifCounterPeek(scenario);
	for (int i = 0; i < this->pocetOpakovani; i++)
	{
		double pocetOperacii = testujem->generating(1, 100);
		if ((pocetOperacii < cPush) && (tempPush < (pocetOpakovani / 100 * cPush)))
		{
			tempPush++;
			this->makeOperation(1);
		}
		else if ((pocetOperacii < (cPush + cPop)) && (tempPop < (pocetOpakovani / 100 * cPop)))
		{
			if (this->queue_->size() > 0)
			{
				tempPop++;
				this->makeOperation(2);
			}
			else
			{

				tempPush++;
				this->makeOperation(1);
			}
		}
		else if (tempPeek < (pocetOpakovani / 100 * cPeek))
		{
			if (this->queue_->size() > 0)
			{
				tempPeek++;
				this->makeOperation(3);
			}
			else
			{
				tempPush++;
				this->makeOperation(1);
			}
		}
		else
		{
			if (tempPush < (pocetOpakovani / 100 * cPush))
			{
				tempPush++;
				this->makeOperation(1);
			}
			else if (tempPop < (pocetOpakovani / 100 * cPop))
			{
				tempPop++;
				this->makeOperation(2);
			}
			else
			{
				tempPeek++;
				this->makeOperation(3);
			}
		}
		vypis();
	}
}

void PriorityQueueTest::makeOperation(int number)
{
	int data;
	int priority;
	if (number == 1)
	{
		data = testujem->generating(0, 100);
		priority = testujem->generating(0, 10000);
		cout << "Vlozeny prvok: " << priority << endl;
		start = high_resolution_clock::now();
		this->queue_->push(priority, data);
		stop = high_resolution_clock::now();
		operationName = "push";
	}
	else if (number == 2)
	{
		start = high_resolution_clock::now();
		this->queue_->pop();
		stop = high_resolution_clock::now();
		operationName = "pop";
	}
	else
	{
		start = high_resolution_clock::now();
		this->queue_->peek();
		stop = high_resolution_clock::now();
		operationName = "peek";
	}
	duration = duration_cast<nanoseconds>(stop - start);
	actualSize = this->queue_->size();
	cout << "F: " << operationName << " T: " << duration.count() << " nanoseconds, S: " << actualSize << endl;	
	testujem->writeCSV(this->fileName, operationName, duration.count(), actualSize);
}

PriorityQueue<int>& PriorityQueueTest::vyberADT(int adt, char scenar)
{
	string name;
	name.append(1, scenar);
	if (adt == 6) {
		this->queue_ = new PriorityQueueSortedArrayList<int>();
		cout << "Chystas sa testovat utriedeny prioritny front. \n" << endl;
		fileName = name + "_PriorityQueueSortedArrayList.txt";
	}
	else if (adt == 7) {
		this->queue_ = new Heap<int>();
		cout << "Chystas sa testovat lavostrannu haldu. \n" << endl;
		fileName = name + "_Heap.txt";
	}
	else if (adt == 8) {
		this->queue_ = new PriorityQueueTwoLists<int>();
		cout << "Chystas sa testovat dvojzoznam. \n" << endl;
		fileName = name + "_PriorityQueueTwoLists.txt";
	}
	return *queue_;
}

void PriorityQueueTest::vypis()
{
	for (size_t i = 0; i < this->queue_->size(); i++)
	{
		cout << this->queue_->peekPriority() << " ";
	}
	cout << endl;
}


void PriorityQueueTest::push()
{
}

void PriorityQueueTest::pop()
{
}

void PriorityQueueTest::peek()
{
}



