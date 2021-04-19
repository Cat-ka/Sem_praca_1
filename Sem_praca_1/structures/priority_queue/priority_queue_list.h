#pragma once

#include "priority_queue.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Spolocny predok pre vsetky prioritne fronty, ktorych implementujucim typom je zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueList : public PriorityQueue<T>
	{
	public:
		/// <summary> Destruktor. </summary>
		~PriorityQueueList();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia pre prioritny front implementovany zoznamom. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom zoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom zoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho zoznamom. </summary>
		void clear() override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho zoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		int peekPriority() const override;

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky prioritneho frontu. </param>
		/// <remarks> 
		/// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu. 
		/// Prioritny front implementovany zoznamom dealokuje tento objekt.
		/// </remarks>
		PriorityQueueList(List<PriorityQueueItem<T>*>* list);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueList(const PriorityQueueList<T>& other);

		/// <summary> Vrati index v zozname, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>  
		virtual int indexOfPeek() const;

	protected:
		/// <summary> Smernik na zoznam, do ktoreho sa ukladaju prvky prioritneho frontu. </summary>
		List<PriorityQueueItem<T>*>* list_;
	};

	template<typename T>
	inline PriorityQueueList<T>::PriorityQueueList(List<PriorityQueueItem<T>*>* list) :
		PriorityQueue<T>(),
		list_(list)
	{
	}

	template<typename T>
	inline PriorityQueueList<T>::PriorityQueueList(const PriorityQueueList<T>& other) :
		PriorityQueueList<T>(dynamic_cast<List<PriorityQueueItem<T>*>*>(other.list_->clone()))
	{
		list_->clear();
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename T>
	inline PriorityQueueList<T>::~PriorityQueueList()
	{
		this->clear();
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename T>
	inline PriorityQueue<T>& PriorityQueueList<T>::operator=(const PriorityQueue<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const PriorityQueueList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline PriorityQueueList<T>& PriorityQueueList<T>::operator=(const PriorityQueueList<T>& other)
	{
		if (this != &other)
		{
			this->clear();
			for (PriorityQueueItem<T>* item : *other.list_)
			{
				this->list_->add(new PriorityQueueItem<T>(*item));
			}
		}
		return *this;
	}

	template<typename T>
	inline size_t PriorityQueueList<T>::size() const
	{
		return list_->size();
	}

	template<typename T>
	inline void PriorityQueueList<T>::clear()
	{
		//ked�e neviem �i mi do cyklu for each vstupuje ArrayList alebo LinkedList, mus�m pou�i� for each cyklus
		//ktor� m� v oboch pr�padoch garantovan� n-kov� zlo�itos�
		for (PriorityQueueItem<T>* item : *this->list_)
		{
			delete item;
		}
		this->list_->clear();
	}

	template<typename T>
	inline int PriorityQueueList<T>::indexOfPeek() const
	{
		//tu si dam do maxPriority bud prioritu �o ma prv� prvok, alebo dam nejak� vysoku.
		//standardne sme d�vali max Integer
		//index si d�m na 0
		//urobili sme to tak, �e sme dali prioritu prvku 0 a ak n�jde prvok s vy��ou prioritou tak to zmen�, ak nie, tak prvok na indexe 0 
		//m� najvy��iiu prioritu a vr�ti index 0
		if (this->list_->size() < 1)
		{
			throw std::logic_error("PriorityQueueList<T>::indexOfPeek() : Priority queue is empty.");
		}
		else {
			int maxPriority = (*this->list_)[0]->getPriority();
			int indexOfMaxPriority = 0;
			int i = 0;
			for (PriorityQueueItem<T>* item : *this->list_)
			{
				if (item->getPriority() < maxPriority)
				{
					maxPriority = item->getPriority();
					indexOfMaxPriority = i;
				}
				i++;
			}
			return indexOfMaxPriority;
		}
	}

	template<typename T>
	inline T PriorityQueueList<T>::pop()
	{
		//popujem prvok na indexe peeku
		int index = this->indexOfPeek();
		//do vytvoren�ho itemu vlo��m mazan� prvok, potom spr�stupn�m data na �om a a idem rovno vyma�em kv�li memory leakom
		PriorityQueueItem<T>* item = this->list_->removeAt(index);
		T data = item->accessData();
		delete item;
		//a vr�tim data, do ktor�ch som si ulo�ila d�ta
		return data;
	}

	template<typename T>
	inline T& PriorityQueueList<T>::peek()
	{
		int index = this->indexOfPeek();
		return (*this->list_)[index]->accessData();
	}

	template<typename T>
	inline const T PriorityQueueList<T>::peek() const
	{
		int index = this->indexOfPeek();
		return (*this->list_)[index]->accessData();
	}

	template<typename T>
	inline int PriorityQueueList<T>::peekPriority() const
	{
		//t�to funkcia mi vr�ti t� maxim�lnu prioritu, ktor� tam m�m ulo�en�
		//to najmen�ie ��slo priority
		//to viem �e je na tom indexOfPeek, tak to pou�ijem
		int temp = this->indexOfPeek();
		return (*this->list_)[temp]->getPriority();
	}
}