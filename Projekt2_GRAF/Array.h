#pragma once
#include <iostream>
#include <random>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;

// Szablon klasy implementuj¹cej stukture danych 'Array'
// T - typ
// _data - przechowuje dane
// _size - przechowuje rozmiar tablicy

template <typename T>
class Array
{
private:
	T* _data;
	int _size;

	//Konstuktory, funkcjie dostêpu
public:
	Array(int size);
	Array(int size, int[]);
	Array();
	~Array();
	Array(const Array<T>& a);
	int GetSize() const { return this->_size; }
	void SetSize(int size) { this->_size = size; }

	//Funkcje publiczne
public:
	void Concat(Array<T> end);
	void Swap(int i, int j);

	//Operatory
public:
	T& operator [](int idx) {
		return _data[idx];
	}

	T operator [](int idx) const {
		return _data[idx];
	}

	Array<T>& operator= (const Array<T> &a);
};

//Konstruktory
template<typename T>
Array<T>::Array(int size)
{
	this->_size = size;
	this->_data = new T[this->_size];
}

template<typename T>
Array<T>::Array()
{
	this->_size = 0;
	this->_data = new T[this->_size];
}

template<typename T>
Array<T>::Array(int size, int a[])
{
	this->_size = size;
	this->_data = new T[this->_size];
	for (int i = 0; i < size; ++i)
		this->_data[i] = a[i];
}

//Dekonstruktor
template<typename T>
Array<T>::~Array()
{
	delete[] this->_data;
}

//Konstruktor kopjuj¹cy
template<typename T>
Array<T>::Array(const Array<T>& a)
{
	this->_size = a.GetSize();
	this->_data = new T[this->_size];
	for (int i = 0; i < a.GetSize(); ++i)
		this->_data[i] = a._data[i];
}

//Operator przesuniêcia bitowego w lewo
template<typename T>
std::ostream &operator<<(std::ostream &output, Array<T> &a) {
	for (int i = 0; i < a.GetSize(); ++i)
		output << a[i] << ", ";

	return output;
}

//Operator przypisania
template<typename T>
Array<T>& Array<T>::operator= (const Array<T> &a)
{
	if (this != &a) {
		delete[] this->_data;
		this->_size = a.GetSize();
		this->_data = new T[this->_size];
		for (int i = 0; i < a.GetSize(); ++i)
			this->_data[i] = a._data[i];
	}
	return *this;
}

//Do³¹cza tablice end do koñca aktualnej tablicy
template<typename T>
void Array<T>::Concat(Array<T> end)
{
	int size = this->GetSize() + end.GetSize();		//Powieksz rozmiar

	Array<T> tmp(size);								//Zaalokuj nowa tablice

	for (int i = 0; i < this->GetSize(); i++)		//Skopjuj oryginalna
	{
		tmp[i] = (*this)[i];
	}
	for (int i = this->GetSize(); i < size; i++)	//Skopjuj do³¹czan¹
	{
		tmp[i] = end[i - this->GetSize()];
	}
	*this = tmp;
}

//Zamienia miejscami elementy o indeksach i oraz j
template<typename T>
void Array<T>::Swap(int i, int j)
{
	T tmp = (*this)[i];

	(*this)[i] = (*this)[j];
	(*this)[j] = tmp;

}