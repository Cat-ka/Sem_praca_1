#include "array2D_test.h"

using namespace std;

Array2D_test::Array2D_test(int nRows, int nColumn, int initValue) : nRows_(nRows), nColumns_(nColumn), initValue_(initValue)
{
	//this->nRows_ = nRows;
	//this->nColumns_ = nColumn;
	//this->initValue_ = initValue;	
}

Array2D_test::~Array2D_test()
{
}

/*
Array2D<int>& Array2D_test::chooseArray2D(int adt, char scenario)
{
	string name;
	name.append(1, scenario);
	if (adt == 4) {
		array2D_;		
		cout << "Chystas sa testovat s˙visl˙ maticu. \n" << endl;
		fileName = name + "_Array2D_contiguous.txt";
	}
	else if (adt == 5) {
		//array2D_non = new Array2Dnoncontiguous<int>(nRows_, nColumns_, initValue_);
		//tato je st·le potomkom. ked to pomenÌm, musÌm odkomentovaù
		cout << "Chystas sa testovat nes˙visl˙ maticu. \n" << endl;
		fileName = name + "_Array2D_noncontiguous.txt";
	}
	return array2D_;
}
*/

