#pragma once
#include "IEdeg.h"
#include <iostream>

class IEdge;

//Interface do klas wierzcho�k�w
 class IVertex {
 public:
	 virtual MLista<IEdge*> IncidentEdges() = 0; //Lista kraw�dzi incydentnych do wierzcho�ka
	 virtual bool isAdjacentTo(IVertex*) = 0;   //Zwraca czy v jest s�siednie
	 virtual void Print(std::ostream&) = 0;
 };

