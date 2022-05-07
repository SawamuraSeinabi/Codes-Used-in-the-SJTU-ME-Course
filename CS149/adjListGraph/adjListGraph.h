#pragma once
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph :public graph<TypeOfVer, TypeOfEdge>
{
public:
	adjListGraph(int vSize, const TypeOfVer d[]);
	void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w);
	void remove(TypeOfVer x, TypeOfVer y);
	bool exist(TypeOfVer x, TypeOfVer y) const;
	~adjListGraph();
	template <class TypeOfVer, class TypeOfEdge>
	template <class TypeOfVer, class TypeOfEdge>
	void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
	{
		bool* visited = new bool[Vers];

		for (int i = 0; i < Vers; ++i) visited[i] = false;

		cout << "当前图的深度优先遍历序列为：" << endl;
		for (i = 0; i < Vers; ++i) {
			if (visited[i] == true) continue;
			dfs(i, visited);
			cout << endl;
		}
	}
	template <class TypeOfVer, class TypeOfEdge>
	bool adjListGraph<TypeOfVer, TypeOfEdge>::Road(TypeOfVer start, TypeOfVer end) const
	{
		bool* visited = new bool[Vers];

		for (int i = 0; i < Vers; ++i) visited[i] = false;
		int start1, end1;
		for (start1 = 0; start1 < Vers; ++start1) {
			if verList[start1].ver == start) int startx = start1;
		}
		for (end1 = 0; end1 < Vers; ++end1) {
			if verList[end1].ver == start) int endx = end1;
		}
		return Road(startx, endx, visited);
	}
	bool adjListGraph<TypeOfVer, TypeOfEdge>::DAG() const
	{
		bool* visited = new bool[Vers];
		bool flag;
		for (int i = 0; i < Vers; ++i) visited[i] = false;

		for (i = 0; i < Vers; ++i) {
			flag=DAG(i, visited);
			if (flag = false) return false;
		}
		return true;
	}
private:
	struct edgeNode {                   //邻接表中存储边的结点类
		int end;                          //终点编号
		TypeOfEdge weight;                //边的权值
		edgeNode* next;

		edgeNode(int e, TypeOfEdge w, edgeNode* n = NULL)
		{
			end = e; weight = w; next = n;
		}
	};
	struct verNode {                     //保存顶点的数据元素类型
		TypeOfVer ver;                   //顶点值
		edgeNode* head;                 //对应的单链表的头指针 verNode *verList;
		verNode(edgeNode* h = nullptr)
		{
			head = h;
		}
	};
	verNode* verList;
	int find(TypeOfVer v) const
	{
		for (int i = 0; i < Vers; ++i)
			if (verList[i].ver == v) return i;
	}
	template <class TypeOfVer, class TypeOfEdge>
	void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
	{
		edgeNode* p = verList[start].head;
		cout << verList[start].ver << '\t';
		visited[start] = true;
		while (p != nullptr) {
			if (visited[p->end] == false) dfs(p->end, visited);
			p = p->next;
		}
	}
	bool adjListGraph<TypeOfVer, TypeOfEdge>::DAG(int start, bool visited[]) const
	{
		edgeNode* p = verList[start].head;
		bool flag;
		visited[start] = true;
		while (p != nullptr) {
			if (visited[p->end] == true) return false;
			else flag = DAG(p->end, visited);
			if (flag != true) return false;
			p = p->next;
		}
	}
	template <class TypeOfVer, class TypeOfEdge>
	bool adjListGraph<TypeOfVer, TypeOfEdge>::Road(int start, int end, bool visited[]) const
	{
		bool x;
		edgeNode* p = verList[start].head;
		visited[start] = true;
		while (p != nullptr) {
			if (visited[p->end] == false)
			{
				flag = Road(p->end, end, visited);
				if (flag == true)return true;
			}
			p = p->next;
		}
		return false;
	}
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge> ::adjListGraph(int vSize, const TypeOfVer d[])
{
	Vers = vSize; Edges = 0;
	verList = new verNode[vSize];
	for (int i = 0; i < Vers; ++i) verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
	int i;
	edgeNode* p;
	for (i = 0; i < Vers; ++i)
		while ((p = verList[i].head) != NULL) {
			verList[i].head = p->next;
			delete p;
		}
	delete[] verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
	int u = find(x), v = find(y);
	verList[u].head = new edgeNode(v, w, verList[u].head);
	++Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
	int u = find(x), v = find(y);
	edgeNode* p = verList[u].head, * q;
	if (p == NULL) return;  //结点u没有相连的边 
	if (p->end == v) {       //单链表中的第一个结点就是被删除的边
		verList[u].head = p->next;
		delete p; --Edges;
		return;
	}
	while (p->next != NULL && p->next->end != v) p = p->next;//查找被删除的边
	if (p->next != NULL) {               //删除
		q = p->next;          p->next = q->next;          delete q;        --Edges;
	}
}
template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
	int u = find(x), v = find(y);
	edgeNode* p = verList[u].head;

	while (p != NULL && p->end != v) p = p->next;
	if (p == NULL) return false; else  return true;
}
