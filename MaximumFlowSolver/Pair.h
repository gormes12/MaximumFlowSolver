#pragma once

typedef int DataType;
typedef int KeyType;

class Pair
{
private:
	DataType m_Data;
	KeyType m_Key;

public:
	Pair();
	Pair(DataType i_Data, KeyType i_Key);
	~Pair();
	KeyType GetKey();
	DataType GetData();
	void SetKey(KeyType i_NewKey);
	void SetData(DataType i_NewData);
};