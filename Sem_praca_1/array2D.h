#pragma once

#include "structures/array/array.h"
#include "structures/list/list.h"
#include "structures/structure.h"
#include "structures/heap_monitor.h"

using namespace structures;

template <typename T>
class Array2D : public Structure
{
public:

	Structure& operator=(const Structure& other) override;
	virtual Array2D<T>& operator=(const Array2D<T> other) = 0;
	virtual T& operator[](const int index) = 0;
	virtual const T operator[](const int index) const = 0;
	
	virtual void clear() = 0;

private:	
	Array2D(unsigned nRows, unsigned nColumn, unsigned initValue);
};


template<typename T>
inline Structure& Array2D<T>::operator=(const Structure& other)
{
	if (this != &other)
	{
		*this = dynamic_cast<const Array2D<T>&>(other);
	}
	return *this;
}

template<typename T>
inline Array2D<T>::Array2D(unsigned nRows, unsigned nColumn, unsigned initValue) :
	Structure()
{
}



