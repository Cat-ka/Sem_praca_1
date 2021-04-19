#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany dvojzoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		void push(const int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		int peekPriority() const override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		this->clear();
		delete this->shortList_;
		delete this->longList_;
		this->shortList_ = nullptr;
		this->longList_ = nullptr;
	}

	template<typename T>
	Structure* PriorityQueueTwoLists<T>::clone() const
	{
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other)
	{
		if (this != &other)
		{
			this->clear();		
			for (PriorityQueueItem<T>* data : *other.longList_)
			{
				this->longList_->add(new PriorityQueueItem<T>(*data));
			}			
		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const
	{

		return this->longList_->size() + this->shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{

		this->shortList_->clear();

		for (PriorityQueueItem<T>* item : *this->longList_)
		{
			delete item;
		}
		this->longList_->clear();

	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T& data)
	{
		if (this->shortList_->size() < this->shortList_->getCapacity() || this->shortList_->minPriority() > priority)
		{
			PriorityQueueItem<T>* item = shortList_->pushAndRemove(priority, data);
			if (item != nullptr) {
				this->longList_->add(item);
			}
			else
			{
				//PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
				//this->longList_->add(item);
			}
		}
		else
		{
			PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
			this->longList_->add(item);
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		this->shortList_->pop();
		if (this->shortList_->size() == 0)
		{
			if (this->longList_->size() > 0)
			{
				int capacity = sqrt(this->longList_->size());
				if (capacity < 4)
				{
					capacity = 4;
				}

				this->shortList_->trySetCapacity(capacity);
				LinkedList<PriorityQueueItem<T>*>* temp = new LinkedList<PriorityQueueItem<T>*>();

				for (PriorityQueueItem<T>* item : *this->longList_)
				{
					PriorityQueueItem<T>* removed = this->shortList_->pushAndRemove(item->getPriority(), item->accessData());
					if (removed != nullptr) {
						temp->add(removed);
					}
					delete item;
				}

				this->longList_->clear();
				delete this->longList_;
				this->longList_ = temp;
			}
			//return PriorityQueueItem<T>::pop();
			return 0;
		}

	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek();
	}

	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const
	{
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const
	{
		if (this->shortList_->size() < 1)
		{
			throw std::logic_error("PriorityQueueSortedArrayList<T>::indexOfPeek() : Priority queue is empty.");
		}
		else
		{
			return shortList_->peekPriority();
		}
	}
}

