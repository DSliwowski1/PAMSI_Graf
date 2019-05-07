#pragma once
#include <iostream>
#include "GrafLS.h"
#include "GrafMS.h"
#include "Dijkstra.h"
#include <chrono>
#include <fstream>
//#include <Windows.h>

void Test(int ilosc, int* n, double* p)
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<double> duration;

	std::fstream file1;
	std::fstream file2;
	file1.open("GrafMS_tests10.csv", std::fstream::app | std::fstream::out );

	//Dla ka¿dej pary ilosæ wierzcho³ków i gêsotœci wygeneruj 'iloœæ' instancji, oblicz najkrótsze scie¿ki
	//pomiedzy ka¿dym wierzcho³kiem a zerowym
	for(int i=0; i<5; i++)
		for (int j = 0; j < 5; j++)
		{
			
			for (int x = 0; x < ilosc; x++)
			{
				std::cout << "x: " << x << std::endl;

				GrafMS<int>* t = new GrafMS<int>;
				t->Generate(n[i], p[j]);
			
				std::cout << "Wygenerowalem" << std::endl;

				MIterator<IVertex*> z = t->Vertices().Begin();
				MLista<IVertex* > vert = t->Vertices();
				MIterator<IVertex *> q = vert.Begin();

				start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < vert.Size(); ++i)
				{
					Dijkstra(t, z.GetNode()->GetElem(), q.GetNode()->GetElem());
					++q;
				}
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;

				//Zapisz wynik
				file1 << n[i] << "_" << p[j] << ";" << duration.count() << endl;
				delete t;
			}
	//		Beep(500, 1000);
			std::cout << "Skonczylem dla n i p: " << n[i] << " " << p[j] << std::endl;
		}
	file1.close();
//	file2.close();
}