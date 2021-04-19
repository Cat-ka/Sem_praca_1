#pragma once

#include "array2D.h"
#include "../structures/heap_monitor.h"
#include "../structures/array/array.h"
#include "../structures/list/list.h"
#include "../structures/structure.h"


namespace structures
{

	template<typename T>
	class Array2Dnoncontiguous : public Array2D<T>
	{
	public:
		//Matica<T>* vytvorMaticu(int riadky, int stlpce) override { return new NesuvislaMatica<T>(riadky, stlpce); }
		Array2Dnoncontiguous(int nRows, int nColumn, int initValue);
		~Array2Dnoncontiguous();
		Array2Dnoncontiguous(const Array2Dnoncontiguous& other);

		
		//T** create2DArray(unsigned nRows, unsigned nCols, const T& initValue = T());
		T get(unsigned nRow, unsigned nCol) override;
		void set(unsigned nRow, unsigned nCol, const T& initValue = T()) override;

		//T** data();
		unsigned getRows();
		unsigned getColumns();
		Structure* clone() const override;

	private:
		int nRows_;
		int nColumn_;
		int initValue_;
		Array<T>* array_;
	};

	template<typename T>
	inline Array2Dnoncontiguous<T>::Array2Dnoncontiguous(int nRows, int nColumn, int initValue) :
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
	inline Array2Dnoncontiguous<T>::~Array2Dnoncontiguous()
	{
		for (int i = 0; i < nRows; i++)
		{
			delete (*array_)[i];
			(*array_)[i] = nullptr;
			nRows_ = 0;
			nColumn_ = 0;
		}
		delete array_;
	}

	template<typename T>
	inline Array2Dnoncontiguous<T>::Array2Dnoncontiguous(const Array2Dnoncontiguous & other)
	{

	}


	template<typename T>
	inline Structure* Array2Dnoncontiguous<T>::clone() const
	{
		return new Array2Dnoncontiguous<T>(*this);
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