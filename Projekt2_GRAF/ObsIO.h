#pragma once
#include <iostream>
#include "IGraf.h"
#include <string>
#include <fstream>
#include "Dijkstra.h"

using std::cout;
using std::cin;
using std::endl;

//Struktura do kuórej czytamy
struct Zadanie
{
	IGraf* wynikg=nullptr;
	IVertex* start = nullptr;
};

typedef Zadanie zadanie;

//Wczytaj graf do g
zadanie* Wczytaj()
{
	//Pomocncze zmienne
	int b;
	int param[3];
	std::string fname;
	std::string buffer;
	IGraf* wynikg = nullptr;
	IVertex* startowy = nullptr;
	zadanie wynikz;
	cout << "Wybierz reperezentajce" << endl;
	cout << "0 - lista sasiedztwa \n1 - macierz sasiedztwa" << endl;
	cin >> b;

	//Stworzernie grafu
	switch (b)
	{
	case 0:
		wynikg = new GrafLS<double>;
		break;
	case 1:
		wynikg = new GrafMS<double>;
		break;
	default:
		cout << "Z³y wybór" << endl;
		break;
	}

	cout << "Podaj nazwe pliku z ktorego chcesz wczytac" << endl;
	cin >> fname;

	//otwarcie pliku
	std::ifstream file(fname);

	if (!file.good())
	{
		std::cout << "Nie ma takiego pliku" << endl;
		return &wynikz;
	}

	//wczytanie lini z parametrami grafu
	if (std::getline(file, buffer))
	{
		int i = 0;
		std::string slowo = "";

		for (char x : buffer)
		{
			if (x == '\t')
			{
				param[i] = std::atoi(slowo.c_str());
				i++;
				slowo = "";
			}
			else
				slowo = slowo + x;
		}
		param[i] = std::atoi(slowo.c_str());

		//Utworzenie wierzcho³ków
		for (int i = 0; i < param[1]; i++)
		{
			switch (b)
			{
			case 0:
				wynikg->InsertVertex(new VertexLS<double>(i));
				break;
			case 1:
				wynikg->InsertVertex(new VertexMS<double>(i));
				break;
			default:
				cout << "Z³y wybór" << endl;
				break;
			}
		}
	}

	//Ustawienie wierzcho³ka startowego
	if (b == 0)//GrafLS
	{
		MLista<IVertex*> verts = wynikg->Vertices();
		MIterator<IVertex*> p = verts.Begin();

		VertexLS<double>* tmpv1 = dynamic_cast<VertexLS<double>*>(p.GetNode()->GetElem());
		
		while (tmpv1->GetElem() != param[2])	//Szukaj wierzcho³ka a¿ nie znajdziesz zadanego
		{
			tmpv1 = dynamic_cast<VertexLS<double>*>(p.GetNode()->GetElem());
			++p;
		}
		startowy = tmpv1;
	}
	else if (b == 1) //GrafMS
	{
		MLista<IVertex*> verts = wynikg->Vertices();
		MIterator<IVertex*> p = verts.Begin();

		VertexMS<double>* tmpv1 = dynamic_cast<VertexMS<double>*>(p.GetNode()->GetElem());

		while (tmpv1->GetElem() != param[2]) //Szukaj wierzcho³ka a¿ nie znajdziesz zadanego
		{
			tmpv1 = dynamic_cast<VertexMS<double>*>(p.GetNode()->GetElem());
			++p;
		}
		startowy = tmpv1;
	}

	//Tworzenie krawêdzi
	while (std::getline(file, buffer))
	{
		double edge[3];
		int i = 0;
		std::string slowo = "";
		//Czytanie lini i zapisywanie parametrów
		for (char x : buffer)
		{
			if (x == '\t')
			{
				edge[i] = std::atoi(slowo.c_str());
				i++;
				slowo = "";
			}
			else
				slowo = slowo + x;
		}
		edge[i] = std::atoi(slowo.c_str());

		//Tworzenie krawêdzi
		if (b == 0) //Lista S¹siedztwa
		{
			MLista<IVertex*> verts = wynikg->Vertices();
			MIterator<IVertex*> p = verts.Begin();
			MIterator<IVertex*> q = verts.Begin();


			VertexLS<double>* tmpv1 = dynamic_cast<VertexLS<double>*>(p.GetNode()->GetElem());
			VertexLS<double>* tmpv2 = dynamic_cast<VertexLS<double>*>(q.GetNode()->GetElem());

			//Szunakie pocz¹tkowaej
			while(tmpv1->GetElem() != edge[0])
			{
				tmpv1 = dynamic_cast<VertexLS<double>*>(p.GetNode()->GetElem());
				++p;
			}
			//Szukanie koñcowej
			while (tmpv2->GetElem() != edge[1])
			{
				tmpv2 = dynamic_cast<VertexLS<double>*>(q.GetNode()->GetElem());
				++q;
			}
			//Utwirzenie	
			wynikg->InsertEdge(tmpv1, tmpv2, edge[2]);	
		}
		else if (b == 1) //GrafMS
		{
			MLista<IVertex*> verts = wynikg->Vertices();
			MIterator<IVertex*> p = verts.Begin();
			MIterator<IVertex*> q = verts.Begin();


			VertexMS<double>* tmpv1 = dynamic_cast<VertexMS<double>*>(p.GetNode()->GetElem());
			VertexMS<double>* tmpv2 = dynamic_cast<VertexMS<double>*>(q.GetNode()->GetElem());
			//Szukanie pierwszej
			while (tmpv1->GetElem() != edge[0])
			{
				tmpv1 = dynamic_cast<VertexMS<double>*>(p.GetNode()->GetElem());
				++p;
			}
			//Szukanie drugej
			while (tmpv2->GetElem() != edge[1])
			{
				tmpv2 = dynamic_cast<VertexMS<double>*>(q.GetNode()->GetElem());
				++q;
			}
			//Wstawienie
			wynikg->InsertEdge(tmpv1, tmpv2, edge[2]);
		}
		else
		{
			cout << "Z³y wybór" << endl;
		}
		
		
		
	}

	wynikz.start = startowy;
	wynikz.wynikg = wynikg;
	return &wynikz;
}


