#pragma once
#include "Lista.h"

class IVertex;

//Interface do klas krawêdzi
class IEdge {
public:
	virtual MLista<IVertex*> EndVerticies() = 0;	//Zwraca liste z wierzcho³kami kocowymi
	virtual IVertex* Opposite(IVertex*) = 0;	//Zwraca wierzcho³ek s¹siaduj¹cy z podanym
	virtual bool IsAdjecentTo(IEdge*) = 0;		//Sprawdza, czy jest s¹siednia z inn¹ krawêdzi¹
	virtual bool isIncidentOn(IVertex*) = 0;	//Sprawdza, czy wierzcho³ek jest incydenty do krawêdzi
	virtual double GetWaga() = 0;	//Zwraca wage
};