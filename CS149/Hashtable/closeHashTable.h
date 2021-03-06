#pragma once
#include"HashTable.h"
template <class Type>
class closeHashTable :public hashtable<Type>
{
private:
	struct node
	{
		Type data;
		int state;

		node() { state = 0; }
	};
	node* array;
	int size;
public:
	closeHashTable(int length = 101, int(*f)(const Type& x) = defaultKey);
	~closeHashTable() { delete[]array; }
	bool find(const Type& x)const;
	bool insert(const Type& x);
	bool remove(const Type& x);
	void rehash();
	bool insert2(const Type& x, int& count)
	{
		count = 0;
		int initPos, pos;
		initPos = pos = key(x) % size;
		do {
			++count;
			if (array[pos].state != 1) {
				array[pos].data = x;
				array[pos].state = 1;
				return true;
			}
			if (array[pos].state == 1 && key(array[pos].data) == key(x))
				return true;
			pos = (pos + 1) % size;
		} while (pos != initPos);
		return false;
	}
};
template<class Type>
closeHashTable<Type>::closeHashTable(int length, int(*f)(const Type& x))
{
	size = length;
	array = new node[size];
	key = f;
}
template<class Type>
bool closeHashTable<Type>::insert(const Type& x)
{
	int initPos, pos;

	initPos = pos = key(x) % size;
	do {
		if (array[pos].state != 1) {
			array[pos].data = x;
			array[pos].state = 1;
			return true;
		}
		if (array[pos].state == 1 && key(array[pos].data) == key(x))
			return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);
	return false;
}
template<class Type>
bool closeHashTable<Type>::find(const Type & x) const
{
	int initPos, pos;

	initPos = pos = key(x) % size;
	do {
		if (array[pos].state == 1) return false;
		if (array[pos].state == 1 && key(array[pos].data) == key(x))
			return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);
	return false;
}
template<class Type>
bool closeHashTable<Type>::remove(const Type & x)
{
	int initPos, pos;

	initPos = pos = key(x) % size;
	do {
		if (array[pos].state == 1) return false;
		if (array[pos].state == 1 && key(array[pos].data) == key(x))
		{
			array[pos].state = 2; return true;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);
	return false;
}
template<class Type>
void closeHashTable<Type>::rehash()
{
	node* tmp = array;
	array = new node[size];
	for (int i = 0; i < size; ++i)
	{
		if (tmp[i].state == 1)insert(tmp[i].data);
	}
	delete[]tmp;
}
