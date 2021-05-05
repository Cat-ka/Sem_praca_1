#pragma once

#include "../structures/heap_monitor.h"
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

template<typename T>
class ITest {
public:
	ITest();
	~ITest();

	int generating(int min, int max);
	void writeCSV(string fileName, string operation, int time, int sizeOf);	
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
	return genNumber;
}

template<typename T>
inline void ITest<T>::writeCSV(string fileName, string operation, int time, int sizeOf)
{
	ofstream file;
	file.open(fileName, ios_base::app);
	file << operation << ", " << time << ", " << sizeOf << endl;
	file.close();
}






