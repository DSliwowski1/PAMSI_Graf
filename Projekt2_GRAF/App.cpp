#include "Iterator.h"
#include "Lista.h"
#include <iostream>
#include "EdgeLS.h"
#include "VertexLS.h"
#include "GrafLS.h"

#include "GrafMS.h"
#include "VertexMS.h"
#include "EdgeMS.h"

#include "Distance.h"
#include "Heap_Dis.h"
#include "Dijkstra.h"

#include "ObsIO.h"

#include <chrono>

#include "Test.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char**argv){
	

	IGraf* t = nullptr;
	IVertex* start=nullptr;
	zadanie* z = nullptr;

	//Wczytaj
	z = Wczytaj();

	if (z->wynikg == nullptr)
	{
		cin.get();
		cin.get();
		cin.get();
		return -1;
	}

	t = z->wynikg;
	start = z->start;


	std::string fname;

	cout << "Podaj nazwe pliku do ktorego chcesz zapisac" << endl;
	cin >> fname;

	//otwarcie pliku zapisu
	std::fstream file(fname, std::fstream::out);

	//Wykonaj test dla ka¿dego i zapisane do pliku
	MLista<IVertex* > vert = t->Vertices();
	MLista<wynik*> wyniki;
	MIterator<IVertex *> q = vert.Begin();

	for (int i = 0; i < vert.Size(); ++i)
	{

		wynik w = Dijkstra(t, start, q.GetNode()->GetElem());
		wyniki.AddFront(&w);

		file << w << endl;

		++q;
	}

	//usuniêcie zaalokowanej pamiêci
	delete t;
	delete start;
	file.close();

	cin.get();
	cin.get();

}