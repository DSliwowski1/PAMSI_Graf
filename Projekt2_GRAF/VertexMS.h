#pragma once
#include "IVertex.h"
#include "Lista.h"
#include "Array.h"
#include "MacierzKw.h"
#include <iostream>

template<typename T>
class EdgeMS;

template<typename T>
class VertexMS :public IVertex {
private:
	int index;						//Indeks elementu
	T elem;							//Przechowywana dana
	MNode<VertexMS<T>*>* position;  //Pokazuje na sw�j wska�nik w li�cie wierzcho�k�w
	MacierzKw<EdgeMS<T>*>* MSasiedztwa; //Wska�nik na macierz s�si�dztwa, aby mie� informacje o incydetnych kraw�dziach
public:
	MLista<IEdge*> IncidentEdges() override; //Lista kraw�dzi incydentnych do wierzcho�ka
	bool isAdjacentTo(IVertex*) override;    //Zwraca czy v jest s�siednie
	void Print(std::ostream&) override;
public: 
	VertexMS(T e)
	{
		position = nullptr;
		elem = e;
		index = -1;			//Domy�lny index -1, poniewa� taki nie mo�e istnie� w tablicy
		MSasiedztwa = nullptr;
	}
public:
	void SetPosition(MNode<VertexMS<T>*>* a) { position = a; }
	void SetElem(T a) { elem = a; }
	void SetIndex(int a) { index = a; }
	void SetMSasiedztwa(MacierzKw<EdgeMS<T>*>* a) { MSasiedztwa = a; }

	MNode<VertexMS<T>*>* GetPosition() { return this->position; }
	T GetElem() { return this->elem; }
	int GetIndex() { return index; }
};

template<typename T>
std::ostream& operator <<(std::ostream& wyj, VertexMS<T>& a)
{
	wyj << a.GetElem();

	return wyj;
}

template<typename T>
inline void VertexMS<T>::Print(std::ostream& wyj)
{
	wyj << *(this);
}

template<typename T>
MLista<IEdge*> VertexMS<T>::IncidentEdges()
{
	MLista<IEdge*> tmp;	//Lista do kt�rej b�d� dodawane kraw�dzie

	if (index == -1 || MSasiedztwa == nullptr) {  //sprawdzenie czy nale�y do grafu
		std::cout << "Nie nale�y do grafu" << std::endl;
		return tmp;
	}

	for (int j = 0; j < this->MSasiedztwa->GetWymiar(); ++j)
	{
		IEdge* e = this->MSasiedztwa->operator()(this->index, j);
		if (e != nullptr)
			tmp.AddEnd(e);
	}		

	return tmp;
}

template<typename T>
bool VertexMS<T>::isAdjacentTo(IVertex *v)
{
	VertexMS<T>* vMS = dynamic_cast<VertexMS<T>*>(v);	//rzutowanie �eby m�c uzywa� method VertexMS
	if (vMS){		//Sprawdzenie czy rzutowanie sie uda�o
		if (MSasiedztwa == nullptr || vMS->MSasiedztwa == nullptr) { //sprawdzenie czy nale�� do grafu
			std::cout << "Nie nale�y do grafu" << std::endl;
			return false;
		}

		int ui = this->GetIndex();	//Indeks U
		int vi = vMS->GetIndex();	//Indeks V

		if (this->MSasiedztwa->operator()(ui, vi) == nullptr) //Je�eli krew�d� u i v jest nullptr, to nie s� s�siednie
			return false;
		else
			return true;
	}	
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return false;
	}
}