#pragma once

#include "ITest.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/list/list.h"


//namespace structures
using namespace std;

template<typename T>
class ListTest : public ITest<T>
{
public:
	ListTest();
	~ListTest();
	int setOperation();
	void setOption(char& scenario);
	
	void runTesting();
	int generating(int& min, int& max);

	void add();
	void remove();
	void set();
	void index();

	void mesaureTime();	


private:
	List list_;


	int counterAdd;
	int tempAdd;
	int counterRemove;
	int tempRemove;
	int counterSet;
	int tempSet;
	int counterIndex;
	int tempIndex;
};

template<typename T>
inline ListTest<T>::ListTest()
{
	tempAdd = 0;
	tempRemove = 0;
	tempSet = 0;
	tempIndex = 0;
}

template<typename T>
inline ListTest<T>::~ListTest()
{
}

template<typename T>
inline int ListTest<T>::setOperation()
{

	return 0;
}

template<typename T>
inline void ListTest<T>::setOption(char& scenario) {
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

template<typename T>
inline int ListTest<T>::generating(int& min, int& max) {
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

template<typename T>
inline void ListTest<T>::runTesting() {
	//20 vloz prvy, vloz posledny, vloz na index
	//add, insert

	//20 zrus prvy, zrus posledny, zrus na indexe
	//removeAt

	//50 spristupni, nastav
	//operator= operator[]

	//10 index prvku 
	//getIndexOf

	for (int i = 0; i < 10; i++)
	{
		List<T>* list_ = new List<T>();
		List<T>;
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

template<typename T>
inline void ListTest<T>::add()
{
	cout << "Idem pridavat.";
	int temp = this->generating(0, 2);
	int data = this->generating(0, 100);
	switch (temp) {
	case 0:
		List<int>::add(data);
		break;
	case 1:
		List<int>::insert(data, 0);
		break;
	default:
		List<int>::insert(data, List<int>::size());
		break;
	}
}

template<typename T>
inline void ListTest<T>::remove()
{
	this->generating(0, 2);

}

template<typename T>
inline void ListTest<T>::set()
{
	this->generating(0, 1);
}

template<typename T>
inline void ListTest<T>::index()
{

}

template<typename T>
inline void ListTest<T>::mesaureTime()
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


