#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "HashTable.h"
#include "closeHashTable.h"
int main()
{
	closeHashTable<int>ht(25013);
	int count;
	double avgCountSer = 0;
	int list[10000];

	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		list[i] = rand();
		ht.insert2(list[i], count);
		avgCountSer += count;
	}
	avgCountSer /= 10000;
	cout << "平均探测次数：" << avgCountSer << endl;
	return 0;
}
