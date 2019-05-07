#pragma once
#include "Node.h"

template<typename T>
class MIterator {
private:
	MNode<T>* n;
public:
	T& operator *();								//Zwróæ element z wêz³a na który pokazuje iterator
	bool operator ==(const MIterator<T>& p) const;	//czy równe
	bool operator !=(const MIterator<T>& p) const;	//czy nie równe
	MIterator<T> operator++();						//przesuñ iterator na nastêpny elem
	MIterator<T> operator--();						//przesuñ iterator na poprzedni elem
public: 
	MIterator() {}									//Kostruktor domyœlny
	MIterator(MNode<T>* a);							//Stworz iterator z wêz³a
	MNode<T>* GetNode() { return n; }
};

template<typename T>
T& MIterator<T>::operator*()
{
	return n->GetElem();
}

template<typename T>
bool MIterator<T>::operator==(const MIterator<T>& p) const
{
	return (this->n == p.n);
}

template<typename T>
bool MIterator<T>::operator!=(const MIterator<T>& p) const
{
	return (this->n != p.n);
}

template<typename T>
inline MIterator<T> MIterator<T>::operator++()
{
	n=n->GetNext();
	return *this;
}

template<typename T>
inline MIterator<T> MIterator<T>::operator--()
{
	n=n->GetPrev();

	return *this;
}

template<typename T>
MIterator<T>::MIterator(MNode<T>* a)
{
	n = a;
}