#pragma once
#include "Array.h"
#include <iostream>

//U¿ywa reprezentacji wierszowej
template<typename T>
class MacierzKw {
private:
	int n; //wymiar macierzy
	Array<T> dane;
public:
	MacierzKw()
	{
		n = 0;
	}
	MacierzKw(int i)
	{
		n = i;
		dane = Array<T>(n*n);
	}
public:
	int GetWymiar() { return n; }

	T& operator ()(int x, int y);

	T operator ()(int x, int y) const;
};

//Zwróæ wartoœæ przechowywan¹ w x, y
template<typename T>
T & MacierzKw<T>::operator()(int x, int y)
{
	return dane[x*n + y];
}

template<typename T>
T MacierzKw<T>::operator()(int x, int y) const
{
	return dane[x*n + y];
}