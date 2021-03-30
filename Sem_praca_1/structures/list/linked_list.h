#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"


namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class LinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		LinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		LinkedListItem(const LinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~LinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		LinkedListItem<T>* getNext();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name¥= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(LinkedListItem<T>* next);

	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		LinkedListItem<T>* next_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class LinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		LinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		LinkedList(const LinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~LinkedList();

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
		LinkedList<T>& operator=(const LinkedList<T>& other);

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
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		LinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		LinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		LinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class LinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			LinkedListIterator(LinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~LinkedListIterator();

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
			/// <summary> Aktualna pozicia v zozname. </summary>
			LinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr)
	{
	}

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(const LinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_)
	{
	}

	template<typename T>
	inline LinkedListItem<T>::~LinkedListItem()
	{
		next_ = nullptr;
	}

	template<typename T>
	inline LinkedListItem<T>* LinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline void LinkedListItem<T>::setNext(LinkedListItem<T>* next)
	{
		next_ = next;
	}
	
	template<typename T>
	inline LinkedList<T>::LinkedList() :
		List(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(const LinkedList<T>& other) :
		LinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		this->clear();
	}

	template<typename T>
	inline Structure* LinkedList<T>::clone() const
	{
		return new LinkedList<T>(*this);
	}

	template<typename T>
	inline size_t LinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& LinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const LinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
	{
		if (this != &other)
		{
			this->clear();
			//cyklus for each vyuûÌva iter·tor preto m· zloûitosù O(n)
			for (T data : other) {
				this->add(data);
			}
		}
		return *this;
	}

	template<typename T>
	inline T& LinkedList<T>::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "LinkedList<T>::operator[]: invalid index.");
		LinkedListItem<T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline const T LinkedList<T>::operator[](const int index) const
		//const metÛda musÌ volaù len const metÛdy
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "LinkedList<T>::operator[]: invalid index.");
		LinkedListItem<T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline void LinkedList<T>::add(const T& data)
	{
		LinkedListItem<T>* newItem = new LinkedListItem<T>(data);
		if (this->size_ == 0) {
			this->first_ = newItem;
			this->last_ = newItem;
		}
		else {
			this->last_->setNext(newItem);
			this->last_ = newItem;
			//najskÙr musÌm urobiù, aby posledn˝ ukazoval na ten nov˝ a potom z ten posledn˝ zmenÌm, aby sa nÌm stal ten nov˝ 
		}
		this->size_++;
	}

	template<typename T>
	inline void LinkedList<T>::insert(const T& data, const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_ + 1, "LinkedList<T>::insert: invalid index.");
		//ak vklad·m na koniec, ale je zoznam pr·zdny
		if (index == this->size_) {
			this->add(data);
		}
		else {
			//utËite nevklad·m na koniec a urËite nie je zoznam pr·zdny
			//uû m·m nastavenÈ first a lasta uû ju len modifikujem
			LinkedListItem<T>* newItem = new LinkedListItem<T>(data);
			if (index == 0) {
				newItem->setNext(this->first_);
				this->first_ = newItem;
			}
			else {
				LinkedListItem<T>* prev = this->getItemAtIndex(index - 1);
				newItem->setNext(prev->getNext());
				prev->setNext(newItem);
			}
			this->size_++;
		}
	}

	template<typename T>
	inline bool LinkedList<T>::tryRemove(const T& data)
	{
		//TODO 04: LinkedList
		//zavolame metodu getindexof
		//potom zavolame metodu remove at
		//na domacu ulohu 
		throw std::exception("LinkedList<T>::tryRemove: Not implemented yet.");
	}

	template<typename T>
	inline T LinkedList<T>::removeAt(const int index)
	{
		if (this->size_ != 0) {
			DSRoutines::rangeCheckExcept(index, this->size_, "LinkedList<T>::removeAt: invalid index.");
			LinkedListItem<T>* remove = nullptr;

			//odober·m z prvej pozÌcie prvok
			if (index == 0) {
				remove = this->first_;
				LinkedListItem<T>* next = remove->getNext();
				this->first_ = next;
				//ak odober·m jedin˝ prvok, ktor˝ sa v liste nach·dza
				if (this->size_ == 1) {
					this->last_ = nullptr;
				}
			}
			//odober·m z konca		
			else {

				LinkedListItem<T>* prev = this->getItemAtIndex(index - 1);
				remove = prev->getNext();
				prev->setNext(remove->getNext());
				if (index == this->size_ - 1) {
					this->last_ = prev;
				}
			}
			T data = remove->accessData();
			this->size_--;
			delete remove;
			return data;
		}
		else {
			//std::cout << "The list is empty. Nothing to delete." << std::endl;
		}
	}

	template<typename T>
	inline int LinkedList<T>::getIndexOf(const T& data)
	{
		LinkedListItem<T>* result = this->first_;
		int index = 0;

		//nepouûÌvam cyklus for, pretoûe for prebehne celÈ, ale viem to vyrieöiù breakom
		//kombin·cia cyklu (On) a hranat˝ch z·tvoriek (On) mi d·va zloûitosù (On^2), preto sa 
		//tomu chceme vyhn˙ù

		while (result != nullptr) {
			if (result->accessData() == data) {
				return index;
			}
			index++;
			result = result->getNext();
		}
		return -1;
	}

	template<typename T>
	inline void LinkedList<T>::clear()
	{
		LinkedListItem<T>* curr = this->first_;
		while (curr != nullptr) {
			curr = curr->getNext();
			delete this->first_;
			this->first_ = curr;
		}
		this->size_ = 0;
		this->last_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getBeginIterator() const
	{
		return new LinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getEndIterator() const
	{
		return new LinkedListIterator(nullptr);
	}

	template<typename T>
	inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "LinkedList<T>::getItemAtIndex: invalid index.");

		LinkedListItem<T>* result = this->first_;
		for (int i = 0; i < index; i++)
		{
			result = result->getNext();
		}
		return result;
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T>* position) :
		position_(position)
	{
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
	{
		this->position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(const Iterator<T>& other)
	{
		if (this != &other) {
			this->position_ = dynamic_cast<const LinkedListIterator&>(other).position_;

			//parameter other je iterator a potrebujem LinkedListIterator a preto musÌm pretypov
		}
		return *this;
	}

	template<typename T>
	inline bool LinkedList<T>::LinkedListIterator::operator!=(const Iterator<T>& other)
	{
		return this->position_ != dynamic_cast<const LinkedListIterator&>(other).position_;

		//parameter other je iterator a potrebujem LinkedListIterator a preto musÌm pretypovaù - pouûijem 
		//dynamic_cast, kde ho pretypujem na <const LinkedListIterator&>, aby som z neho dostal potomka
		//a sprÌstupnÌm position
	}

	template<typename T>
	inline const T LinkedList<T>::LinkedListIterator::operator*()
	{
		//toto nie je n·sobenie
		//toto je sprÌstupnenie d·t, na ktorÈ iter·tor ukazuje
		T data = this->position_->accessData();
		return data;
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
	{
		this->position_ = this->position_->getNext();
		return *this;
		//musÌm vr·tiù ten objekt iter·tor ktor˝ som modifikoval a to je ten objekt this
	}
	
}