#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>
#include <math.h>

namespace structures {

	Vector::Vector(size_t size) :
		//inicializuje mi to a je to r�chlej�ie ako v tele
		//alokuje mi pam� cez calloc a size_ nastav� na size		
		memory_(calloc(size, 1)),
		size_(size)
	{
		//Kva��ay cvi�enie
		//this->memory_ = malloc(size);
		//this->size_ = size;
		//toto je ekvivalent tomu �o je hore
		//ten inicializa�n� zoznam sa pou��va �astej�ie lebo odde�uje inicializa�n� logiku 
		//od funk�nej logiky, ktor� by bola v z�tovrk�ch a je to r�chlej�ie 
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		//pomocou memcpy nakop�rujte pam� z 2. vektora
		//m��eme pou�i� memcpy, lebo v tomto pr�pade to kop�rujeme  na koniec, pam�te sa neprekryj�
		memcpy(memory_, other.memory_, size_);
		// kop�rujem other do mojej memory
	}

	Vector::Vector(Vector&& other) :
		memory_(other.memory_),
		size_(other.size_)
	{
		other.memory_ = nullptr;
		other.size_ = 0;
	}

	Vector::~Vector()
	{
		free(memory_);
		size_ = 0;
		memory_ = nullptr;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure& Vector::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
			//dynamic_cast<na �o to chcem pretypova�>(�o chcem pretypova�)
			// viac verzi� jedn�ho pr�kazu
			//this->operator=(dynamic_cast<const Vector&>(other));
			//(*this).operator=(dynamic_cast<const Vector&>(other));
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			//budem meni� seba. teda ten this
			//zmen�me ve�kos� objektu this na ve�kos� other 
			size_ = other.size_;
			//naalokujeme pam�, namiesto free a nov� naalokovanie pam�te zavol�me realloc
			memory_ = realloc(memory_, other.size_);
			memcpy(memory_, other.memory_, size_);
		}
		return *this;
	}

	Vector& Vector::operator=(Vector&& other)
	{
		if (this != &other) {
			size_ = other.size_;
			free(memory_);
			memory_ = other.memory_;

			other.size_ = 0;
			other.memory_ = nullptr;
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		// 1) A = identita: this == &other
		// 2) B = rovnake velkosti: size_ == other.size_
		// 3) C = rovnaka pam�: memcpy(memory_, other.memory_, size_) == 0

		// return (A) alebo (B a C)

		return this == &other || (size_ == other.size_ && memcpy(memory_, other.memory_, size_) == 0);
	}

	byte& Vector::operator[](const int index)
	{
		// 1) pretypuj memory_ na byte* (ptrB)
		// 2) posun ptrB o index
		// 3) vrat *ptrB

		//dynamic_cast<na �o to chcem pretypova�>(�o chcem pretypova�)
		DSRoutines::rangeCheckExcept(index, size_, "Vector::operator[]: invalid index.");
		return *(reinterpret_cast<byte*>(memory_) + index);

		//return reinterpret_cast<byte*>(memory_)[index];
		// tu sme nedali t� hviezdi�ku... pre�o???

		//Kvassay cvi�enie
		//DSRoutines::rangeCheckExcept(index, this->size_, "Vector::operator[]: invalid index.");
		// return *this->getBytePointer(index);

		//tu vraciame origin�l objektu, lebo ho vraciame referenciou
		// ak by to bolo byte* Vector tak by sme vracali adresu objektu
		//tento oper�tor potrebujem ke� chcem hlavne zapisova�, �i�e ke� m�m [] nalavo od oper�tora priradenia
		//napr. Vector V
		//V[3] = 10;
		//ale d� sa pou�i� aj ke� chcem ��ta�, ale pou��va sa hlavne pri zapisovan�

	}

	byte Vector::operator[](const int index) const
	{
		//toto je oproti tej predch�dzaj�cej met�de in�,  
		DSRoutines::rangeCheckExcept(index, size_, " Vector::operator[]: Invalid index!");
		return *(reinterpret_cast<byte*>(memory_) + index);
		//tu vraciam k�piu
		//tento oper�tor priradenia pou��vam, len ke� chcem ��ta�, �i�e ke� m�m [] napravo
		//napr. byte b = V[5];

		//Kva��ay cvi�enie
		//DSRoutines::rangeCheckExcept(index, this->size_, "Vector::operator[]: invalid index.");
		//return *this->getBytePointer(index);


	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		//sl��i na to, �e z vektora this prekop�ruje bajty, za��naj�ce na indexe, v po�te count a prekop�rujeme ju 
		//do adresy dest, mimo m�j teraj�� vektor 
		//byte& dest - znamen� �e tam posielam origin�l a nie kopiu destu
		//ak by sme posielali adresu, tak namiesto & by tam bola *
		//met�da skop�ruje nejak� bajty do nejakej pam�te, kde s nimi budem chcie� nesk�r pracova�
		//keby posielam kopiu (�e neposlem cez & ale cez *) tak sa mi v pam�ti vytvor� lok�lna k�pia, 
		// a ten blok pam�te 
		//po skon�en� funkcie prestane existova�

		if (count > 0)
		{
			//DSRoutines::rangeCheckExcept(index, size_, "Vector::readBytes: Invalid index!");
			//toto nemus�m, lebo toto m�m o�etren� cez getBytePoiner
			DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Vector::readBytes: Invalid count!");
			//d�vam tam - 1, lebo potrebujem kontrolova� posledn� bajt, ktor� kontrolujem a index + count mi d� index, 
			//ktor� u� nebudem kop�rova�
			//pr�padne m��em da� in� variantu a to, size_ + 1 => toto je bezpe�nej�ie, preto�e ak by bol index aj count 0, 
			//tak by som dostala -1
			//vieme to o�etri� t�m, �e sa op�tame �i count > 0 (dala som to do ifu)
			memcpy(&dest, this->getBytePointer(index), count);
			return dest;
		}
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		//ke� kop�rujem v r�mci svojho vektoru
		if (length != 0) {
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Vector::copy: Invalid index in Vector src.");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Vector::copy: Invalid index in Vector dest.");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Vector::copy: Index out of range!");
			DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Vector::copy: Index out of range!");
			if (&src == &dest && abs(srcStartIndex - destStartIndex) < length) {
				memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
			else {
				memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
		}

	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Vector::getBytePointer: invalid index.");
		return reinterpret_cast<byte*>(memory_) + index;
		//return &reinterpret_cast<byte*>(memory_)[index];
		
		//v tejto funkcii po�lem ako parameter niektor� bajt z vektoru a t�to funkcia mi vr�ti adresu
		//na ktorej sa ten m�j po�adovan� bajt nach�dza
		//z�skam adresu po�adovan�ho bajtu tak �e pripo��tam index k za�iatku mojej memory ktor� ukazuje 
		//na za�iatok m�jho vektoru 
		//reinterpret cast pou��vam ked pretypov�vam pointre, ako v tomto pr�pade void
		//DSRoutines mi kontroluje �i m�j index je v rozmedz� 0 a� size, (malo by tam by� size-1, ale t�to met�da
		//je u� nastaven� tak, �e mi t� -1 berie sama
	}
}