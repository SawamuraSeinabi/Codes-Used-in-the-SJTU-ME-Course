#pragma once
template<class KEY,class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};
/*template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY& x)
{
	data[0].key = x;
	for (int i = size; x != data[i].key; --i);
	return i;
}
template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER> data[], int size, const KEY & x)
{
	data[0].key = x;
	for (int i = size; x < data[i].key; --i);
	if (x == data[i].key) return i;
	else return 0;
}
template <class KEY, class OTHER>
int binarySearch(SET<KEY, OTHER> data[], int size, const KEY& x, int low = 1)
{
	int high = size, mid = (low + high) / 2;
	do
	{
        if (x == data[mid].key)  return mid;
		if (x < data[mid].key) binarySearch(SET<KEY, OTHER> data[], int mid, const KEY & x, 1);
		if (x > data[mid].key) binarySearch(SET<KEY, OTHER> data[], int mid, const KEY & x, mid + 1);
	} while (low <= high);    
	return 0;
}*/