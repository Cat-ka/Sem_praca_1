#pragma once

#include "array2D.h"
#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/list.h"
#include "structures/structure.h"


namespace structures
{

	template<typename T>
	class array2Dnoncontiguous : public Array2D<T>
	{
	public:
		array2Dnoncontiguous(int nRows, int nColumn, int initValue);
		~array2Dnoncontiguous();

	private:
		int nRows_;
		int nColumn_;
		int initValue_;
	};

	template<typename T>
	inline array2Dnoncontiguous<T>::array2Dnoncontiguous(int nRows, int nColumn, int initValue) :
		nRows_(nRows), nColumn_(nColumn)
	{
		Array2D newArray2D = new Array<Array<T>*>(nRows_);
		for (int i = 0; i < nRows_; i++)
		{
			for (int j = 0; j < nColumn_; j++)
			{
				newArray2D[i][j] = initValue;
			}
		}
	}

	template<typename T>
	inline array2Dnoncontiguous<T>::~array2Dnoncontiguous()
	{
	}




	/*
	Array<Array<T>*> data;
	data[0][1]


	Data = new Array<Array<T>*>(1);
	for (int i = 0; i < 2.rozmer; i++)
	{
		data[i] = new Array<T> * ();
	}
	*/
}