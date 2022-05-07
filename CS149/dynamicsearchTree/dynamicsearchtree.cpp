#include <iostream>
using namespace std;
#include "set.h"
#include "dynamicsearchtree.h"
int main()
{
	SET<int,char*> a[] = { {10,(char*)"aaa"}, {8,(char*)"bbb"}, {21,(char*)"ccc"},{87,(char*)"ddd"},{56,(char*)"eee"},  {4,(char*)"fff"}, {11,(char*)"ggg"}, {3,(char*)"hhh"}, {22,(char*)"iiiii"}, {7,(char*)"jjj"} };
	BinarySearchTree<int, char*>  tree;
	SET<int,char*> x;
	SET<int,char*>* p;
	SET<int, char*>* y;
	for (int i = 0; i < 10; ++i) tree.insert(a[i]);
    p = tree.find(56);


	if (p) cout << "find 56 is " << p->key << "  " << p->other << endl;
	else cout << "not found" << endl;
	tree.remove(56);
	p = tree.find(56);
	if (p) cout << "find 56 is " << p->key << "  " << p->other << endl;
	else cout << "not found" << endl;

	p = tree.find(21);
	if (p) cout << "find 21 is " << p->key << "  " << p->other << endl;
	else cout << "not found" << endl;
	tree.remove(21);
	p = tree.find(21);
	if (p) cout << "find 21 is " << p->key << "  " << p->other << endl;
	else cout << "not found" << endl;

	x.key = 30; x.other = (char*)"xyz";
	tree.insert(x);
	p = tree.find(30);
	if (p) cout << "find 30 is " << p->key << "  " << p->other << endl;
	else cout << "not found" << endl;
	char *xx;
	xx = tree.findmax();
	return 0;
}
