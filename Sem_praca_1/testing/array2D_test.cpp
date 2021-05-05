#include "array2D_test.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;
using namespace std::chrono;


Array2D_test::Array2D_test()
{
}

Array2D_test::~Array2D_test()
{
	delete this->array2D_;
	this->array2D_ = nullptr;
	delete this->testujem;
	this->testujem = nullptr;
}

void Array2D_test::nasobenie(Array2D<int>& first, Array2D<int>& second, Array2D<int>& result)
{
	for (int i = 0; i < first.getNumberOfRows(); i++)
	{
		for (int j = 0; j < second.getNumberOfColumns(); j++)
		{
			int temp = 0;
			for (int k = 0; k < first.getNumberOfColumns(); k++)
			{
				temp += first.get(i, k) * second.get(k, j);
			}
			result.set(i, j, temp);
		}
	}

}

void Array2D_test::scitanie(Array2D<int>& first, Array2D<int>& second, Array2D<int>& result)
{
	for (int i = 0; i < first.getNumberOfRows(); i++)
	{
		for (int j = 0; j < first.getNumberOfColumns(); j++)
		{
			int number1 = first.get(i, j);
			int number2 = second.get(i, j);
			int resultNumber = number1 + number2;
			result.set(i, j, resultNumber);
		}
	}

}





void Array2D_test::runTesting(int adt, char scenario)
{
	string name;
	name.append(1, scenario);
	if (adt == 4) {
		if (scenario == 'A') {
			cout << "Chystas sa testovat suvislu maticu. \n" << endl;
			cout << "Scitanie matic \n" << endl;
			fileName = name + "_Array2D_contiguous_add.txt";
			for (m = 100; m <= 2000; m = m + 100)
			{
				cout << "------->>>> m:  " << m << "<<<<-------" << endl;
				for (n = 100; n <= 2000; n = n + 100)
				{
					Array2D<int>* prva = new Array2Dcontiguous<int>(n, m, 1);
					Array2D<int>* druha = new Array2Dcontiguous<int>(n, m, 1);
					Array2D<int>* vysledna = new Array2Dcontiguous<int>(n, m, 0);

					start = high_resolution_clock::now();
					//cout << "zaciatok  " << endl;
					this->scitanie(*prva, *druha, *vysledna);
					//cout << "koniec  " << endl;
					stop = high_resolution_clock::now();
					duration = duration_cast<microseconds>(stop - start);
					cout << "n:  " << n << " T: " << duration.count() << " microseconds, S: " << n * m << endl;
					this->zapis(this->fileName, n, duration.count(), n * m);
					delete prva;
					delete druha;
					delete vysledna;
					prva = nullptr;
					druha = nullptr;
					vysledna = nullptr;
				}
			}
		}
		else
		{
			cout << "Chystas sa testovat suvislu maticu. \n" << endl;
			cout << "Nasobenie matic. \n" << endl;
			fileName = name + "_Array2D_contiguous_multipli.txt";
			for (n = 100; n <= 2000; n = n + 100)
			{
				//cout << "------->>>> n:  " << n << "<<<<-------" << endl;
				//for (m = 100; m <= 2000; m = m + 100)
				//{
					Array2D<int>* prva = new Array2Dcontiguous<int>(n, n, 1);
					Array2D<int>* druha = new Array2Dcontiguous<int>(n, n, 1);
					Array2D<int>* vysledna = new Array2Dcontiguous<int>(n, n, 0);

					start = high_resolution_clock::now();
					//cout << "zaciatok  " << endl;
					this->nasobenie(*prva, *druha, *vysledna);
					//cout << "koniec  " << endl;
					stop = high_resolution_clock::now();
					duration = duration_cast<microseconds>(stop - start);
					cout << "n:  " << n << " T: " << duration.count() << " microseconds, S: " << n * m << endl;
					this->zapis(this->fileName, n, duration.count(), n * m);
					delete prva;
					delete druha;
					delete vysledna;
					prva = nullptr;
					druha = nullptr;
					vysledna = nullptr;
				//}
			}

		}
	}
	else
	{
		if (scenario == 'A') {
			cout << "Chystas sa testovat nesuvislu maticu. \n" << endl;
			cout << "Scitanie matic \n" << endl;
			fileName = name + "_Array2D_noncontiguous_add.txt";
			for (m = 1800; m <= 2000; m = m + 100)
			{
				cout << "------->>>> m:  " << m << "<<<<-------" << endl;
				for (n = 100; n <= 2000; n = n + 100)
				{
					Array2D<int>* prva = new Array2Dnoncontiguous<int>(n, m, 1);
					Array2D<int>* druha = new Array2Dnoncontiguous<int>(n, m, 1);
					Array2D<int>* vysledna = new Array2Dnoncontiguous<int>(n, m, 0);

					start = high_resolution_clock::now();
					//cout << "zaciatok  " << endl;
					this->scitanie(*prva, *druha, *vysledna);
					//cout << "koniec  " << endl;
					stop = high_resolution_clock::now();
					duration = duration_cast<microseconds>(stop - start);
					cout << "n:  " << n << " T: " << duration.count() << " microseconds, S: " << n * m << endl;
					this->zapis(this->fileName, n, duration.count(), n * m);					
				}
			}
		}
		else
		{
			cout << "Chystas sa testovat nesuvislu maticu. \n" << endl;
			cout << "Nasobenie matic. \n" << endl;
			fileName = name + "_Array2D_noncontiguous_multipli.txt";
			for (n = 100; n <= 2000; n = n + 100)
			{
				cout << "------->>>> n:  " << n << "<<<<-------" << endl;
				for (m = 100; m <= 2000; m = m + 100)
				{
					Array2D<int>* prva = new Array2Dnoncontiguous<int>(n, m, 1);
					Array2D<int>* druha = new Array2Dnoncontiguous<int>(m, n, 1);
					Array2D<int>* vysledna = new Array2Dnoncontiguous<int>(n, n, 0);

					start = high_resolution_clock::now();
					cout << "zaciatok  " << endl;
					this->nasobenie(*prva, *druha, *vysledna);
					cout << "koniec  " << endl;
					stop = high_resolution_clock::now();
					duration = duration_cast<microseconds>(stop - start);
					cout << "m:  " << m << " T: " << duration.count() << " microseconds, S: " << n * m << endl;
					this->zapis(this->fileName, m, duration.count(), n * m);
				}
			}
		}
	}
}

void Array2D_test::zapis(string fileName, int columns, int trvanie, int sizeOf)
{
	ofstream file;
	file.open(fileName, ios_base::app);
	file << columns << ", " << trvanie << ", " << sizeOf << endl;
	file.close();
}




