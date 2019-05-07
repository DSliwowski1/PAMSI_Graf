#pragma once
#include "IGraf.h"
#include "IVertex.h"
#include "IEdeg.h"
#include "Lista.h"
#include "Heap_Dis.h"
#include <iostream>

//Struktura przechowuj�ca wynik
struct Wynik
{
	MLista<IVertex*> trasa;
	double droga;
};

typedef struct Wynik wynik;

wynik Dijkstra(IGraf* g, IVertex* start, IVertex* end)
{
	MLista<IVertex*> vertecies = g->Vertices();		//Macierz wierzcho�k�w
	Heap_dis D(vertecies.Size());	//Kopiec o rozmiarze macierzy wieszcho�k�w, przechowuj�cy elementy wi��ce odleg�o�� z wierzcho�kiem
	wynik w;

	//Jele�i elementy nie maj� kraw�dzi oznacza to, �e nie ma mi�dzy nimi drogi
	if (start->IncidentEdges().IsEmpty() || end->IncidentEdges().IsEmpty())
	{
		w.droga = -1;
		return w;
	}

	//Przypisanie ka�demu elementowi kopca w�asnego wierzcho�ka
	MIterator<IVertex* > p = vertecies.Begin();
	for (int i = 0; i < vertecies.Size(); i++)
	{
		D.Heap()[i].SetVertex(p.GetNode()->GetElem());
		if (p.GetNode()->GetElem() != start) {
			D.Heap()[i].SetDis(INF);	//je�eli wiercho�ek jest inni ni� start  to ustawiamy jego odleg�o�� na niesko�czono��
		}
		else
		{
			D.Heap()[i].SetDis(0);	//jak jest startowym to na 0
		}
		D.Heap()[i].SetVia(nullptr);	//Ka�dy wierzcholek nie ma poprzednika w dodze
		++p;
	}

	while (!D.IsEmpty())	//Do czasu a� kopiec nie jest pusty
	{
		D.Heapify();	//Utw�rz kopiec

		
		Dis elem = D.RemoveMin();	//Usu� element minimalny z kopca
	
		IVertex* tmpv = elem.GetVertex();

		MLista<IEdge*> tmpe = tmpv->IncidentEdges();	//kraw�dzie  wychodz�ce z usuni�tego wierzchoka
		MIterator<IEdge*> q = tmpe.Begin();
		for (int i = 0; i < tmpe.Size(); i++)	//Dla ka�dej kraw�dzi wychodz�cej
		{
			IVertex* opposit = q.GetNode()->GetElem()->Opposite(tmpv);	//We� wierzho�ek s�siaduj�cy
				
			for	(int j = D.GetIndex(); j < D.GetSize(); j++)	//Wyszukaj go w aktualnym kopu (pomiedzy indeks a size)
			{
				if (D.Heap()[j].GetVertex() == opposit)	//Je�eli ten element jest w kopcu
				{
					if (elem.GetDis() + q.GetNode()->GetElem()->GetWaga() < D.Heap()[j].GetDis()) {	//Jezeli odleg�o�c przez ten wierzho�ek jest mniejsza
						D.Heap()[j].SetDis(elem.GetDis() + q.GetNode()->GetElem()->GetWaga());	//Uaktualnij odleg�o��
						D.Heap()[j].SetVia(tmpv);	//Ustaw wierzho�ek przek ktory przechodzili�my
					}
				}
			}
			++q;
		}
	
		if (elem.GetVertex() == end)	//Je�eli elementem minialnym jest wierzho�ek ko�cowy
		{
			Dis tmp = elem;
			do
			{
				w.trasa.AddFront(tmp.GetVertex());		//dodaj do trasy
				for (int i = 0; i < D.GetSize(); i++)	//znajd� element DIS z wierzcho�kiem przez kt�ry przechodzili�my
					if (D.Heap()[i].GetVertex() == tmp.GetVia())	
						tmp = D.Heap()[i];	//Je�eli znalaz�e� ustaw podmie� go
			} while (tmp.GetVertex() != start);	//R�b dopoki nie dojdzimy do startowego
			w.trasa.AddFront(start);	//Dodaj startowy
			w.droga = elem.GetDis();	//Ustaw odleg�o��

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