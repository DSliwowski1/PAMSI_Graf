#pragma once
#include "Array.h"
#include "Distance.h"
#include <iostream>

class Heap_dis {
private:
	int size;
	int index;
	Array<Dis> heap;
public:
	Heap_dis(int a){
		index = 0;
		size = a;
		heap = Array<Dis>(size);
	}
public:
	void Heapify();
	void ShiftDown(int start, int end);
	Dis RemoveMin();
	bool IsEmpty();
private:
	int IdxParent(int child) { int tmp = floor((child - 1) / 2); return tmp; }
	int IdxChildL(int root) { int tmp = 2 * root + 1; return tmp; }
	int IdxChildR(int root) { int tmp = 2 * root + 2; return tmp; }
public:
	Array<Dis>& Heap() { return this->heap; }
	int GetSize() { return this->size; }
	int GetIndex() { return this->index; }

};


void Heap_dis::Heapify()
{
	int last = this->size - 1 - this->index;
	int start = this->index + this->IdxParent(last);	         //Zacznij od rodzica ostatiego elementu ostatniego elementu

	while (start >= this->index)
	{
		Heap_dis::ShiftDown(start, this->index + last);   //Przesu� w�ze� start w d�l, tak aby spe�nia� w�a�ciwo�ci kopca
		--start;                                             //Przeskocz na nast�pny element i powt�rz
	}
}

void Heap_dis::ShiftDown(int start, int end)
{
	int root = start;

	while ((this->IdxChildL(root) - this->index) <= end)       //Je�eli istnieje potomek
	{
		int child = this->IdxChildL(root) - this->index;
		int swap = root;	                                 //Zak�adamy, �e root wymaga zmiany z samym sob�

		if (this->heap[swap].GetDis() >= this->heap[child].GetDis())                          //Je�eli swap jest mniejszy od potomka, to zapami�taj indeks potomka do zmiany
			swap = child;	                                 //W tym momencie po zmianie swap bedzie nowym rootem, wi�c nale�y sprawdzi�:

		if (child + 1 <= end)                                //Je�eli istnieje prawy potomek sprawd�, czy jego warto�� nie jest wi�ksza od swap, je�li jest, to zapami�taj
			if (this->heap[swap].GetDis() >= this->heap[child + 1].GetDis())
				swap = child + 1;
		if (swap == root)                                    //Je�eli root od zawsze byl najwi�kszym elementem
			return;
		else {
			this->heap.Swap(root, swap);                            //Wstaw element na w�a�ciwe miejsce
			root = swap;	                                 //Kontynuj sprawdzanie w do�
		}
	}
}

inline Dis Heap_dis::RemoveMin()
{
	if (this->index <this->size)
	{
		index++;	//Presu� indeks o 1
		return this->heap[index - 1];	//Zwr�� element sprzed przesuni�cia
	}
	else
	{
		std::cout << "Nie ma wiecej element�w w kopcu" << std::endl;
	}

}

bool Heap_dis::IsEmpty()
{
	if (this->index >= this->size || this->size == 0)
		return true;
	else
		return false;
}