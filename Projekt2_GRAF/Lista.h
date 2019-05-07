#pragma once

#include "Iterator.h"
#include "Node.h"
#include <iostream>

template<typename T>
class MLista {
private:
	MNode<T>* header;	//stra¿nik pocz¹tku
	MNode<T>* tailer;	//stra¿nik koñca
	int size;			//Rozmiar
public:
	int Size();					//Zwraca rozmiar
	int Size() const;					//Zwraca rozmiar
	bool IsEmpty();				//Zrwaca czy pusta
	MIterator<T> Begin();		//Zrwaca iterator na pocz¹tek
	MIterator<T> Begin() const;		//Zrwaca iterator na pocz¹tek
	MIterator<T> End();			//Zwraca iterator na koniec
	void AddFront(MNode<T> a);	//Dodaje na pocz¹tku
	void AddEnd(MNode<T> a);	//Dodaje na koñcu
	void Add(MIterator<T> q, MNode<T>& a);		//Dodaje przed iteratorem
	void EraseFront();	//Usuwa z pocz¹tku
	void EraseBack();	//Usuwa z koñca
	void Erase(MIterator<T> q);	//usuwa z pozycji iteratora
public:
	MLista();	//konstuktor domyslny
	~MLista();	//dekonstruktor
public:
	MLista<T>& operator=(MLista<T>);
	MLista(const MLista<T>&);
};

//Wyœwietlanie listy g³ównie u¿yte do debugowania
template<typename T>
std::ostream& operator <<(std::ostream& wyj, MLista<T>& a)
{
	MIterator<T> p = a.Begin();

	if (a.IsEmpty())
		wyj << "Pusta" << std::endl;

	for (int i = 0; i < a.Size(); ++i)
	{
		wyj << p.GetNode()->GetElem() << ", ";
		++p;
	}
	return wyj;
}

template<typename T>
MLista<T>::MLista()
{
	header = new MNode<T>;
	tailer = new MNode<T>;
	size = 0;

	header->SetNext(tailer);
	header->SetPrev(nullptr);
	tailer->SetNext(nullptr);
	tailer->SetPrev(header);
}

template<typename T>
MLista<T>::~MLista()
{
	delete header;
	delete tailer;
	header = tailer = nullptr;
}

template<typename T>
int MLista<T>::Size()
{
	return size;
}

template<typename T>
bool MLista<T>::IsEmpty()
{
	return (size == 0);
}

template<typename T>
MIterator<T> MLista<T>::Begin()
{
	MIterator<T> a(header->GetNext());	//Begin zrwaca iterator na pierwszy element listy, czyli element po header
	return a;
}

template<typename T>
MIterator<T> MLista<T>::End()
{
	MIterator<T> a(tailer);		//End zwraca iterator na pierwszy element po ostatnim elemencie tablicy, czyli na tailer
	return a;
}

template<typename T>
void MLista<T>::Add(MIterator<T> q, MNode<T>& n)
{
	MNode<T>* ost = q.GetNode();
	MNode<T>* pier = ost->GetPrev();
	MNode<T>* sr = new MNode<T>;
	sr->SetElem(n.GetElem());

	sr->SetNext(ost);
	ost->SetPrev(sr);
	sr->SetPrev(pier);
	pier->SetNext(sr);

	size++;
}

template<typename T>
void MLista<T>::AddFront(MNode<T> a)
{
	this->Add(this->Begin(), a);
}

template<typename T>
void MLista<T>::AddEnd(MNode<T> a)
{
	this->Add(this->End(), a);
}

template<typename T>
void MLista<T>::Erase(MIterator<T> q)
{
	MNode<T>* b = q.GetNode(); //Ten do usuniecia
	MNode<T>* a = b->GetPrev(); //element poprzedzajacy
	MNode<T>* c = b->GetNext(); //element za

	a->SetNext(c);
	c->SetPrev(a);
	delete b;

	size--;
}

template<typename T>
void MLista<T>::EraseFront()
{
	this->Erase(this->Begin());		//usuñ pierwszy element
}

template<typename T>
void MLista<T>::EraseBack()
{
	this->Erase(--(this->End()));	//Usuñ element ostatni (element przez End)
}


template<typename T>
MLista<T>& MLista<T>::operator=(MLista<T> a)
{
	MLista<T> wyn;

	MIterator<T> p = a.Begin();
	for (int i = 0; i < a.Size(); i++)
	{
		wyn.AddFront(p.GetNode()->GetElem());
		++p;
	}

	return wyn;
}

template<typename T>
MLista<T>::MLista(const MLista<T>& a)
{
	this->header = new MNode<T>;
	this->tailer = new MNode<T>;
	this->size = 0;

	this->header->SetNext(tailer);
	this->header->SetPrev(nullptr);
	this->tailer->SetNext(nullptr);
	this->tailer->SetPrev(header);

	MIterator<T> p = a.Begin();
	for (int i = 0; i < a.Size(); i++)
	{
		this->AddFront(p.GetNode()->GetElem());
		++p;
	}
}

template<typename T>
inline MIterator<T> MLista<T>::Begin() const
{
	MIterator<T> a(header->GetNext());	//Begin zrwaca iterator na pierwszy element listy, czyli element po header
	return a;
}

template<typename T>
inline int MLista<T>::Size() const
{
	return size;
}