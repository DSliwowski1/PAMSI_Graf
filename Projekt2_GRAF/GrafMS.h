#pragma once
#include "IGraf.h"
#include "EdgeMS.h"
#include "VertexMS.h"
#include "Lista.h"
#include "MacierzKw.h"
#include <random>

template<typename T>
class GrafMS : public IGraf {
private:
	MLista<VertexMS<T>*> vertexList;
	MLista<EdgeMS<T>*> edgeList;
	MacierzKw<EdgeMS<T>*>* MSasiedztwa;
public:
	MLista<IVertex* > Vertices() override;
	MLista<IEdge* > Edges() override;
	IVertex* InsertVertex(IVertex*) override;
	IEdge* InsertEdge(IVertex*, IVertex*, double) override;
	void RemoveVertex(IVertex*) override;
	void RemoveEdge(IEdge*) override;
	void Generate(int, double) override;
public:
	MLista<VertexMS<T>*>& GetVL() { return this->vertexList; }
	MLista<EdgeMS<T>*>& GetEL() { return this->edgeList; }
public:
	GrafMS()
	{
		MSasiedztwa = new MacierzKw<EdgeMS<T>*>();
	}
	~GrafMS()
	{
		delete MSasiedztwa;
	}
};

template<typename T>
std::ostream& operator <<(std::ostream& wyj, GrafMS<T>& g)
{
	wyj << "Num vert: " << g.GetVL().Size() << " Num edge: " << g.GetEL().Size() << std::endl;
	wyj << "U     " << "w     " << "V      " << std::endl;

	MIterator<EdgeMS<T>*> p = g.GetEL().Begin();
	for (int i = 0; i < g.GetEL().Size(); ++i)
	{
		wyj << p.GetNode()->GetElem()->GetU()->GetElem() << "     " << p.GetNode()->GetElem()->GetWaga() << "     " << p.GetNode()->GetElem()->GetV()->GetElem() << "     " << std::endl;
		++p;
	}

	return wyj;
}


//Zwraca list� wierzcho�k�w
template<typename T>
MLista<IVertex*> GrafMS<T>::Vertices()
{
	MLista<IVertex*> tmp;	//Wyniki
	MIterator<VertexMS<T>*> p = this->vertexList.Begin();	//Iterator na pocz�tek
	for (int i = 0; i < this->vertexList.Size(); i++)
	{
		tmp.AddFront(p.GetNode()->GetElem());	//Dodaj do wynik�w
		++p;	//przejd� do nast�pnego wierzcho�ka
	}
	return tmp;
}

//Zwraca list� kraw�dzi
template<typename T>
MLista<IEdge*> GrafMS<T>::Edges()
{
	MLista<IEdge*> tmp;		//Wyniki
	MIterator<EdgeMS<T>*> p = this->edgeList.Begin();	//Iterator na pocz�tek
	for (int i = 0; i < this->edgeList.Size(); i++)
	{
		tmp.AddFront(p.GetNode()->GetElem());	//Dodaj do wynik�w
		++p;	//Przejd� do nast�pnego
	}
	return tmp;
}

template<typename T>
IVertex * GrafMS<T>::InsertVertex(IVertex * a)
{
	VertexMS<T>* aMS = dynamic_cast<VertexMS<T>*>(a);	//Rzutowanie w d�, by m�c u�ywa� metod VertexMS

	if (aMS)	//Sprawdzenie czy sie powiod�o
	{	
		this->vertexList.AddEnd(aMS);	//Dodanie wierzcho�ka na konie� listy wierzcho�k�w
		MIterator<VertexMS<T>*> p = this->vertexList.End();	//Ustawienie iteratora na element po ostatniom elemencie listy
		--p;	//Przesuni�cie go na ostatni element
		p.GetNode()->GetElem()->SetPosition(p.GetNode());	//Ustawienie wska�nika pozycji dodanego elementu

		//Zaktualizowanie indeks�w
		p = this->vertexList.Begin();	//Przechodimy od pocz�tku listy
		for (int i = 0; i < this->vertexList.Size(); ++i)	//Dla ka�dego elementu
		{
			p.GetNode()->GetElem()->SetIndex(i);	//Ustaw indeks
			++p;
		}

		//Powi�kszenie macierzy s�siedztwa
		delete this->MSasiedztwa;
		this->MSasiedztwa = new MacierzKw<EdgeMS<T>*>(this->vertexList.Size());
		
		//Ustawienie wszystkich wska�nik�w na null
		for (int i = 0; i < this->MSasiedztwa->GetWymiar(); ++i)
			for (int j = 0; j < this->MSasiedztwa->GetWymiar(); ++j)
				this->MSasiedztwa->operator()(i, j) = nullptr;

		//Ponowne ustawienie wska�nik�w na kraw�dzie, je�eli istnia�y
		if (!this->edgeList.IsEmpty()) {	//Je�eli istani�y jakie� kraw�dzie
			MIterator<EdgeMS<T>*> q = this->edgeList.Begin();
			for (int x = 0; x < this->edgeList.Size(); ++x)		//Przejd� po wszystkich kraw�dziach
			{
				int i = q.GetNode()->GetElem()->GetU()->GetIndex();	//Odczytaj indeks U
				int j = q.GetNode()->GetElem()->GetV()->GetIndex();	//Odczytaj indeks V
				this->MSasiedztwa->operator()(i, j) = q.GetNode()->GetElem();	//Ustaw wska�nik w polu (i ,j)
				this->MSasiedztwa->operator()(j, i) = q.GetNode()->GetElem();	//Jako, �e nieskierowany, to ten sam wska�nik w (j, i)
			}
		}

		//Ustawienie wszystkim wierzcho�kom nowej macierzy s�siedztwa;
		p = this->vertexList.Begin();
		for (int i = 0; i < this->vertexList.Size(); ++i)
		{
			p.GetNode()->GetElem()->SetMSasiedztwa(this->MSasiedztwa);
			++p;
		}

		//Zwr�cenie dodanego elementu
		p = this->vertexList.End();
		--p;
		return p.GetNode()->GetElem();
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return nullptr;
	}
}

template<typename T>
inline IEdge * GrafMS<T>::InsertEdge(IVertex * v, IVertex * u, double w)
{
	VertexMS<T>* vMS = dynamic_cast<VertexMS<T>*>(v);	//Rzutowanie
	VertexMS<T>* uMS = dynamic_cast<VertexMS<T>*>(u);	//Rzutowanie
		
	if (vMS && uMS)	//Sprawdzenie, czy rzutowanie sie powiodlo
	{
		EdgeMS<T>* e = new EdgeMS<T>();	//Stworzenie kraw�dzie

		this->edgeList.AddFront(e);		//Dodanie jej do listy kraw�dzi

		//Ustawienie pozycji
		MIterator<EdgeMS<T>*> p = this->edgeList.Begin();
		p.GetNode()->GetElem()->SetPos(p.GetNode());	

		//Ustawienie U* i V*
		e->SetU(uMS);
		e->SetV(vMS);

		//Odczytanie ideks�w
		int i = e->GetU()->GetIndex();	//Odczytaj indeks U
		int j = e->GetV()->GetIndex();	//Odczytaj indeks V

		//Ustawienie wska�nik�w M. S�siedztwa
		this->MSasiedztwa->operator()(i, j) = e;	//Ustaw wska�nik w polu (i ,j)
		this->MSasiedztwa->operator()(j, i) = e;	//Jako, �e nieskierowany, to ten sam wska�nik w (j, i)
	
		//Ustawienie wagi
		e->SetWaga(w);

		//Zwr�cenie kraw�dzi
		return e;
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
		return nullptr;
	}
}

template<typename T>
inline void GrafMS<T>::RemoveVertex(IVertex *a)
{
	VertexMS<T>* aMS = dynamic_cast<VertexMS<T>*>(a);

	if (aMS)
	{
		for (int i = 0; i < this->MSasiedztwa->GetWymiar(); i++)
		{
			//std::cout << this->MSasiedztwa->operator()(i, aMS->GetIndex()) << std::endl;
			this->RemoveEdge(this->MSasiedztwa->operator()(i, aMS->GetIndex()));
		}

		aMS->SetMSasiedztwa(nullptr);

		//Usu� z listy wierzcho�k�w
		MIterator<VertexMS<T>*> q(aMS->GetPosition());
		this->vertexList.Erase(q);
		aMS->SetPosition(nullptr);

		delete aMS;

		MIterator<VertexMS<T>*> p = this->vertexList.Begin();
		for (int i = 0; i < this->vertexList.Size(); ++i)	//Dla ka�dego elementu
		{
			p.GetNode()->GetElem()->SetIndex(i);	//Ustaw indeks
			++p;
		}

		//Pomniejszenie macierzy s�siedztwa
		delete this->MSasiedztwa;
		this->MSasiedztwa = new MacierzKw<EdgeMS<T>*>(this->vertexList.Size());

		//Ustawienie wszystkich wska�nik�w na null
		for (int i = 0; i < this->MSasiedztwa->GetWymiar(); ++i)
			for (int j = 0; j < this->MSasiedztwa->GetWymiar(); ++j)
				this->MSasiedztwa->operator()(i, j) = nullptr;

		//Ponowne ustawienie wska�nik�w na kraw�dzie, je�eli istnia�y
		if (!this->edgeList.IsEmpty()) {	//Je�eli istani�y jakie� kraw�dzie
			MIterator<EdgeMS<T>*> q = this->edgeList.Begin();
			for (int x = 0; x < this->edgeList.Size(); ++x)		//Przejd� po wszystkich kraw�dziach
			{
				int i = q.GetNode()->GetElem()->GetU()->GetIndex();	//Odczytaj indeks U
				int j = q.GetNode()->GetElem()->GetV()->GetIndex();	//Odczytaj indeks V
				this->MSasiedztwa->operator()(i, j) = q.GetNode()->GetElem();	//Ustaw wska�nik w polu (i ,j)
				this->MSasiedztwa->operator()(j, i) = q.GetNode()->GetElem();	//Jako, �e nieskierowany, to ten sam wska�nik w (j, i)
				++q;
			}
		}

		//Ustawienie wszystkim wierzcho�kom nowej macierzy s�siedztwa;
		p = this->vertexList.Begin();
		for (int i = 0; i < this->vertexList.Size(); ++i)
		{
			p.GetNode()->GetElem()->SetMSasiedztwa(this->MSasiedztwa);
			++p;
		}
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
	}
}

template<typename T>
inline void GrafMS<T>::RemoveEdge(IEdge *e)
{
	if (e == nullptr)
	{
	//	std::cout << "Nie ma takiej krawedzi" << std::endl;
		return;
	}

	EdgeMS<T>* eMS = dynamic_cast<EdgeMS<T>*>(e);

	if (eMS)
	{
		//Odczytanie ideks�w
		int i = eMS->GetU()->GetIndex();	//Odczytaj indeks U
		int j = eMS->GetV()->GetIndex();	//Odczytaj indeks V

		//Ustawienie wska�nik�w M. S�siedztwa na nullptr
		this->MSasiedztwa->operator()(i, j) = nullptr;	//Ustaw wska�nik w polu (i ,j)
		this->MSasiedztwa->operator()(j, i) = nullptr;	//Jako, �e nieskierowany, to ten sam wska�nik w (j, i)

		//ustawienie u i v na null
		eMS->SetU(nullptr);
		eMS->SetV(nullptr);

		//Usu� e z l. kraw�dzi i usuni�cie pozycji
		MIterator<EdgeMS<T>*> q(eMS->GetPos());
		this->edgeList.Erase(q);
		eMS->SetPos(nullptr);

		//usuni�cie e
		delete eMS;
	}
	else
	{
		std::cout << "Nieudany cast." << std::endl;
	}
}

template<typename T>
void GrafMS<T>::Generate(int n, double p)
{
	std::random_device rd; // losowa liczba z systemu
	std::mt19937 eng(rd()); // seedujemy generator
	std::uniform_real_distribution<double> distr(0, 1); //ustalamy granice

	for (int i = 0; i < n; i++)
	{
		this->InsertVertex(new VertexMS<T>(i));
	}

	MIterator<VertexMS<T>*> a = this->vertexList.Begin();
	for (int i = 0; i < this->vertexList.Size(); i++) {
		MIterator<VertexMS<T>*> q = this->vertexList.Begin();
		for (int j = 0; j < this->vertexList.Size(); j++)
		{
				double lb = distr(eng);
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
