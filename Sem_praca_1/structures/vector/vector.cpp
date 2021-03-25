#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>
#include <math.h>

namespace structures {

	Vector::Vector(size_t size) :
		//inicializuje mi to a je to r˝chlejöie ako v tele
		//alokuje mi pam‰ù cez calloc a size_ nastavÌ na size		
		memory_(calloc(size, 1)),
		size_(size)
	{
		//Kvaööay cviËenie
		//this->memory_ = malloc(size);
		//this->size_ = size;
		//toto je ekvivalent tomu Ëo je hore
		//ten inicializaËn˝ zoznam sa pouûÌva Ëastejöie lebo oddeæuje inicializaËn˙ logiku 
		//od funkËnej logiky, ktor· by bola v z·tovrk·ch a je to r˝chlejöie 
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		//pomocou memcpy nakopÌrujte pam‰ù z 2. vektora
		//mÙûeme pouûiù memcpy, lebo v tomto prÌpade to kopÌrujeme  na koniec, pam‰te sa neprekryj˙
		memcpy(memory_, other.memory_, size_);
		// kopÌrujem other do mojej memory
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
			//dynamic_cast<na Ëo to chcem pretypovaù>(Ëo chcem pretypovaù)
			// viac verziÌ jednÈho prÌkazu
			//this->operator=(dynamic_cast<const Vector&>(other));
			//(*this).operator=(dynamic_cast<const Vector&>(other));
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			//budem meniù seba. teda ten this
			//zmenÌme veækosù objektu this na veækosù other 
			size_ = other.size_;
			//naalokujeme pam‰ù, namiesto free a novÈ naalokovanie pam‰te zavol·me realloc
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
		// 3) C = rovnaka pam‰ù: memcpy(memory_, other.memory_, size_) == 0

		// return (A) alebo (B a C)

		return this == &other || (size_ == other.size_ && memcpy(memory_, other.memory_, size_) == 0);
	}

	byte& Vector::operator[](const int index)
	{
		// 1) pretypuj memory_ na byte* (ptrB)
		// 2) posun ptrB o index
		// 3) vrat *ptrB

		//dynamic_cast<na Ëo to chcem pretypovaù>(Ëo chcem pretypovaù)
		DSRoutines::rangeCheckExcept(index, size_, "Vector::operator[]: invalid index.");
		return *(reinterpret_cast<byte*>(memory_) + index);

		//return reinterpret_cast<byte*>(memory_)[index];
		// tu sme nedali t˙ hviezdiËku... preËo???

		//Kvassay cviËenie
		//DSRoutines::rangeCheckExcept(index, this->size_, "Vector::operator[]: invalid index.");
		// return *this->getBytePointer(index);

		//tu vraciame origin·l objektu, lebo ho vraciame referenciou
		// ak by to bolo byte* Vector tak by sme vracali adresu objektu
		//tento oper·tor potrebujem keÔ chcem hlavne zapisovaù, Ëiûe keÔ m·m [] nalavo od oper·tora priradenia
		//napr. Vector V
		//V[3] = 10;
		//ale d· sa pouûiù aj keÔ chcem ËÌtaù, ale pouûÌva sa hlavne pri zapisovanÌ

	}

	byte Vector::operator[](const int index) const
	{
		//toto je oproti tej predch·dzaj˙cej metÛde in·,  
		DSRoutines::rangeCheckExcept(index, size_, " Vector::operator[]: Invalid index!");
		return *(reinterpret_cast<byte*>(memory_) + index);
		//tu vraciam kÛpiu
		//tento oper·tor priradenia pouûÌvam, len keÔ chcem ËÌtaù, Ëiûe keÔ m·m [] napravo
		//napr. byte b = V[5];

		//Kvaööay cviËenie
		//DSRoutines::rangeCheckExcept(index, this->size_, "Vector::operator[]: invalid index.");
		//return *this->getBytePointer(index);


	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		//sl˙ûi na to, ûe z vektora this prekopÌruje bajty, zaËÌnaj˙ce na indexe, v poËte count a prekopÌrujeme ju 
		//do adresy dest, mimo mÙj terajöÌ vektor 
		//byte& dest - znamen· ûe tam posielam origin·l a nie kopiu destu
		//ak by sme posielali adresu, tak namiesto & by tam bola *
		//metÛda skopÌruje nejakÈ bajty do nejakej pam‰te, kde s nimi budem chcieù neskÙr pracovaù
		//keby posielam kopiu (ûe neposlem cez & ale cez *) tak sa mi v pam‰ti vytvorÌ lok·lna kÛpia, 
		// a ten blok pam‰te 
		//po skonËenÌ funkcie prestane existovaù

		if (count > 0)
		{
			//DSRoutines::rangeCheckExcept(index, size_, "Vector::readBytes: Invalid index!");
			//toto nemusÌm, lebo toto m·m oöetrenÈ cez getBytePoiner
			DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Vector::readBytes: Invalid count!");
			//d·vam tam - 1, lebo potrebujem kontrolovaù posledn˝ bajt, ktor˝ kontrolujem a index + count mi d· index, 
			//ktor˝ uû nebudem kopÌrovaù
			//prÌpadne mÙûem daù in˙ variantu a to, size_ + 1 => toto je bezpeËnejöie, pretoûe ak by bol index aj count 0, 
			//tak by som dostala -1
			//vieme to oöetriù t˝m, ûe sa op˝tame Ëi count > 0 (dala som to do ifu)
			memcpy(&dest, this->getBytePointer(index), count);
			return dest;
		}
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		//keÔ kopÌrujem v r·mci svojho vektoru
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
		
		//v tejto funkcii poölem ako parameter niektor˝ bajt z vektoru a t·to funkcia mi vr·ti adresu
		//na ktorej sa ten mÙj poûadovan˝ bajt nach·dza
		//zÌskam adresu poûadovanÈho bajtu tak ûe pripoËÌtam index k zaËiatku mojej memory ktor· ukazuje 
		//na zaËiatok mÙjho vektoru 
		//reinterpret cast pouûÌvam ked pretypov·vam pointre, ako v tomto prÌpade void
		//DSRoutines mi kontroluje Ëi mÙj index je v rozmedzÌ 0 aû size, (malo by tam byù size-1, ale t·to metÛda
		//je uû nastaven· tak, ûe mi t˙ -1 berie sama
	}
}