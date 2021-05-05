#pragma once

#include "../array/array.h"
#include "../vector/vector.h"
#include "../structure.h"
#include "../heap_monitor.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> 2D Pole. </summary>
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

		/// <summary> Nastaví hodnotu prvku na danıch indexoch. </summary>
		/// <param name = "indexR"> Index riadku, na ktorom chcem meni hodnotu. </param>
		/// <param name = "indexC"> Index ståpca, na ktorom chcem meni hodnotu. </param>		
		virtual void set(unsigned indexR, unsigned indexC, T value) = 0;

		/// <summary> Vráti hodnotu na poadovanıch indexoch. </summary>
		/// <param name = "indexR"> Index riadku, z ktorého chceme hodnotu. </param>
		/// <param name = "indexC"> Index ståpca, z ktorého chceme hodnotu. </param>	
		/// <returns> Dáta uloené na poadovanıch indexoch. </returns>
		virtual T get(unsigned indexR, unsigned indexC) = 0;
		
		/// <summary> Vypíše na konzolu 2D pole. </summary>
		virtual void show() = 0;

		/// <summary> Vráti poèet riadkov v 2D poli. </summary>
		/// <returns> Poèet riadkov v 2D poli. </returns>
		virtual int getNumberOfRows() = 0;

		/// <summary> Vráti poèet ståpcov v 2D poli. </summary>
		/// <returns> Poèet ståpcov v 2D poli. </returns>
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

