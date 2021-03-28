#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../array/array.h"
#include <iostream>

namespace structures
{
	//override - s˙ prekrytÈ a nie je tam =0 takûe nemÙûu byù abstraktnÈ

	/// <summary> Zoznam implementovany polom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> ArrayList, z ktoreho sa prevezmu vlastnosti. </param>
		ArrayList(const ArrayList<T>& other);

		/// <summary> Destruktor. </summary>
		~ArrayList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		ArrayList<T>& operator=(const ArrayList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
	private:
		/// <summary> Rozsiri kapacitu zoznamu. </summary>
		void enlarge();

		/// <summary> Iterator pre ArrayList. </summary>
		class ArrayListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "arrayList"> Zoznam, cez ktory iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			ArrayListIterator(const ArrayList<T>* arrayList, int position);

			/// <summary> Destruktor. </summary>
			~ArrayListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Zoznam, cez ktory iteruje. </summary>
			const ArrayList<T>* arrayList_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList() :
		List(),
		array_(new Array<T>(4)),
		size_(0)
		//size_ nastavÌm na 0, lebo je pr·zdny
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(const ArrayList<T>& other) :
		List(),
		array_(new Array<T>(*other.array_)),
		size_(other.size_)
	{
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList()
	{
		delete this->array_;
		this->size_ = 0;
		this->array_ = nullptr;
	}

	template<typename T>
	inline Structure* ArrayList<T>::clone() const
	{
		return new ArrayList<T>(*this);
	}

	template<typename T>
	inline size_t ArrayList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& ArrayList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ArrayList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
	{
		if (this != &other)
		{
			if (this->array_->size() != other.array_->size()) {
				delete this->array_;
				this->array_ = new Array<T>(*other.array_);
			}
			else {
				*this->array_ = *other.array_;
				//ak s˙ polia rovnako veækÈ tak mÙûem pouûiù oper·rot priradenia nad array 
				//a musÌm ho zdereferencovaù ho aby sme dostali objekty
				//robÌm to preto, lebo oper·cie delete a new s˙ Ëasovo n·roËnÈ
				//a chcem sa im vyhn˙ù ak sa mi d·
			}
			this->size_ = other.size_;
		}
		return *this;
	}

	template<typename T>
	inline T& ArrayList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "T& ArrayList<T>::operator[]: invalid index.");
		//vraciam origin·l a zase musÌm dereferencovaù, aby som dostala objekt, lebo array_ je pointer
		//pomocou tohto vieme zapisovaù a aj ËÌtaù
		return (*this->array_)[index];
	}

	template<typename T>
	inline const T ArrayList<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "T ArrayList<T>::operator[]: invalid index.");
		//tu nie je referencia &, preto vraciam kÛpiu
		//pomocou tohto vieme len ËÌtaù
		return (*this->array_)[index];
		//ale je to presne ten ist˝ z·pis
	}

	template<typename T>
	inline void ArrayList<T>::add(const T& data)
	{
		//zavol·me najskÙr funkciu enlarge(), aby n·m prekontrolovalo, Ëi m·me v array miesto 
		//na vloûenie prvku, ak nie, rovno n·m vytvorÌ novÈ pole s viac miestom

		this->enlarge();

		//t˝m ûe tam d·me *, urobÌme zo smernÌka array_ objekt dereferenciou a mÙûeme pouûiù
		//oper·tor[]
		(*this->array_)[static_cast<int>(this->size_)] = data;
		this->size_++;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T& data, const int index)
	{
		if (index == this->size_) {
			add(data);
		}
		else {
			DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::insert: invalid index.");
			if (this->size_ == this->array_->size()) {
				this->enlarge();
			}
			Array<T>::copy(*this->array_, index, *this->array_, index + 1, static_cast<int>(this->size_) - index);
			(*this->array_)[index] = data;
			this->size_ = this->size_ + 1;
		}
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T& data)
	{
		int temp = this->getIndexOf(data);
		if (temp > -1) {
			this->removeAt(temp);
			return true;
		}
		else {
			return false;
		}
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(const int index)
	{
		if (this->size_ != 0) {
			//DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::removeAt: invalid index.");
			T removed = (*this->array_)[index];
			Array<T>::copy(*this->array_, index + 1, *this->array_, index, static_cast<int>(this->size_) - index - 1);
			this->size_ = this->size_ - 1;
			return removed;
		}
		else {			
			//std::cout << "The list is empty. Nothing to delete." << std::endl;
		}
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T& data)
	{
		for (int i = 0; i < this->size_; i++)
		{
			if ((*this->array_)[i] == data) {
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear()
	{
		this->size_ = 0;

	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator() const
	{
		return new ArrayListIterator(this, 0);
		//tuto metodu potrebujeme aby sme mohli arraylist prech·dzaù pomocou for each cyklu
		//preto potrebujeme zaËiatoËn˝ a koneËn˝ iterator
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator() const
	{
		return new ArrayListIterator(this, static_cast<int>(this->size_));
		//tu je size_, aby ukazoval na prv˙ neplatn˙ adresu 
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		//this->size_ = toto je aktu·la veækosù zoznamu, koæko som tam vloûil poloûiek
		//this->array_->size_ = kapacita zoznamu, koæko max. poloûiek tam mÙûem 
		//vloûiù do toho zoznamu
		if (this->size_ >= this->array_->size()) {
			Array<T>* tmp = new Array<T>(this->size_ > 0 ? 2 * this->size_ : 10);
			//do smernÌka na Array tmp sme vytvorili novÈ pole
			//smernÌk je tam preto, lebo chceme aby pole existovalo aj po skonËenÌ funkcie
			//preto cez smernÌk ho uklad·me na haldu, nie na z·sobnÌk
			//tern·rny oper·tor, ûe ak je veækosù poæa 0, tak ho nastavÌme na 10 

			//funkcia copy je statick·, preto ju vyvol·vam nad triedovu
			//prekopÌruje n·m aktu·lny array do nami novo vytvorenÈho
			Array<T>::copy(*this->array_, 0, *tmp, 0, static_cast<int>(this->size_));
			delete this->array_;
			this->array_ = tmp;
			//smernik sme presmerovali na novÈ pole 
		}
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(const ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator()
	{
		this->arrayList_ = nullptr;
		this->position_ = 0;
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(const Iterator<T>& other)
	{
		if (this != &other) {
			const ArrayListIterator& it = dynamic_cast<const ArrayListIterator&>(other);
			this->arrayList_ = it.arrayList_;
			this->position_ = it.position_;
		}
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(const Iterator<T>& other)
	{
		const ArrayListIterator& it = dynamic_cast<const ArrayListIterator&>(other);
		//const ArrayListIterator& - toto nevznikla ako nov· premenn·
		//tu sme prv˝ raz pouûili & pre lok·lnu premenn˙, doteraz sme ju pouûÌvali pri parametroch alebo pri n·vratov˝ch hodnot·ch
		//keÔ ho pouûijem pri lok·lnej premennej, tak t˝m hovorÌm ûe nevytv·ram nov˙ lok·lnu premenn˙, v pam‰ti sa mi nealokuje novÈ 
		//miesto, ale len vytv·ram alias
		//teda ten other sa bude volat aj ako it
		//keby som tam nedala ten & tak vtedy vytv·rame nov˙ lok·lnu premenn˙ a do nej sa skopÌruje obsah toho dynamic_castu
		//bolo by to Ëasovo n·roËnejöie
		//it a other s˙ moment·lne identickÈ veci a ak nieËo zmenÌm v it, tak sa to zmenÌ aj v other

		return this->arrayList_ != it.arrayList_ || this->position_ != it.position_;

		//return 
		//	this->arrayList_ != dynamic_cast<ArrayList<T>::ArrayListIterator>(other->arrayList_) ||
		//	this->position_ != dynamic_cast<ArrayList<T>::ArrayListIterator>(other->position_);
	}

	template<typename T>
	inline const T ArrayList<T>::ArrayListIterator::operator*()
	{
		//vracia poloûku na ktor˙ ten iterator ukazuje
		//navratov˝ typ je T
		return (*this->arrayList_)[this->position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++()
	{
		++this->position_;
		return *this;
		//vraciam seba pretoûe modifikujem samÈho seba
		//vraciam cez * pretoûe this je pointer, ale ja potrebujem objekt a viem to, pretoûe tam nie je ûiadna hviezdiËka

		//je to prefixov˝ oper·tor ++this->position_; - lebo operator++()
		//keby to bol postfixov˝ oper·tor this->position_++; - bolo by to operator++(int)
		//ten parameter int je tam len preto, aby sa rozliöovalo Ëi je to prefixov˝ alebo postfixov˝ oper·tor
		//to int je nejak˝ dummy parameter
		//je to len syntex c++
		// zase musÌme daù *this, lebo this je pointer a ja potrebujem objekt a nem· v hlaviËke ûiadnu hviezdiËku
	}
}