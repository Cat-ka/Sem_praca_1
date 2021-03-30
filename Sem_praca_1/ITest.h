#pragma once

#include "structures/heap_monitor.h"
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>

//using namespace std::chrono

template<typename T>
class ITest {
public:
	ITest();
	~ITest();

	int generating(int min, int max);

	
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




