#pragma once

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

	//int setOperation() override;


	//void runTesting() override;
	int generating(int min, int max);
	//void odmerajTrvanieOperacie();

	//void add() override;
	//void remove() override;
	//void set() override;
//	void index() override;

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
	//unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	//std::minstd_rand0 g1(seed1);  // minstd_rand0 is a standard linear_congruential_engine
	//int result = g1() % max + min;
	//std::cout << "A time seed produced: " << result << std::endl;
	//return 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	int genNumber = dis(gen);
	std::cout << "Generovane cislo: " << genNumber << std::endl;
	return genNumber;
}




