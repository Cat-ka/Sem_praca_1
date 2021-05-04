#pragma once

#include <iostream>
#include "array2D.h"
#include "../vector/vector.h"
#include "../array/array.h"
#include "../heap_monitor.h"

using namespace structures;
using namespace std;

template <typename T>
class Array2Dnoncontiguous : public Array2D<T>
{
public:
	Array2Dnoncontiguous(const size_t rows, const size_t columns, const T initValue);
	Array2Dnoncontiguous(const Array2Dnoncontiguous<T>& other);
	~Array2Dnoncontiguous();
	//Array2D<T>& makeArray2D(unsigned nRows, unsigned nColumns, T initValue) override;

	int getNumberOfRows() override;
	int getNumberOfColumns() override;
	size_t size() const override;
	Structure* clone() const override;

	void show() override;
	Array2D<T>& operator=(const Array2D<T>& other) override;
	Array2Dnoncontiguous<T>& operator=(const Array2Dnoncontiguous<T>& other);
	//T& opertor()(const int indexRow, const int indexColumn) override;
	T get(unsigned indexR, unsigned indexC) override;
	void set(unsigned indexR, unsigned indexC, T value) override;

protected:
	unsigned nRows_;
	unsigned nColumns_;
	T initValue_;
	//int mapFunction(const int indexRow, const int indexColumn) const;
	Array<Array<T>*>* array_;
	Vector* vector_;

};

template<typename T>
Array2Dnoncontiguous<T>::Array2Dnoncontiguous(const size_t rows, const size_t columns, const T initValue) :
	Array2D<T>::Array2D(),
	//array_(new Array<T>(rows* columns)),
	nRows_(rows),
	nColumns_(columns),
	initValue_(initValue)
	//napr. Array<int> *a = new Array<int>(4)
{
	this->array_ = new Array<Array<T>*>(this->nRows_);
	for (int i = 0; i < this->nRows_; i++)
	{
		(*array_)[i] = new Array<T>(this->nColumns_);
	}

	for (int  i = 0; i < this->nRows_; i++)
	{
		for (int j = 0; j < this->nColumns_; j++)
		{
			(*(*array_)[i])[j] = this->initValue_;
		}
	}
}

template<typename T>
inline Array2Dnoncontiguous<T>::Array2Dnoncontiguous(const Array2Dnoncontiguous<T>& other) :
	Array2D<T>::Array2D(),
	nRows_(other.nRows_),
	nColumns_(other.nColumns_),
	initValue_(other.initValue_)	
{
	*this = other;
}


template<typename T>
inline Array2Dnoncontiguous<T>::~Array2Dnoncontiguous()
{
	for (int i = 0; i < this->nRows_; i++)
	{
		delete this->array_->operator[](i);
		(*this->array_)[i] = nullptr;
		this->nRows_ = 0;
		this->nColumns_ = 0;
		this->initValue_ = 0;
	}
}

template<typename T>
inline Structure* Array2Dnoncontiguous<T>::clone() const
{
	return new Array2Dnoncontiguous<T>(*this);
}

template<typename T>
inline void Array2Dnoncontiguous<T>::show()
{
	for (int i = 0; i < this->nRows_; i++)
	{
		for (int j = 0; j < this->nColumns_; j++)
		{
			//int index = this->mapFunction(i, j);
			cout << this->get(i,j) << " ";
		}
		cout << endl;
	}
}

template<typename T>
inline Array2D<T>& Array2Dnoncontiguous<T>::operator=(const Array2D<T>& other)
{
	if (this != &other)
	{
		*this = dynamic_cast<const Array2Dnoncontiguous<T>&>(other);
	}
	return *this;
}

template<typename T>
inline Array2Dnoncontiguous<T>& Array2Dnoncontiguous<T>::operator=(const Array2Dnoncontiguous<T>& other)
{
	if (this != &other)
	{
		if (this->nRows_ != other.nRows_ && this->nColumns_ != other.nColumns_)
		{
			throw std::logic_error("Array2Dnoncontiguous<T>::operator=: Arrays` sizes differ!");
		}
		*this->array_ = *other.array_;
	}
	return *this;
}

template<typename T>
inline T Array2Dnoncontiguous<T>::get(unsigned indexR, unsigned indexC)
{
	T temp = (*(*array_)[indexR])[indexC];
	return temp;
	//return (*(*array_)[indexR])[indexC];
}

template<typename T>
inline void Array2Dnoncontiguous<T>::set(unsigned indexR, unsigned indexC, T value)
{
	(*(*array_)[indexR])[indexC] = value;
}


template<typename T>
inline int Array2Dnoncontiguous<T>::getNumberOfRows()
{
	return this->nRows_;
}

template<typename T>
inline int Array2Dnoncontiguous<T>::getNumberOfColumns()
{
	return this->nColumns_;
}

template<typename T>
inline size_t Array2Dnoncontiguous<T>::size() const
{
	return this->nRows_ * this->nColumns_;
}
