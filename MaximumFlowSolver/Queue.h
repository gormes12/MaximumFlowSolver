#pragma once
#include "LinkedList.h"
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
	Node<T>* m_Head;
	Node<T>* m_Tail;

public:
	Queue();
	~Queue();
	void MakeEmpty();
	bool IsEmpty();
	void EnQueue(T i_Item);
	T DeQueue();
	void Print();
};

template<class T>
Queue<T>::Queue()
{
	m_Head = new Node<T>;
	m_Tail = m_Head;
}

template<class T>
Queue<T>::~Queue()
{
	MakeEmpty();
}

template<class T>
void Queue<T>::MakeEmpty()
{
	Node<T>* temp = m_Head->DeleteAfterAndReturnIt();
	while (temp != nullptr)
	{
		delete temp;
		temp = m_Head->DeleteAfterAndReturnIt();
	}

	delete m_Head;
}

template<class T>
bool Queue<T>::IsEmpty()
{
	return (m_Head == m_Tail);
}

template<class T>
void Queue<T>::EnQueue(T i_Item)
{
	Node<T>* newNode = new Node<T>(i_Item);
	m_Tail->InsertAfter(newNode);
	m_Tail = newNode;
}

template<class T>
T Queue<T>::DeQueue()
{
	if (IsEmpty())
	{
		cout << "Error: QUEUE EMPTY\n";
		exit(1);
	}
	else
	{
		Node<T>* temp = m_Head->DeleteAfterAndReturnIt();
		T item = temp->GetData();
		if (m_Tail == temp)
		{
			m_Tail = m_Head;
		}

		delete temp;
		
		return item;
	}
}

template<class T>
void Queue<T>::Print()
{
	if (!this->IsEmpty())
	{
		cout << this->DeQueue();
	}

	while (!this->IsEmpty())
	{
		cout << ", " << this->DeQueue() ;
	}
}
