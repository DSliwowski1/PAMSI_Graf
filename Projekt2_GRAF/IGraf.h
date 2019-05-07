#pragma once
#include "Lista.h"
#include "IEdeg.h"
#include "IVertex.h"

//Interface do klas Graf�w
class IGraf { 
public:
	virtual MLista<IVertex* > Vertices() = 0;		//Zwraca liste wierzcho�k�w
	virtual MLista<IEdge* > Edges() = 0;			//Zwraca list� kraw�dzi
	virtual IVertex* InsertVertex(IVertex*) = 0;	//Dodaje wierzcho�ek
	virtual IEdge* InsertEdge(IVertex*, IVertex*, double) = 0;	//Dodje kraw�d�
	virtual void RemoveVertex(IVertex*) = 0;	//Usuwa wierzcho�ek
	virtual void RemoveEdge(IEdge*) = 0;		//Usuwa krawed�
	virtual void Generate(int, double) = 0;		//Tworzy losowy graf
};