#pragma once

#include "../structures/array2D/array2D.h"
#include "../structures/array2D/array2Dcontiguous.h"
#include "../structures/array2D/array2Dnoncontiguous.h"
#include "../structures/heap_monitor.h"
#include "ITest.h"
#include <iostream>
#include <fstream>


using namespace structures;
using namespace std;

class Array2D_test
{
public:
	Array2D_test();
	~Array2D_test();

	void nasobenie(Array2D<int>& first, Array2D<int>& second, Array2D<int>& result);
	void scitanie(Array2D<int>& first, Array2D<int>& second, Array2D<int>& result);
	void runTesting(int adt, char scenario);
	void zapis(string fileName, int columns, int trvanie, int sizeOf);
	
private:
	int n;
	int m;

	int nRows_;
	int nColumns_;
	int initValue_;
	string fileName;
	ITest<int>* testujem;
	Array2D<int>* array2D_;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
	std::chrono::microseconds duration;




};


