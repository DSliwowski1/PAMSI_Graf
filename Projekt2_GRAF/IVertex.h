#pragma once
#include "IEdeg.h"
#include <iostream>

class IEdge;

//Interface do klas wierzcho³ków
 class IVertex {
 public:
	 virtual MLista<IEdge*> IncidentEdges() = 0; //Lista krawêdzi incydentnych do wierzcho³ka
	 virtual bool isAdjacentTo(IVertex*) = 0;   //Zwraca czy v jest s¹siednie
	 virtual void Print(std::ostream&) = 0;
 };

