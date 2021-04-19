#pragma once

#include "../structures/heap_monitor.h"
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

//using namespace std::chrono
using namespace std;

template<typename T>
class ITest {
public:
	ITest();
	~ITest();

	int generating(int min, int max);
	void zapis(string fileName, string operation, int trvanie, int sizeOf);
	//void vypis(List<T> list);


	
protected:

};


template<typename T>
inline ITest<T>::ITest()
{
}

template<typename T>
inline ITest<T>::~ITest()
{
}

template<typename T>
inline int ITest<T>::generating(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	int genNumber = dis(gen);
	//std::cout << "Generovane cislo: " << genNumber << std::endl;
	return genNumber;
}

template<typename T>
inline void ITest<T>::zapis(string fileName, string operation, int trvanie, int sizeOf)
{
	ofstream file;
	file.open(fileName, ios_base::app);
	file << operation << ", " << trvanie << ", " << sizeOf << endl;
	file.close();
}

/*
template<typename T>
inline void ITest<T>::vypis(List<T> list)
{
	for (size_t i = 0; i < list->size(); i++)
	{
		cout << this->list_->operator[](i) << " ";
	}
	cout << endl;
}
*/





