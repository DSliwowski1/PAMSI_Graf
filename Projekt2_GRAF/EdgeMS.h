#pragma once
#include "IEdeg.h"

template<typename T>
class VertexMS;

template<typename T>
class EdgeMS : public IEdge {
private:
	VertexMS<T>* u;
	VertexMS<T>* v;
	MNode<EdgeMS<T>*>* position; //Pokazuje na sw�j wska�nik w li�cie kraw�dzi
	double waga;
public:
	MLista<IVertex*> EndVerticies() override;
	IVertex* Opposite(IVertex*) override;
	bool IsAdjecentTo(IEdge*) override;
	bool isIncidentOn(IVertex*) override;
	double GetWaga() override { return waga; }
public:
	VertexMS<T>* GetU() { return u; }
	VertexMS<T>* GetV() { return v; }
	MNode<EdgeMS<T>*>* GetPos() { return this->position; }

	void SetU(VertexMS<T>* a) { u = a; }
	void SetV(VertexMS<T>* a) { v = a; }
	void SetPos(MNode<EdgeMS<T>*>* a) { position = a; }
	void SetWaga(double a) { waga = a; }
};

//Zwraca liste wektor�w ko�cowych kraw�dzi
template<typename T>
MLista<IVertex*> EdgeMS<T>::EndVerticies()
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
IVertex * EdgeMS<T>::Opposite(IVertex *a)
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
inline bool EdgeMS<T>::IsAdjecentTo(IEdge* e)
{
	EdgeMS<T>* eLS = dynamic_cast<EdgeMS<T>*>(e);	//Downcast, by m�c uzywa� funkcji EdgeLS
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
inline bool EdgeMS<T>::isIncidentOn(IVertex *a)
{
	VertexMS<T>* aLS = dynamic_cast<VertexMS<T>*>(a);

	if (aLS) {
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