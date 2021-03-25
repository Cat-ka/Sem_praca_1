#pragma once

#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/list/list.h"
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>

template<typename T>
class ITest {
public:	
	ITest();
	virtual ~ITest();

	virtual int setOperation() = 0;
	virtual void setOption(char& scenario) = 0;

	virtual void runTesting() = 0;
	virtual int generating(int& min, int& max) const = 0;

	virtual void add() = 0;
	virtual void remove() = 0;
	virtual void set() = 0;
	virtual void index() = 0;
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

