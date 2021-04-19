#pragma once

//#include "structures/array/array.h"
//#include "structures/list/list.h"
//#include "structures/structure.h"
//#include "structures/heap_monitor.h"
//#include "structures/vector/vector.h"


template <typename T>
class Array2D : public Structure
{
public:


	virtual Array2D<T>* vytvorMaticu(int riadky, int stlpce, int initValue) = 0;

	//T& Array2D<T>::operator[](const int index) = 0;
	//const T Array2D<T>::operator[](const int index) const = 0;

	//virtual Structure* clone() = 0;
	//virtual size_t size() = 0;

	//virtual T get(unsigned nRow, unsigned nCol) = 0;
	//virtual void set(unsigned nRow, unsigned nCol, const T& initValue = T()) = 0;

	//Structure& operator=(const Structure& other);


private:
	//Array2D();
	//Array2D(unsigned nRows, unsigned nColumn, unsigned initValue);
	//Array2D(const Array2D& other);
	//~Array2D() = 0;
	//Vector* vector_;
	//Array<T>* array_;
};

/*
template<typename T>
inline Structure& Array2D<T>::operator=(const Structure& other)
{
	if (this != &other)
	{
		*this = dynamic_cast<const Array2D<T>&>(other);
	}
	return *this;
}
*/

