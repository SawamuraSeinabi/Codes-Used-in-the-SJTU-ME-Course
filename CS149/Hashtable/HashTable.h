#pragma once
template <class Type>
class hashtable
{
public:
	virtual bool find(const Type& x)const = 0;
	virtual bool insert(const Type& x) = 0;
	virtual bool remove(const Type& x) = 0;
protected:
	int(*key)(const Type& x);
	static int defaultKey(const int& k) { return k; }
};
