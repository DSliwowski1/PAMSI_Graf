#pragma once
#include "Lista.h"
#include "IEdeg.h"
#include "IVertex.h"

//Interface do klas Grafów
class IGraf { 
public:
	virtual MLista<IVertex* > Vertices() = 0;		//Zwraca liste wierzcho³ków
	virtual MLista<IEdge* > Edges() = 0;			//Zwraca listê krawêdzi
	virtual IVertex* InsertVertex(IVertex*) = 0;	//Dodaje wierzcho³ek
	virtual IEdge* InsertEdge(IVertex*, IVertex*, double) = 0;	//Dodje krawêdŸ
	virtual void RemoveVertex(IVertex*) = 0;	//Usuwa wierzcho³ek
	virtual void RemoveEdge(IEdge*) = 0;		//Usuwa krawedŸ
	virtual void Generate(int, double) = 0;		//Tworzy losowy graf
};