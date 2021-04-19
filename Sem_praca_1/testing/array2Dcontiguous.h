#pragma once
#include "../structures/heap_monitor.h"
#include "../structures/vector/vector.h"
#include "array2D.h"

using namespace std;

namespace structures
{

	template <typename T>
	class Array2Dcontiguous	: public Array2D<T>	
	{

	public:
		
		//Array2Dcontiguous(int nRows, int nColumn, int initValue);
		Array2Dcontiguous();
		~Array2Dcontiguous();
		Array2Dcontiguous(const Array2Dcontiguous& other);

		Array2D<T>* vytvorMaticu(int riadky, int stlpce, int initValue) override;

		//T& Array2Dcontiguous<T>::operator[](const int nRow, const int nCol) override;
		//const T Array2Dcontiguous<T>::operator[](const int nRow, const int nCol) override;

		T& get(unsigned nRow, unsigned nCol) ;
		void set(unsigned nRow, unsigned nCol, const T& initValue = T()) ;

		/*
		Array2D(unsigned nRows, unsigned nColumn, unsigned initValue);
		Array2D(const Array2D& other) = 0;
		~Array2D() = 0;

		virtual Structure* clone() = 0;

		virtual Array2D get(unsigned nRow, unsigned nCol) = 0;
		virtual Array2D set(unsigned nRow, unsigned nCol, const T& initValue = T()) = 0;
		*/

		void writeArray2D();

		unsigned getRows();
		unsigned getColumns();
		Structure* clone() const override;
		size_t size() const override;

	private:
		//Array2D<T>* data_ptr;
		unsigned nRows_;
		unsigned nColumns_;
		int mapFunction(const int index1, const int index2) const;
		Vector* vector_;
		Array2D* suvislaArray2D_;

	};


	/*
	template<typename T>
	inline Array2Dcontiguous<T>::Array2Dcontiguous()
	{
	}
	*/

	template<typename T>
	inline Array2Dcontiguous<T>::Array2Dcontiguous()
	{		
	}

	template<typename T>
	inline Array2Dcontiguous<T>::Array2Dcontiguous(const Array2Dcontiguous& other) :
		nRows_(other.nRows_),
		nColumns_(other.nColumns_),
		vector_(new Vector(nRows_* nColumns_ * sizeof(T)))
	{
	}

	template<typename T>
	inline Array2D<T>* Array2Dcontiguous<T>::vytvorMaticu(int nRows, int nColumn, int initValue)
	{
		/*
		if (nRows == 0)
			throw std::invalid_argument("number of rows is 0");
		if (nColumn == 0)
			throw std::invalid_argument("number of columns is 0");
		suvislaArray2D_ = dynamic_cast<Array2D>(new Vector * (nRows * nColumn * sizeof(T)));
		nRows_ = nRows;
		nColumns_ = nColumn;
		for (int i = 0; i < suvislaArray2D_->size(); i++)
		{
			suvislaArray2D_[i] = initValue;
		}
		*/
		return suvislaArray2D_;
		
	}

	

	template<typename T>
	inline Array2Dcontiguous<T>::~Array2Dcontiguous()
	{
		if (vector_)
		{
			delete this->vector_;
			this->vector_ = nullptr;
			nRows_ = 0;
			nColumns_ = 0;
		}
	}



	template<typename T>
	inline T& Array2Dcontiguous<T>::get(unsigned nRow, unsigned nCol) 
	{
		//return (*this)->mapFunction(nRow, nCol);
		int vectorIndex = (*this)->mapFunction(nRow, nCol);
		return reinterpret_cast<byte*>(vectorIndex);

		//int vectorIndex = this->mapFunction(index);
		//return *reinterpret_cast<T*>(this->vector_->getBytePointer(vectorIndex));
	}

	template<typename T>
	inline void Array2Dcontiguous<T>::set(unsigned nRow, unsigned nCol, const T& value)
	{
		(*this->vector_)[nRow * nCol] = value;
	}






	template<typename T>
	inline void Array2Dcontiguous<T>::writeArray2D()
	{
		for (int i = 0; i < this->nRows_; i++)
		{
			for (int j = 0; j < this->nColumns_; j++)
			{
				cout << vector_[i][j] << end;
			}
			cout << "" << endl;
		}
	}

	template<typename T>
	inline unsigned Array2Dcontiguous<T>::getRows()
	{
		return nRows_;
	}

	template<typename T>
	inline unsigned Array2Dcontiguous<T>::getColumns()
	{
		return nColumns_;
	}

	
	template<typename T>
	inline Structure* Array2Dcontiguous<T>::clone() const
	{
		return 0; // new Array2Dcontiguous<T>(*this);
	}

	template<typename T>
	inline size_t Array2Dcontiguous<T>::size() const
	{
		return size_t();
	}
	

	template<typename T>
	inline int Array2Dcontiguous<T>::mapFunction(const int index1, const int index2) const
	{
		//vráti mi na ktorom indexe vo vectore sa nachádza ten môj požadovaný index po¾a
		return (index1 + index2) * sizeof(T);
	}

	


};







