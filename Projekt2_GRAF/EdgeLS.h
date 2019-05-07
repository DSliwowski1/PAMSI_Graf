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
	MLista<EdgeLS<T>*>* lSasiedztwaU; //WskaŸnik na listê s¹siedztwa u, która zawiera wskaŸniki na krawêdzie
	MLista<EdgeLS<T>*>* lSasiedztwaV; //WskaŸnik na listê s¹siedztwa v, która zawiera wskaŸniki na krawêdzie
	MNode<EdgeLS<T>*>* position; //Pokazuje na swój wskaŸnik w liœcie krawêdzi
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

//Zwraca liste wektorów koñcowych krawêdzi
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

//Zrwaca przeciwny wierzcho³ek koñcowy
template<typename T>
IVertex * EdgeLS<T>::Opposite(IVertex *a)
{
	if (this->isIncidentOn(a)) {	//Czy krawêdŸ wychodzi z a
		if (this->u == a)			//Je¿eli krawêdŸ jest zapisana w u
		{
			IVertex* tmp = this->v;	
			return tmp;		//to zwróæ v
		}
		if (this->v == a)	//Je¿eli krawêdŸ zapisana jest w v
		{
			IVertex* tmp = this->u;
			return tmp;		//to zrówæ u
		}
	}
	else
	{
		std::cout << "Blad: krawêdŸ nie jest incydentna do podanego wierzcholka!" << std::endl;
		return nullptr;
	}
}

//Sprawdza, czy krawêdŸ jest s¹siadnia (wychodzi z tego samego wierzcho³ka)
template<typename T>
inline bool EdgeLS<T>::IsAdjecentTo(IEdge* e)
{
	EdgeLS<T>* eLS = dynamic_cast<EdgeLS<T>*>(e);	//Downcast, by móc uzywaæ funkcji EdgeLS
	if (eLS)	//Sprawdzenie, cze sie powiod³o
	{
		if (this->u == eLS->GetU() || this->u == eLS->GetV()		//Je¿eli przynajmniej jeden z wskaŸników this i e pokazuj¹
			|| this->v == eLS->GetU() || this->v == eLS->GetV())	//na ten sam wierzko³ek, to znaczy, ¿e s¹ s¹siednie
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

//Sprawdza, czy krawêdŸ wychodzi z wierzcho³ka a
template<typename T>
inline bool EdgeLS<T>::isIncidentOn(IVertex *a)
{
	VertexLS<T>* aLS = dynamic_cast<VertexLS<T>*>(a);

	if (aLS){
		if (aLS == this->u || aLS == this->v)	//je¿eli którykolwiek z wskaŸników pokazuje na a, to znaczy, ¿e
			return true;						//krawêdŸ wychodzi z a
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