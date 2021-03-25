#include "list_test.h"


ListTest::ListTest(List<int>& list)
{
	list_ = &list;
	tempAdd = 0;
	tempRemove = 0;
	tempSet = 0;
	tempIndex = 0;
}

ListTest::~ListTest()
{
}

int ListTest::setOperation()
{
	return 0;
}

void ListTest::setOption(char& scenario)
{
	//je lepšie to ma takto? alebo urobi pre každý scénar samostatne funkciu
	if (scenario == 'a') {
		this->counterAdd = 20000;
		this->counterRemove = 20000;
		this->counterSet = 50000;
		this->counterIndex = 10000;
		cout << counterAdd << ", " << counterRemove << ", " << counterSet << ", " << counterIndex;
	}
	else if (scenario == 'b')
	{
		this->counterAdd = 35000;
		this->counterRemove = 35000;
		this->counterSet = 20000;
		this->counterIndex = 10000;
	}
	else if (scenario == 'c') {
		this->counterAdd = 45000;
		this->counterRemove = 45000;
		this->counterSet = 5000;
		this->counterIndex = 5000;
	}
}

void ListTest::runTesting()
{
	//20 vloz prvy, vloz posledny, vloz na index
	//add, insert

	//20 zrus prvy, zrus posledny, zrus na indexe
	//removeAt

	//50 spristupni, nastav
	//operator= operator[]

	//10 index prvku 
	//getIndexOf

	for (int i = 0; i < 1000000; i++)
	{
		
		int temp = generating(1, 100);
		if (temp < counterAdd / 1000) {
			tempAdd++;
			if (tempAdd <= counterAdd) {
				add();
			}
		}
		else if (temp < (counterAdd + counterRemove) / 1000) {
			tempRemove++;
			if (tempRemove <= counterRemove) {
				remove();
			}
		}
		else if (temp < (counterAdd + counterRemove + counterSet) / 1000) {
			tempSet++;
			if (tempSet <= counterSet) {
				set();
			}
		}
		else {
			tempIndex++;
			if (tempIndex < counterIndex) {
				index();
			}
		}
	}
}

int ListTest::generating(int min, int max)
{
	//unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	//std::minstd_rand0 g1(seed1);  // minstd_rand0 is a standard linear_congruential_engine
	//int result = g1() % max + min;
	//std::cout << "A time seed produced: " << result << std::endl;

	//return 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	int genNumber = dis(gen);
	std::cout << genNumber << std::endl;
	return genNumber;
}

void ListTest::add()
{
	cout << "Idem pridavat.";
	int temp = this->generating(0, 2);
	int data = this->generating(0, 100);
	switch (temp) {
	case 0:

		this->list_->add(data);
		break;
	case 1:
		this->list_->insert(data, 0);
		break;
	default:
		this->list_->insert(data, this->list_->size());
		break;
	}
}

void ListTest::remove()
{
	this->generating(0, 2);
	//pri mazaní budem generova index ktorý budem maza od 0 po size
}

void ListTest::set()
{
	this->generating(0, 1);
}

void ListTest::index()
{
}

void ListTest::mesaureTime()
{
	// Using time point and system_clock 
	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::system_clock::now();
	int cislo = generating(1, 250);
	std::cout << "generujem = " << cislo << '\n';
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	//std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
