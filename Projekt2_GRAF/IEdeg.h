#pragma once
#include "Lista.h"

class IVertex;

//Interface do klas kraw�dzi
class IEdge {
public:
	virtual MLista<IVertex*> EndVerticies() = 0;	//Zwraca liste z wierzcho�kami kocowymi
	virtual IVertex* Opposite(IVertex*) = 0;	//Zwraca wierzcho�ek s�siaduj�cy z podanym
	virtual bool IsAdjecentTo(IEdge*) = 0;		//Sprawdza, czy jest s�siednia z inn� kraw�dzi�
	virtual bool isIncidentOn(IVertex*) = 0;	//Sprawdza, czy wierzcho�ek jest incydenty do kraw�dzi
	virtual double GetWaga() = 0;	//Zwraca wage
};