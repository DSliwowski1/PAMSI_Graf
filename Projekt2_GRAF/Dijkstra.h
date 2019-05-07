#pragma once
#include "IGraf.h"
#include "IVertex.h"
#include "IEdeg.h"
#include "Lista.h"
#include "Heap_Dis.h"
#include <iostream>

//Struktura przechowuj¹ca wynik
struct Wynik
{
	MLista<IVertex*> trasa;
	double droga;
};

typedef struct Wynik wynik;

wynik Dijkstra(IGraf* g, IVertex* start, IVertex* end)
{
	MLista<IVertex*> vertecies = g->Vertices();		//Macierz wierzcho³ków
	Heap_dis D(vertecies.Size());	//Kopiec o rozmiarze macierzy wieszcho³ków, przechowuj¹cy elementy wi¹¿ce odleg³oœæ z wierzcho³kiem
	wynik w;

	//Jele¿i elementy nie maj¹ krawêdzi oznacza to, ¿e nie ma miêdzy nimi drogi
	if (start->IncidentEdges().IsEmpty() || end->IncidentEdges().IsEmpty())
	{
		w.droga = -1;
		return w;
	}

	//Przypisanie ka¿demu elementowi kopca w³asnego wierzcho³ka
	MIterator<IVertex* > p = vertecies.Begin();
	for (int i = 0; i < vertecies.Size(); i++)
	{
		D.Heap()[i].SetVertex(p.GetNode()->GetElem());
		if (p.GetNode()->GetElem() != start) {
			D.Heap()[i].SetDis(INF);	//je¿eli wiercho³ek jest inni ni¿ start  to ustawiamy jego odleg³oœæ na nieskoñczonoœæ
		}
		else
		{
			D.Heap()[i].SetDis(0);	//jak jest startowym to na 0
		}
		D.Heap()[i].SetVia(nullptr);	//Ka¿dy wierzcholek nie ma poprzednika w dodze
		++p;
	}

	while (!D.IsEmpty())	//Do czasu a¿ kopiec nie jest pusty
	{
		D.Heapify();	//Utwórz kopiec

		
		Dis elem = D.RemoveMin();	//Usuñ element minimalny z kopca
	
		IVertex* tmpv = elem.GetVertex();

		MLista<IEdge*> tmpe = tmpv->IncidentEdges();	//krawêdzie  wychodz¹ce z usuniêtego wierzchoka
		MIterator<IEdge*> q = tmpe.Begin();
		for (int i = 0; i < tmpe.Size(); i++)	//Dla ka¿dej krawêdzi wychodz¹cej
		{
			IVertex* opposit = q.GetNode()->GetElem()->Opposite(tmpv);	//WeŸ wierzho³ek s¹siaduj¹cy
				
			for	(int j = D.GetIndex(); j < D.GetSize(); j++)	//Wyszukaj go w aktualnym kopu (pomiedzy indeks a size)
			{
				if (D.Heap()[j].GetVertex() == opposit)	//Je¿eli ten element jest w kopcu
				{
					if (elem.GetDis() + q.GetNode()->GetElem()->GetWaga() < D.Heap()[j].GetDis()) {	//Jezeli odleg³oœc przez ten wierzho³ek jest mniejsza
						D.Heap()[j].SetDis(elem.GetDis() + q.GetNode()->GetElem()->GetWaga());	//Uaktualnij odleg³oœæ
						D.Heap()[j].SetVia(tmpv);	//Ustaw wierzho³ek przek ktory przechodziliœmy
					}
				}
			}
			++q;
		}
	
		if (elem.GetVertex() == end)	//Je¿eli elementem minialnym jest wierzho³ek koñcowy
		{
			Dis tmp = elem;
			do
			{
				w.trasa.AddFront(tmp.GetVertex());		//dodaj do trasy
				for (int i = 0; i < D.GetSize(); i++)	//znajdŸ element DIS z wierzcho³kiem przez który przechodziliœmy
					if (D.Heap()[i].GetVertex() == tmp.GetVia())	
						tmp = D.Heap()[i];	//Je¿eli znalaz³eœ ustaw podmieñ go
			} while (tmp.GetVertex() != start);	//Rób dopoki nie dojdzimy do startowego
			w.trasa.AddFront(start);	//Dodaj startowy
			w.droga = elem.GetDis();	//Ustaw odleg³oœæ

			return w;
		}
	}
}


std::ostream& operator <<(std::ostream& wyj, wynik w)
{
	MIterator<IVertex*> p = w.trasa.Begin();

	wyj << "Najkrotsza sciezka: ";
	for (int i = 0; i < w.trasa.Size(); ++i)
	{
		p.GetNode()->GetElem()->Print(wyj);
		wyj << "->";
		++p;
	}
	wyj << std::endl << "Droga: " << w.droga << std::endl;

	return wyj;
}