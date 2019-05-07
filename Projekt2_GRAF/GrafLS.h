#pragma once
#include "IGraf.h"
#include "VertexLS.h"
#include "EdgeLS.h"
#include "Lista.h"
#include <iostream>
#include <random>

template<typename T>
class GrafLS: public IGraf
{
private:
	MLista<VertexLS<T>*> vertexList;
	MLista<EdgeLS<T>*> edgeList;
public:
	MLista<IVertex* > Vertices() override;
	MLista<IEdge* > Edges() override;
	IVertex* InsertVertex(IVertex*) override;
	IEdge* InsertEdge(IVertex*, IVertex*, double) override;
	void RemoveVertex(IVertex*) override;
	void RemoveEdge(IEdge*) override;
	void Generate(int, double) override;

public:
	MLista<VertexLS<T>*>& GetVL() { return this->vertexList; }
	MLista<EdgeLS<T>*>& GetEL() { return this->edgeList; }

};

template<typename T>
std::ostream& operator <<(std::ostream& wyj, GrafLS<T>& g)
{
	wyj << "Num vert: " << g.GetVL().Size() << " Num edge: " << g.GetEL().Size() << std::endl;
	wyj << "U     " << "w     " << "V      " << std::endl;

	MIterator<EdgeLS<T>*> p = g.GetEL().Begin();
	for (int i = 0; i < g.GetEL().Size(); ++i)
	{
		wyj << p.GetNode()->GetElem()->GetU()->GetElem() << "     " << p.GetNode()->GetElem()->GetWaga() << "     " << p.GetNode()->GetElem()->GetV()->GetElem() << "     " << std::endl;
		++p;
	}

	return wyj;
}

template<typename T>
MLista<IVertex*> GrafLS<T>::Vertices()
{
	MLista<IVertex*> tmp;
	MIterator<VertexLS<T>*> p = this->vertexList.Begin();	
	for (int i = 0; i < this->vertexList.Size(); i++)
	{
		tmp.AddFront(p.GetNode()->GetElem());	//Dla ka¿dego elementu w liœcie wierzcho³kow, zrzutuj w góre i dodaj do lisy
		++p;
	}
	return tmp;
}

template<typename T>
MLista<IEdge*> GrafLS<T>::Edges()
{
	MLista<IEdge*> tmp;
	MIterator<EdgeLS<T>*> p = this->edgeList.Begin();
	for (int i = 0; i < this->edgeList.Size(); i++)		//Dla ka¿dego elementu w liœcie krawêdzi, zrzutuj w góre i dodaj do lisy
	{
		tmp.AddFront(p.GetNode()->GetElem());	
		++p;
	}
	return tmp;
}

template<typename T>
IVertex* GrafLS<T>::InsertVertex(IVertex *a)
{
	VertexLS<T>* aLS = dynamic_cast<VertexLS<T>*>(a);	//Zrzutuj w dó³ by móc uzywac funkcji

	if (aLS)	//Sprawdzenie czy sie powiod³o
	{
		this->vertexList.AddFront(aLS);		//Dodaj na pocz¹tku listy wierzcho³ków
		MIterator<VertexLS<T>*> p = this->vertexList.Begin();
		p.GetNode()->GetElem()->SetPosition(p.GetNode());	//Ustaw jego pozycje
		return p.GetNode()->GetElem();
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return nullptr;
	}
}

template<typename T>
IEdge* GrafLS<T>::InsertEdge(IVertex *v, IVertex *u, double w)
{
	VertexLS<T>* vLS = dynamic_cast<VertexLS<T>*>(v);	//Zrzutuj w dó³ by móc uzywac funkcji
	VertexLS<T>* uLS = dynamic_cast<VertexLS<T>*>(u);	//Zrzutuj w dó³ by móc uzywac funkcji

	if (vLS && uLS)	//SprawdŸ czy sie powiod³o
	{
		EdgeLS<T>* e = new EdgeLS<T>();		//Stwórz now¹ krawêdŸ

		this->edgeList.AddFront(e);		//Dodaj do listy krawêdzi
		MIterator<EdgeLS<T>*> p = this->edgeList.Begin();
		p.GetNode()->GetElem()->SetPos(p.GetNode());	//Ustaw pozucje

		vLS->GetlSasiedztwa()->AddFront(e);		//Dodaj do list s¹siedztwa
		uLS->GetlSasiedztwa()->AddFront(e);

		e->SetU(uLS);	//Ustaw wierzcho³iki
		e->SetV(vLS);

		e->SetlSasiedztwaU(uLS->GetlSasiedztwa());	//Ustaw listy s¹siedztwa
		e->SetlSasiedztwaV(vLS->GetlSasiedztwa());

		e->SetWaga(w);	//Ustaw wage

		return e;
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return nullptr;
	}
}

template<typename T>
void GrafLS<T>::RemoveVertex(IVertex *a)
{
	MIterator<VertexLS<T>*> p;
	VertexLS<T>* aLS = dynamic_cast<VertexLS<T>*>(a);

	if (aLS)
	{
		//Usuniêcie wszystkich krawêdzi incydentnych na a
		while (!aLS->GetlSasiedztwa()->IsEmpty())
		{
			MIterator<EdgeLS<T>*> p = aLS->GetlSasiedztwa()->Begin();
			EdgeLS<T>* e = p.GetNode()->GetElem();
			this->RemoveEdge(e);
		}
		//Usuñ z listy wierzcho³ków
		MIterator<VertexLS<T>*> q(aLS->GetPosition());
		this->vertexList.Erase(q);
		aLS->SetPosition(nullptr);
		//Usuniêdzie aLS
		delete aLS;
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
	}
}

template<typename T>
void GrafLS<T>::RemoveEdge(IEdge *e)
{
	if (e == nullptr)
	{
		std::cout << "Nie ma takiej krawedzi" << std::endl;
		return;
	}

	EdgeLS<T>* eLS = dynamic_cast<EdgeLS<T>*>(e);

	if (eLS)
	{	
		//Usuñ z listy s¹siedztwa U
		MIterator<EdgeLS<T>*> p = eLS->GetlSasiedztwaU()->Begin();
		for (int i = 0; i < eLS->GetlSasiedztwaU()->Size(); i++)
		{
			if (p.GetNode()->GetElem() == eLS)
				break;
			++p;
		}
		eLS->GetlSasiedztwaU()->Erase(p);
		eLS->SetlSasiedztwaU(nullptr);

		//Usuñ z listy s¹siedztwa V
		p = eLS->GetlSasiedztwaV()->Begin();
		for (int i = 0; i < eLS->GetlSasiedztwaV()->Size(); i++)
		{
			if (p.GetNode()->GetElem() == eLS)
				break;
			++p;
		}
		eLS->GetlSasiedztwaV()->Erase(p);
		eLS->SetlSasiedztwaV(nullptr);

		//ustawienie u i v na null
		eLS->SetU(nullptr);
		eLS->SetV(nullptr);

		//Usuñ z listy krawêdzi
		MIterator<EdgeLS<T>*> q(eLS->GetPos());
		this->edgeList.Erase(q);
		eLS->SetPos(nullptr);

		delete eLS;
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
	}
}

template<typename T>
void GrafLS<T>::Generate(int n, double p)
{
	std::random_device rd; // losowa liczba z systemu
	std::mt19937 eng(rd()); // seedujemy generator
	std::uniform_real_distribution<double> distr(0, 1); //ustalamy granice

	for (int i = 0; i < n; i++)
	{
		this->InsertVertex(new VertexLS<T>(i));	//Dodajemy zadana iloœc wierzcho³ków
	}

	MIterator<VertexLS<T>*> a = this->vertexList.Begin();
	for (int i = 0; i < this->vertexList.Size(); i++) {

		MIterator<VertexLS<T>*> q = this->vertexList.Begin();
		for (int j = 0; j < this->vertexList.Size(); j++)	//dla ka¿dej pary wierzcho³ków
		{
			double lb = distr(eng);		//wygeneruj lowosa piczb¹
			//Jezeli jest mniejsza niz zadana wartoœæ oraz nie ma pomiedzy nimi krawêdzi to stwórz j¹ z losowym indeksem
			if (a.GetNode()->GetElem() != q.GetNode()->GetElem() && lb <= p && !a.GetNode()->GetElem()->isAdjacentTo(q.GetNode()->GetElem()))
			{
				double waga = 1 + (std::rand() % (10 - 1 + 1));
				this->InsertEdge(a.GetNode()->GetElem(), q.GetNode()->GetElem(), waga);
			}
			++q;
		}
		++a;
	}
}