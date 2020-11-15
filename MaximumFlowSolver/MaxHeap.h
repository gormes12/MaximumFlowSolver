#pragma once
#include "Pair.h"
#include <iostream>
using namespace std;

typedef Pair Type;

class MaxHeap {
private:
	Type* m_Data; //points to data array
	int* m_IndexPlaceInHeapArray; 
	int m_MaxSizeOfHeap; //Max size of heap
	int m_CurrentHeapSize; //Current size of heap
	bool m_Allocated;
	void FixHeap(int i_Node);
	int GetLeftChildIndex(int i_Node);
	int GetRightChildIndex(int i_Node);
	int GetParentIndex(int i_Node);
public:
	MaxHeap(int i_MaxSize); //Allocate memory
	MaxHeap(Type* A, int i_Size);
	~MaxHeap();
	void Build(Type* A, int i_Size); //Turn A[] into heap
	void Insert(Type i_Item);
	void IncreaseKey(int i_IndexPlace, int i_NewKey);
	bool IsEmpty();
	int GetIndexPlaceInHeap(int i_Node);
	Type Max();
	Type DeleteMax();
};
