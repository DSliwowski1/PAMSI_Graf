#pragma once
#include "IEdeg.h"
#include <iostream>

template<typename T>
class VertexLS;


template<typename T>
class EdgeLS : public IEdge {
private:
	VertexLS<T>* u;
	VertexLS<T>* v;
	MLista<EdgeLS<T>*>* lSasiedztwaU; //Wska�nik na list� s�siedztwa u, kt�ra zawiera wska�niki na kraw�dzie
	MLista<EdgeLS<T>*>* lSasiedztwaV; //Wska�nik na list� s�siedztwa v, kt�ra zawiera wska�niki na kraw�dzie
	MNode<EdgeLS<T>*>* position; //Pokazuje na sw�j wska�nik w li�cie kraw�dzi
	double waga;
public:
	MLista<IVertex*> EndVerticies() override;
	IVertex* Opposite(IVertex*) override;
	bool IsAdjecentTo(IEdge*) override;
	bool isIncidentOn(IVertex*) override;
	double GetWaga() override { return waga; }
public:
	VertexLS<T>* GetU() { return u; }
	VertexLS<T>* GetV() { return v; }
	MLista<EdgeLS<T>*>* GetlSasiedztwaU() { return this->lSasiedztwaU; }
	MLista<EdgeLS<T>*>* GetlSasiedztwaV() { return this->lSasiedztwaV; }
	MNode<EdgeLS<T>*>* GetPos() { return this->position; }


	void SetU(VertexLS<T>* a) { u = a; }
	void SetV(VertexLS<T>* a) { v = a; }
	void SetlSasiedztwaU(MLista<EdgeLS<T>*>* a) { lSasiedztwaU = a; }
	void SetlSasiedztwaV(MLista<EdgeLS<T>*>* a) { lSasiedztwaV = a; }
	void SetPos(MNode<EdgeLS<T>*>* a) { position = a; }
	void SetWaga(double a) { waga = a; }
};

//Zwraca liste wektor�w ko�cowych kraw�dzi
template<typename T>
MLista<IVertex*> EdgeLS<T>::EndVerticies()
{
	MLista<IVertex*> tmp;	//Wynik
	
	IVertex* tmpu = this->u;	//Upcast u
	IVertex* tmpv = this->v;	//Upcast v

	tmp.AddEnd(tmpu);
	tmp.AddEnd(tmpv);

	return tmp;
}

//Zrwaca przeciwny wierzcho�ek ko�cowy
template<typename T>
IVertex * EdgeLS<T>::Opposite(IVertex *a)
{
	if (this->isIncidentOn(a)) {	//Czy kraw�d� wychodzi z a
		if (this->u == a)			//Je�eli kraw�d� jest zapisana w u
		{
			IVertex* tmp = this->v;	
			return tmp;		//to zwr�� v
		}
		if (this->v == a)	//Je�eli kraw�d� zapisana jest w v
		{
			IVertex* tmp = this->u;
			return tmp;		//to zr�w� u
		}
	}
	else
	{
		std::cout << "Blad: kraw�d� nie jest incydentna do podanego wierzcholka!" << std::endl;
		return nullptr;
	}
}

//Sprawdza, czy kraw�d� jest s�siadnia (wychodzi z tego samego wierzcho�ka)
template<typename T>
inline bool EdgeLS<T>::IsAdjecentTo(IEdge* e)
{
	EdgeLS<T>* eLS = dynamic_cast<EdgeLS<T>*>(e);	//Downcast, by m�c uzywa� funkcji EdgeLS
	if (eLS)	//Sprawdzenie, cze sie powiod�o
	{
		if (this->u == eLS->GetU() || this->u == eLS->GetV()		//Je�eli przynajmniej jeden z wska�nik�w this i e pokazuj�
			|| this->v == eLS->GetU() || this->v == eLS->GetV())	//na ten sam wierzko�ek, to znaczy, �e s� s�siednie
			return true;
		else
		{
			return false;
		}
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return nullptr;
	}

}

//Sprawdza, czy kraw�d� wychodzi z wierzcho�ka a
template<typename T>
inline bool EdgeLS<T>::isIncidentOn(IVertex *a)
{
	VertexLS<T>* aLS = dynamic_cast<VertexLS<T>*>(a);

	if (aLS){
		if (aLS == this->u || aLS == this->v)	//je�eli kt�rykolwiek z wska�nik�w pokazuje na a, to znaczy, �e
			return true;						//kraw�d� wychodzi z a
		else
		{
			return false;
		}
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
	}

	return false;
}