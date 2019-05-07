#pragma once
#include "IVertex.h"
#include "Lista.h"

template<typename T>
class EdgeLS;


template<typename T>
class VertexLS : public IVertex {
private:
	MNode<VertexLS<T>*>* position;	 //Pokazuje na swój wskaŸnik w liœcie wierzcho³ków
	T elem;							 //Dana, któr¹ przechowuje wierzko³ek
	MLista<EdgeLS<T>*>* lSasiedztwa; //WskaŸnik na listê s¹siedztwa, która zawiera wskaŸniki na krawêdzie
public:
	MLista<IEdge*> IncidentEdges() override; //Lista krawêdzi incydentnych do wierzcho³ka
	bool isAdjacentTo(IVertex* v) override; //Zwraca czy v jest s¹siednie
	void Print(std::ostream&) override;
public:
	VertexLS(T e) 
	{
		position = nullptr;
		elem = e;
		lSasiedztwa = new MLista<EdgeLS<T>*>;
	}
	~VertexLS()
	{
		delete lSasiedztwa;
	}
public:
	void SetPosition(MNode<VertexLS<T>*>* a) { position = a; }
	void Setelem(T a) { elem = a; }
	void SetlSasiedzwtwa(MLista<EdgeLS<T>>* a) { lSasiedztwa = a; }
	MNode<VertexLS<T>*>* GetPosition() { return this->position; }
	T GetElem() { return this->elem; }
	MLista<EdgeLS<T>*>* GetlSasiedztwa() { return this->lSasiedztwa; }
};

template<typename T>
std::ostream& operator <<(std::ostream& wyj, VertexLS<T>& a)
{
	wyj << a.GetElem();

	return wyj;
}

template<typename T>
inline void VertexLS<T>::Print(std::ostream& wyj)
{
	wyj << *(this);
}


//Zwraca liste wszystkich krawêdzi wychodz¹cych(Zatem wszystkich w l. S¹siedztwa)
template<typename T>
MLista<IEdge*> VertexLS<T>::IncidentEdges()
{
	MLista<IEdge*> tmp;	//Wynik

	MIterator<EdgeLS<T>*> p = this->lSasiedztwa->Begin();	//Iterator na pocz¹tku LS
	for (int i = 0; i < this->lSasiedztwa->Size(); i++)		//Przechodzimi po ka¿dym elemencie
	{
		IEdge* a = p.GetNode()->GetElem();	
		tmp.AddEnd(a);		//Dodajemy do listy wyników
		++p;		//Przesuwamy siê na nastêpny wêze³
	}

	return tmp;
}

//Sprawdz, czy dwie krawêdzie s¹ s¹siednie
template<typename T>
bool VertexLS<T>::isAdjacentTo(IVertex *v)
{
	VertexLS* tmp = dynamic_cast<VertexLS*>(v);		//Downcast by móc uzywaæ metod VertexLS
	if (tmp)		//Sprawdzenie, czy siê powiod³o
	{
		if (this->lSasiedztwa->Size() <= tmp->lSasiedztwa->Size())		//Wybierz krótsz¹ liste s¹siedztwa
		{
			MIterator<EdgeLS<T>*> p = this->GetlSasiedztwa()->Begin();	//Ustaw iterator na pocz¹tku LS this
			for (int i = 0; i < this->lSasiedztwa->Size(); i++)			//Dla ka¿dego elementu w LS
			{
				if (p.GetNode()->GetElem()->GetU() == v || p.GetNode()->GetElem()->GetV() == v)	//SprawdŸ, czy którykolwiek z wskaŸników pokazuje na v
					return true;
				else
					return false;
				++p;
			}
		{

		}
		}
		else
		{
			MIterator<EdgeLS<T>*> p = tmp->GetlSasiedztwa()->Begin();	//to samo co wy¿ej tylko dla tmp
			for (int i = 0; i < tmp->lSasiedztwa->Size(); i++)
			{
				if (p.GetNode()->GetElem()->GetU() == this || p.GetNode()->GetElem()->GetV() == this)  //SprawdŸ, czy którykolwiek z wska¿ników pokazuje na this
					return true;
				else
					return false;
				++p;
			}
		}
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return false;
	}
}