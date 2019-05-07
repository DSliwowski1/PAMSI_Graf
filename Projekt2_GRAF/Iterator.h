#pragma once
#include "Node.h"

template<typename T>
class MIterator {
private:
	MNode<T>* n;
public:
	T& operator *();								//Zwr�� element z w�z�a na kt�ry pokazuje iterator
	bool operator ==(const MIterator<T>& p) const;	//czy r�wne
	bool operator !=(const MIterator<T>& p) const;	//czy nie r�wne
	MIterator<T> operator++();						//przesu� iterator na nast�pny elem
	MIterator<T> operator--();						//przesu� iterator na poprzedni elem
public: 
	MIterator() {}									//Kostruktor domy�lny
	MIterator(MNode<T>* a);							//Stworz iterator z w�z�a
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