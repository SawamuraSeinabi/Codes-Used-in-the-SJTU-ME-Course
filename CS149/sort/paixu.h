#pragma once
#include"set.h"
template <class KEY, class OTHER>
void simpleInsertSort(SET<KEY, OTHER> a[], int size)
{
	int k;
	SET<KEY, OTHER> tmp;
	for (int j = 1; j < size; ++j) {
		tmp = a[j];
		for (k = j - 1; tmp.key < a[k].key && k >= 0; --k)
			a[k + 1] = a[k];
		a[k + 1] = tmp;
	}
}
template <class KEY, class OTHER>
void binaryInsertSort(SET<KEY, OTHER> a[], int size)
{
	int k;
	SET<KEY, OTHER>tmp;
	int i = 0;
	for (int j = 1; j < size; ++j)
	{
		tmp = a[j];
		k = j - 1;
		while (i <= k) {
			int mid = (i + k) / 2;
			if (a[j].key < a[mid].key) j = mid - 1;
			else if (a[j].key > a[mid].key)j = mid + 1;
			else if (a[j].key == a[mid].key) break;
		}
		for (k = j - 1; tmp.key < a[k].key && k >= 0; --k)
			a[k + 1] = a[k];
		a[k + 1] = tmp;
	}
}
