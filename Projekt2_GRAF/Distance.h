#pragma once
#include "IVertex.h"

#define INF 99999999

class Dis 
{
private:
	IVertex* vert;
	double dis;
	IVertex* via;
public:
	IVertex* GetVertex() { return vert; }
	IVertex* GetVia() { return via; }
	double GetDis() { return dis; }

	void SetVertex(IVertex* a) { vert = a; }
	void SetVia(IVertex* a) { via = a; }
	void SetDis(double a) { dis = a; }
};