#include "MaxHeap.h"

MaxHeap::MaxHeap(int i_MaxSize) //c'tor - allocate memory for the heap and make it empty
{
	m_Data = new Type[i_MaxSize];
	m_IndexPlaceInHeapArray = new int[i_MaxSize];
	m_MaxSizeOfHeap = i_MaxSize;
	m_CurrentHeapSize = 0;
	m_Allocated = true;
}

MaxHeap::MaxHeap(Type * A, int i_Size)
{
	m_IndexPlaceInHeapArray = new int[i_Size];
	Build(A, i_Size);
}

MaxHeap::~MaxHeap()
{
	if (m_Allocated == true)
	{
		delete[] m_Data;
	}

	m_Data = nullptr;
	delete[] m_IndexPlaceInHeapArray;
}

void MaxHeap::Build(Type* A, int i_Size) //Turn A[] into heap
{
	m_CurrentHeapSize = m_MaxSizeOfHeap = i_Size;

	m_Data = A;
	m_Allocated = false;

	for (int i = 0; i < i_Size; i++)
	{
		m_IndexPlaceInHeapArray[m_Data[i].GetData()] = i;
	}

	for (int i = i_Size / 2 - 1; i >= 0; i--)
		FixHeap(i);
}

Type MaxHeap::Max()
{
	if (m_CurrentHeapSize < 1)
	{
		cout << "Error! EMPTY HEAP!\n";
		exit(1);
	}
	else
		return m_Data[0];
}

Type MaxHeap::DeleteMax()
{
	if (m_CurrentHeapSize < 1)
	{
		cout << "Error! EMPTY HEAP!\n";
		exit(1);
	}

	Type max = m_Data[0];
	m_CurrentHeapSize--;
	m_Data[0] = m_Data[m_CurrentHeapSize];
	m_IndexPlaceInHeapArray[m_Data[m_CurrentHeapSize].GetData()] = 0;
	FixHeap(0);

	return max;
}

void MaxHeap::Insert(Type i_Item)
{
	if (m_CurrentHeapSize == m_MaxSizeOfHeap)
	{
		cout << "Error! FULL HEAP!\n";
		exit(1);
	}

	int index = m_CurrentHeapSize;
	m_CurrentHeapSize++;

	while ((index > 0) && m_Data[GetParentIndex(index)].GetKey() < i_Item.GetKey())
	{
		m_Data[index] = m_Data[GetParentIndex(index)];
		index = GetParentIndex(index);
	}

	m_Data[index] = i_Item;
}


void MaxHeap::IncreaseKey(int i_IndexPlace, int i_NewKey)
{
	if (i_NewKey < m_Data[i_IndexPlace].GetKey())
	{
		cout << "New Key is smaller than current\n";
	}
	else
	{
		int increasedItem = m_Data[i_IndexPlace].GetData();

		m_Data[i_IndexPlace].SetKey(i_NewKey);
		Type item = m_Data[i_IndexPlace];

		while ((i_IndexPlace > 0) && m_Data[GetParentIndex(i_IndexPlace)].GetKey() < item.GetKey())
		{
			swap(m_IndexPlaceInHeapArray[increasedItem], m_IndexPlaceInHeapArray[m_Data[GetParentIndex(i_IndexPlace)].GetData()]);
			m_Data[i_IndexPlace] = m_Data[GetParentIndex(i_IndexPlace)];
			i_IndexPlace = GetParentIndex(i_IndexPlace);
		}

		m_Data[i_IndexPlace] = item;
	}
}

bool MaxHeap::IsEmpty()
{
	bool isEmpty = false;

	if (m_CurrentHeapSize < 1)
	{
		isEmpty = true;
	}

	return isEmpty;
}

int MaxHeap::GetIndexPlaceInHeap(int i_Node)
{
	return m_IndexPlaceInHeapArray[i_Node];
}

int MaxHeap::GetParentIndex(int i_Node)
{
	return (i_Node - 1) / 2;
}

int MaxHeap::GetLeftChildIndex(int i_Node)
{
	return (2 * i_Node + 1);
}

int MaxHeap::GetRightChildIndex(int i_Node)
{
	return (2 * i_Node + 2);
}

void MaxHeap::FixHeap(int i_Node)
{
	int tempMax = i_Node;
	int left = GetLeftChildIndex(i_Node);
	int right = GetRightChildIndex(i_Node);

	if ((left < m_CurrentHeapSize) && (m_Data[left].GetKey() > m_Data[i_Node].GetKey()))
	{
		tempMax = left;
	}

	if ((right < m_CurrentHeapSize) && (m_Data[right].GetKey() > m_Data[tempMax].GetKey()))
	{
		tempMax = right;
	}

	if (tempMax != i_Node)
	{
		swap(m_IndexPlaceInHeapArray[m_Data[i_Node].GetData()], m_IndexPlaceInHeapArray[m_Data[tempMax].GetData()]);
		swap(m_Data[i_Node], m_Data[tempMax]);
		FixHeap(tempMax);
	}
}