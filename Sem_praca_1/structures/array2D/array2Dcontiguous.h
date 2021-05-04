#pragma once

#include <iostream>
#include "array2D.h"
#include "../array/array.h"
#include "../vector/vector.h"
#include "../array/array.h"
#include "../heap_monitor.h"

using namespace structures;
using namespace std;

template <typename T>
class Array2Dcontiguous : public Array2D<T>
{
public:
	Array2Dcontiguous(const size_t rows, const size_t columns, const T initValue);
	//Array2Dcontiguous();
	Array2Dcontiguous(const Array2Dcontiguous<T>& other);
	~Array2Dcontiguous();
	//Array2D<T>& makeArray2D(unsigned nRows, unsigned nColumns, T initValue) override;

	int getNumberOfRows() override;
	int getNumberOfColumns() override;
	size_t size() const override;
	Structure* clone() const override;
	
	void show() override;
	Array2D<T>& operator=(const Array2D<T>& other) override;
	Array2Dcontiguous<T>& operator=(const Array2Dcontiguous<T>& other);
	//T& opertor()(const int indexRow, const int indexColumn) override;
	T get(unsigned indexR, unsigned indexC) override;
	void set(unsigned indexR, unsigned indexC, T value) override;
	//void changeParameters(unsigned rows, unsigned columns);

protected:
	unsigned nRows_;
	unsigned nColumns_;
	T initValue_;
	int mapFunction(const int indexRow, const int indexColumn) const;
	Array<T>* array_;
	Vector* vector_;

};

template<typename T>
Array2Dcontiguous<T>::Array2Dcontiguous(const size_t rows, const size_t columns, const T initValue) :
	Array2D<T>::Array2D(),
	array_(new Array<T>(rows* columns)),
	nRows_(rows),
	nColumns_(columns),
	initValue_(initValue)
	//napr. Array<int> *a = new Array<int>(4)
{
	for (int i = 0; i < rows * columns; i++)
	{
		(*array_)[i] = initValue;
	}
}

/*
template<typename T>
inline Array2Dcontiguous<T>::Array2Dcontiguous()
{
	this->makeArray2D(unsigned nRows, unsigned nColumns, T initValue);
}
*/

template<typename T>
inline Array2Dcontiguous<T>::Array2Dcontiguous(const Array2Dcontiguous<T>& other) :
	Array2D<T>::Array2D(),
	array_(new Array<T>(*(other.array_)))
{
}

template<typename T>
inline Array2Dcontiguous<T>::~Array2Dcontiguous()
{
	delete array_;
	this->array_ = nullptr;
	this->nRows_ = 0;
	this->nColumns_ = 0;
	this->initValue_ = 0;
}


template<typename T>
inline int Array2Dcontiguous<T>::getNumberOfRows()
{
	return this->nRows_;
}

template<typename T>
inline int Array2Dcontiguous<T>::getNumberOfColumns()
{
	return this->nColumns_;
}

template<typename T>
inline size_t Array2Dcontiguous<T>::size() const
{
	return this->nRows_ * this->nColumns_;
}

template<typename T>
inline Structure* Array2Dcontiguous<T>::clone() const
{
	return new Array2Dcontiguous<T>(*this);
}

template<typename T>
inline void Array2Dcontiguous<T>::show()
{
	for (int i = 0; i < this->nRows_; i++)
	{
		for (int j = 0; j < this->nColumns_; j++)
		{
			int index = this->mapFunction(i, j);
			cout << (*array_)[index] << " ";
		}
		cout << endl;
	}
}


template<typename T>
inline Array2D<T>& Array2Dcontiguous<T>::operator=(const Array2D<T>& other)
{
	if (this != &other)
	{
		*this = dynamic_cast<const Array2Dcontiguous<T>&>(other);
	}
	return *this;
}


template<typename T>
inline Array2Dcontiguous<T>& Array2Dcontiguous<T>::operator=(const Array2Dcontiguous<T>& other)
{
	if (this != &other)
	{
		if (this->nRows_ != other.nRows_ && this->nColumns_ != other.nColumns_)
		{
			throw std::logic_error("Array2Dcontiguous<T>::operator=: Arrays` sizes differ!");
		}
		*this->array_ = *other.array_;
	}
	return *this;
}

template<typename T>
inline T Array2Dcontiguous<T>::get(unsigned indexR, unsigned indexC)
{
	DSRoutines::rangeCheckExcept(indexR, this->nRows_, "Array2Dcontiguous<T>::get: invalid index");
	DSRoutines::rangeCheckExcept(indexC, this->nColumns_, "Array2Dcontiguous<T>::get: invalid index");
	int index = this->mapFunction(indexR, indexC);
	T temp = (*array_)[index];
	return temp;
}

template<typename T>
inline void Array2Dcontiguous<T>::set(unsigned indexR, unsigned indexC, T value)
{
	DSRoutines::rangeCheckExcept(indexR, this->nRows_, " Array2Dcontiguous<T>::set: invalid index");
	DSRoutines::rangeCheckExcept(indexC, this->nColumns_, " Array2Dcontiguous<T>::set: invalid index");
	int index = this->mapFunction(indexR, indexC);
	(*array_)[index] = value;
}

template<typename T>
inline int Array2Dcontiguous<T>::mapFunction(const int indexRow, const int indexColumn) const
{
	return this->nColumns_ * indexRow + indexColumn;
}


