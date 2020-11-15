#include "Pair.h"


Pair::Pair()
{
	m_Data = 0;
	m_Key = 0;
}

Pair::Pair(DataType i_Data, KeyType i_Key)
{
	m_Data = i_Data;
	m_Key = i_Key;
}

Pair::~Pair()
{
}

KeyType Pair::GetKey()
{
	return m_Key;
}

DataType Pair::GetData()
{
	return m_Data;
}

void Pair::SetKey(KeyType i_NewKey)
{
	m_Key = i_NewKey;
}

void Pair::SetData(DataType i_NewData)
{
	m_Data = i_NewData;
}
