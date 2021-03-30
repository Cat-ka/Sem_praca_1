#pragma once
#include "structures/heap_monitor.h"


template <typename T>
class Array2Dcontiguous : public Array2D
{
    T** data_ptr;
    unsigned nRows;
    unsigned nColumns;

    T** create2DArray(unsigned nRows, unsigned nCols, const T& val = T())
    {
        T** ptr = nullptr;
        T* pool = nullptr;
        try
        {
            ptr = new T * [nRows];  // alokuje pointre
            pool = new T[nRows * nCols]{ val };  // alokuje pool

           
            for (unsigned i = 0; i < nRows; ++i, pool += nCols)
                ptr[i] = pool;

            // hotovo a vraciam pole
            return ptr;
        }
        catch (std::bad_alloc & ex)
        {
            delete[] ptr; 
            throw ex;  
        }
    }

public:
    typedef T value_type;
    T** data() {
        return data_ptr;
    }

    unsigned get_rows() const {
        return nRows;
    }

    unsigned get_cols() const {
        return nColumns;
    }

    Array2D() : data_ptr(nullptr), nRows(0), nColumns(0) {}
    Array2D(unsigned rows, unsigned cols, const T& val = T())
    {
        if (rows == 0)
            throw std::invalid_argument("number of rows is 0");
        if (cols == 0)
            throw std::invalid_argument("number of columns is 0");
        data_ptr = create2DArray(rows, cols, val);
        nRows = rows;
        nColumns = cols;
    }

    ~Array2D()
    {
        if (data_ptr)
        {
            delete[] data_ptr[0];  // vymaž pole
            delete[] data_ptr;     // vymaže aj pointre
        }
    }

    Array2D(const Array2D& other) : nRows(other.nRows), nColumns(other.nColumns)
    {
        data_ptr = create2DArray(nRows, nColumns);
        std::copy(&other.data_ptr[0][0], &other.data_ptr[nRows - 1][nColumns], &data_ptr[0][0]);
    }

    Array2D(Array2D&& other) noexcept
    {
        data_ptr = other.data_ptr;
        nRows = other.nRows;
        nColumns = other.nColumns;
        other.data_ptr = nullptr;
    }

    Array2D& operator=(Array2D&& other) noexcept
    {
        if (&other != this)
        {
            swap(other, *this);
        }
        return *this;
    }

    void swap(Array2D& left, Array2D& right)
    {
        std::swap(left.data_ptr, right.data_ptr);
        std::swap(left.nColumns, right.nColumns);
        std::swap(left.nRows, right.nRows);
    }

    Array2D& operator = (const Array2D& other)
    {
        if (&other != this)
        {
            Array2D temp(other);
            swap(*this, temp);
        }
        return *this;
    }

    T* operator[](unsigned row)
    {
        return data_ptr[row];
    }

    const T* operator[](unsigned row) const
    {
        return data_ptr[row];
    }

    void create(unsigned rows, unsigned cols, const T& val = T())
    {
        *this = Array2D(rows, cols, val);
    }
};

/*
int main()
{
    try
    {
        Array2D<double> dPtr(10, 10);
        std::cout << dPtr[0][0] << " " << a2[0][0] << "\n";
    }
    catch (std::exception & ex)
    {
        std::cout << ex.what();
    }
}
*/

/*

template<typename T>
inline int Array<T>::mapFunction(const int index1, const int index2) const
{
    //vráti mi na ktorom indexe vo vectore sa nachádza ten môj požadovaný index po¾a
    return (index1 + index2) * sizeof(T);
}
*/
