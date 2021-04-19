#pragma once

#include "array2D.h"
#include "array2Dcontiguous.h"
#include "array2Dnoncontiguous.h"
#include <iostream>
#include "array2Dcontiguous.h"
#include "array2Dnoncontiguous.h"

using namespace structures;
using namespace std;

class Array2D_test 
{
public:

	
	//VytvaracSuvislychMatic<int> vsmi;
	//VytvaracNesuvislychMatic<int> vnmi;


	Array2D_test(int nRows, int nColumn, int initValue);
	~Array2D_test();

	Array2D<int>& chooseArray2D(int adt, char scenario);

private:
	Array2Dcontiguous<int>* array2D_;
	Array2Dnoncontiguous<int>* array2D_non;
	int nRows_;
	int nColumns_;
	int initValue_;
	string fileName;
	
};


