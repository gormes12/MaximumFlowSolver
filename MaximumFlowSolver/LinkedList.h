#pragma once
// T must be non-pointer (otherwise it won't be deallocated) 

template <class T>
class Node
{
private:
	T m_Data;

public:
	Node();
	Node(T item, Node<T>* ptr = nullptr);
	~Node();
	Node<T> *m_Next;
	Node<T> *DeleteAfterAndReturnIt();
	void InsertAfter(Node<T> *i_NewNode);
	T GetData();
};

template <class T>
class LinkedList
{
private:
	Node<T> *m_Head, *m_Tail;

public:
	LinkedList()
	{
		m_Head = nullptr;
		m_Tail = nullptr;
	}

	~LinkedList();
	void MakeEmpty();
	void Insert(T i_Data);
	bool IsEmpty();
	Node<T>* GetHead();
};

template<class T>
Node<T>* Node<T>::DeleteAfterAndReturnIt()
{
	Node<T>* deletedNode;
	Node<T>* temp = m_Next;

	if (m_Next == nullptr)
	{
		deletedNode = nullptr;
	}
	else
	{
		m_Next = temp->m_Next;
		deletedNode = temp;
	}

	return deletedNode;
}

template <class T>
Node<T>::Node()
{
	m_Next = nullptr;
}

template <class T>
Node<T>::~Node()
{

}

template<class T>
T Node<T>::GetData()
{
	return m_Data;
}

template <class T>
Node<T>::Node(T i_Item, Node<T>* i_Ptr)
{
	m_Data = i_Item;
	m_Next = i_Ptr;
}

template <class T>
void Node<T>::InsertAfter(Node<T>* i_NewNode)
{
	i_NewNode->m_Next = m_Next;
	m_Next = i_NewNode;
}

template <class T>
void LinkedList<T>::Insert(T i_Data)
{
	if (!m_Head)   // The list is empty
	{
		m_Head = new Node<T>(i_Data);
		m_Tail = m_Head;
	}
	else // The list isn't empty
	{
		if (m_Tail == m_Head)   // The list has one element
		{
			m_Tail = new Node<T>(i_Data);
			m_Head->m_Next = m_Tail;
		}
		else  // The list has more than one element
		{
			Node<T>* newNode = new Node<T>(i_Data);
			m_Tail->m_Next = newNode;
			m_Tail = newNode;
		}
	}
}

template<class T>
bool LinkedList<T>::IsEmpty()
{
	bool isEmpty;

	if (m_Head == nullptr)
	{
		isEmpty = true;
	}
	else
	{
		isEmpty = false;
	}

	return isEmpty;
}

template<class T>
Node<T>* LinkedList<T>::GetHead()
{
	return m_Head;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	MakeEmpty();
}

template <class T>
void LinkedList<T> ::MakeEmpty()
{
	Node<T>* tempNode;
	Node<T>* currNode = m_Head;

	while (currNode != nullptr)
	{
		tempNode = currNode->m_Next;
		delete currNode;
		currNode = tempNode;
	}

	m_Head = m_Tail = nullptr;
}