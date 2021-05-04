#pragma once

#include "../array/array.h"
#include "../vector/vector.h"
#include "../structure.h"
#include "../heap_monitor.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T>
	class Array2D : public Structure
	{
	public:
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		virtual size_t size() const = 0;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (zoznam), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je zoznam. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		
		virtual Array2D<T>& operator=(const Array2D<T>& other) = 0;

		//virtual Array2D<T>& makeArray2D(unsigned nRows, unsigned nColumns, T initValue) = 0;
		virtual void set(unsigned indexR, unsigned indexC, T value) = 0;
		virtual T get(unsigned indexR, unsigned indexC) = 0;
		//virtual void deleteArray2D() = 0;
		virtual void show() = 0;


		virtual int getNumberOfRows() = 0;
		virtual int getNumberOfColumns() = 0;

	protected:
		Array2D();

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
	inline Array2D<T>::Array2D() :
		Structure()
	{
	}
}

