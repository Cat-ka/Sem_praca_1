#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T>
	class Array : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(const size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(const Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat pola. </summary>
		/// <returns> Ukazovatel na vytvoreny klon pola. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (pole), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je Array. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Pole, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		Array<T>& operator=(const Array<T>& other);

		/// <summary> Operator porovnania. </summary>
		/// <param name = "other"> Pole, s ktorym sa ma porovnat. </param>
		/// <returns> true, ak su polia rovnake, false inak. </returns>
		bool operator==(const Array<T>& other) const;

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		T& operator[](const int index);

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		const T operator[](const int index) const;

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception> 
		static void copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length);

	private:
		/// <summary> Vektor s datami. </summary>
		//objektovÈ atrib˙ty je lepöie definovaù ako pointre, kvÙli miestu v z·sobnÌku
		//nechceme aby zaberalo veæa miesta v z·sobnÌku, preto ho budeme implementovaù na halde
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(const int index) const;
	};

	template<typename T>
	Array<T>::Array(const size_t size) :
		vector_(new Vector(size * sizeof(T))),
		size_(size)
		//napr. Array<int> *a = new Array<int>(4)
	{
	}

	template<typename T>
	Array<T>::Array(const Array<T>& other) :
		vector_(new Vector(*(other.vector_))),
		size_(other.size_)
		//kopÌrovacÌ konötruktor
		//napr. Array<int> *b = new Array<int>(*a)
		// (*a).size() == a->size() - in· syntax, rovnak˝ v˝znam
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete vector_;
		vector_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	Structure* Array<T>::clone() const
	{
		//vyvol· copy construktor prÌsluönÈho objektu
		return new Array<T>(*this);
	}

	template<typename T>
	Structure& Array<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Array<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	Array<T>& Array<T>::operator=(const Array<T>& other)
	{
		if (this != &other)
		{
			if (this->size_ != other.size_)
			{
				throw std::logic_error("Array<T>::operator=: Arrays` sizes differ!");
			}
			*this->vector_ = *other.vector_;
			//dereferenciou z tohto robÌm objekt
			//this->vector_->operator=(other.vector_);
			//toto by som pouûila ako metÛdu operator=
			//oper·tor priradenia pouûÌvam len ak s˙ obe polia rovnako veækÈ a=b
		}
		return *this;
	}

	template<typename T>
	size_t Array<T>::size() const
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Array<T>::operator[]: invalid index");
		int vectorIndex = this->mapFunction(index);
		return *reinterpret_cast<T*>(this->vector_->getBytePointer(vectorIndex));
		//musela som to eöte zdereferencovaù, na to som zabudla, lebo chcemem hodnotu toho T
		//a nie adresu
	}

	template<typename T>
	const T Array<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Array<T>::operator[]: invalid index");
		int vectorIndex = this->mapFunction(index);
		return *reinterpret_cast<T*>(this->vector_->getBytePointer(vectorIndex));

		//mÙûeme to napÌsaù aj takto, pretoûe tu vraciam kÛpiu a n·m nevadÌ ûe to 
		//priradÌme do lok·lnej premmenej, ale kvÙli r˝chlosti to tak neurobÌm
		//pri tom vrchnejöom oper·torovi[] to nemÙûeme urobiù, lebo tam vraciame origin·l
		//T res = *reinterpret_cast<T*>(this->vector_->getBytePointer(vectorIndex));
		//return res;
	}

	template<typename T>
	inline bool Array<T>::operator==(const Array<T>& other) const
	{
		return *(this->vector_) == *(other.vector_);
		//*this->vector_ aj *other.vector_ musia maù hviezdiËka, lebo je to smernÌk 
		//na Vector a chceme hodnotu a nie adresu
		//a do z·tvorky to nemusÌme davaù, ale d·me, aby sme zv˝raznili ûe sa dereferencuje
		//aû posledn˝ Ëlen... teda .vector_
		//ale nemusÌme, lebo -> m· v‰Ëöiu prioritu ako *		
		//this->size_ == other.size_ nemusÌ byù, lebo size sa porovn·vaj˙ aj vo vektoroch 
	}

	template<typename T>
	void Array<T>::copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length)
	{ 
		if (length != 0) {
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Array<T>::copy: Invalid index in Vector src.");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Array<T>::copy Invalid index in Vector dest.");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Array<T>::copy Index out of range!");
			DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Array<T>::copy Index out of range!");
			
			Vector::copy(*src.vector_, src.mapFunction(srcStartIndex), *dest.vector_, 
				dest.mapFunction(destStartIndex), length * sizeof(T));
			//preËo VECTOR???? a preËo src.vector_....???? 
		}
	}

	template<typename T>
	inline int Array<T>::mapFunction(const int index) const
	{
		//vr·ti mi na ktorom indexe vo vectore sa nach·dza ten mÙj poûadovan˝ index poæa
		return index * sizeof(T); 
	}
}

