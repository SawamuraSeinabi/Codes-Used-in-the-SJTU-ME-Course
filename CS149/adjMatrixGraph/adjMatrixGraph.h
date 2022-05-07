#pragma once
#include "graph.h"
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph :public graph<TypeOfVer, TypeOfEdge> {
public:
	struct EulerNode {
		int NodeNum;
		EulerNode* next;
		EulerNode(int ver)
		{
			NodeNum = ver; next = NULL;
		}
	};
	adjMatrixGraph(int vSize, const TypeOfVer d[],
		const TypeOfEdge noEdgeFlag);
	void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
	void remove(TypeOfVer x, TypeOfVer y);
	bool exist(TypeOfVer x, TypeOfVer y) const;
	~adjMatrixGraph();
	void dfs()const;
	void bfs()const;
	void EulerCircuit(TypeOfVer start);
private:
    TypeOfEdge **edge;            //存放邻接矩阵
	TypeOfVer *ver;               //存放结点值
	TypeOfEdge noEdge;            //邻接矩阵中的无穷的表示值
	int find(TypeOfVer v) const {
		for (int i = 0; i < Vers; ++i)    if (ver[i] == v) return I;
	}
	void dfs(int start, bool visited[])const;
	verNode* clone() const;
	EulerNode* EulerCircuit(int start, EulerNode*& end);
};
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph
(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag)
{
	int i, j;
	Vers = vSize;
	Edges = 0;
	noEdge = noEdgeFlag;
	//存放结点的数组的初始化
	ver = new TypeOfVer[vSize];
	for (i = 0; i < vSize; ++i) ver[i] = d[i];
	//邻接矩阵的初始化
	edge = new TypeOfEdge * [vSize];
	for (i = 0; i < vSize; ++i) {
		edge[i] = new TypeOfEdge[vSize];
		for (j = 0; j < vSize; ++j) edge[i][j] = noEdge;
	}
}
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph()
{
	delete[] ver;
	for (int i = 0; i < Vers; ++i) delete[] edge[i
		delete[] edge;
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
	int u = find(x), v = find(y);
	edge[u][v] = w;
	++Edges;
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
	int u = find(x), v = find(y);
	edge[u][v] = noEdge;
	--Edges;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
	int u = find(x), v = find(y);
	if (edge[u][v] == noEdge) return false;
	else  return true;
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
	bool* visited = new bool[Vers];
	for (int i = 0; i < Vers; ++i) visitedp[i] = false;
	cout << "dfs is:" << endl;
	for (i = 0; i < Vers; ++i)
	{
		if(visited[i]==true continue;
			dfs(i,visited);
			cout<<endl;
	}
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
	cout << ver[start] << '\t';
		visited[start] = true;
		int i = 0;
		while (i < Vers)
		{
			if (edge[start][i] == noEdge) && visited[i] != 0) dfs(i, visited);
			++i;
		}
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
	bool* visited = new bool[Vers];
	int currentNode;
	linkQueue<int> q;
	edgeNode* p;
	for (int i = 0; i < Vers; ++i) visited[i] = false;
	cout << "bfs is:"<< endl;
	for (i = 0; i < Vers; ++i) {
		if (visited[i] == true) continue;
		q.enQueue(i);
		while (!q.isEmpty()) {
			currentNode = q.deQueue();
			if (visited[currentNode] == true) continue;
			cout << ver[currentNode]<< '\t';
			visited[currentNode] = true;
			while (j < Vers) {
				if (edge[currentNode][j] == noEdge) && visited[j] != 0) q.enQueue(j);
				++j;
			}
		}
		cout << endl;
	}
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{
	EulerNode* beg, * end, * p, * q, * tb, * te;
	int numOfDegree;
    //检查是否存在欧拉回路
	for (int i = 0; i < Vers; ++i) {
		numOfDegree = 0;  r = verList[i].head;
		while (r != 0) { ++numOfDegree; r = r->next; }
		if (numOfDegree == 0 || numOfDegree % 2)
		{
			cout << "不存在欧拉回路" << endl;
			return;
		}
	}
	//寻找起始结点的编号
	i = find(start);

	//创建一份邻接表的拷贝
	tmp = clone();
	//寻找从i出发的路径，
    //路径的起点和终点地址分别是beg和end
	beg = EulerCircuit(i, end);
	while (true) {
		p = beg;
		while (p->next != NULL)
			if (verList[p->next->NodeNum].head != NULL) break;
			else p = p->next;
		if (p->next == NULL)  break;
		q = p->next;
		tb = EulerCircuit(q->NodeNum, te);
		te->next = q->next;
		p->next = tb;
		delete q;
	}
	//恢复原图
	delete[] verList;
	verList = tmp;

	//显示得到的欧拉回路
	cout << "欧拉回路是：" << endl;
	while (beg != NULL) {
		cout << verList[beg->NodeNum].ver << '\t';
		p = beg; beg = beg->next;
		delete p;
	}
	cout << endl;
}
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::verNode* adjMatrixGraph<TypeOfVer, TypeOfEdge>::clone() const
{
	verNode* tmp = new verNode[Vers];
	edgeNode* p;

	for (int i = 0; i < Vers; ++i) {
		tmp[i].ver = verList[i].ver;
		p = verList[i].head;
		while (p != NULL) {
			tmp[i].head =
				new edgeNode(p->end, p->weight, tmp[i].head);
			p = p->next;
		}
	}
	return tmp;
}
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerNode* adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode*& end)
{
	EulerNode* beg;
	int nextNode;
	beg = end = new EulerNode(start);
	while (verList[start].head != NULL)
	{
		nextNode = verList[start].head->end;
		remove(start, nextNode);
		remove(nextNode, start);
		start = nextNode;
		end->next = new EulerNode(start);
		end = end->next;
	}
	return beg;
}
