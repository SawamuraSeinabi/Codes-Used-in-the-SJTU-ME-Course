#ifndef PCH_H
#define PCH_H
using namespace std;
// TODO: 添加要在此处预编译的标头
template <class elemType>
class queue
{
public:
	virtual bool isEmpty() = 0;
	virtual void enQueue(const elemType &x) = 0;
	virtual elemType deQueue() = 0;
	virtual elemType getHead() = 0;
	virtual ~queue() {}
};

template <class elemType>
class linkQueue : public queue<elemType>
{
private:
	struct node
	{
		elemType  data;
		node *next;
		node(const elemType &x, node *N = nullptr)
		{
			data = x; next = N;
		}
		node() :next(nullptr) {}
		~node() {}
	};
	node *front, *rear;
public:
	linkQueue();
	~linkQueue();
	bool isEmpty();
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead();
};
template <class elemType>
linkQueue<elemType>::linkQueue()
{
	front = rear = nullptr;
}
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear == nullptr)
		front = rear = new node(x);
	else
		rear = rear->next = new node(x);
}
template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp = front;
	elemType value = front->data;
	front = front->next;
	if (front == nullptr) rear = nullptr;
	delete tmp;
	return value;
}
template <class elemType>
bool linkQueue<elemType>::isEmpty()
{
	return front == nullptr;
}
template <class elemType>
elemType linkQueue<elemType>::getHead()
{
	return front->data;
}
template <class elemType>
linkQueue<elemType>::~linkQueue()
{
	node *tmp;
	while (front != nullptr)
	{
		tmp = front;
		front = front->next;
		delete tmp;
	}
}
template<class T>
class bTree
{
public:
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
	virtual T Root(T flag) const = 0;
	virtual T parent(T x, T flag) = 0;
	virtual T lchild(T x, T flag) = 0;
	virtual T rchild(T x, T flag) = 0;
	virtual void delLeft(T x) = 0;
	virtual void delRight(T x) = 0;
	virtual void preOrder() const = 0;
	virtual void midOrder() const = 0;
	virtual void postOrder() const = 0;
	virtual void levelOrder() = 0;
};
template<class T>
class binaryTree :public bTree<T>
{
	friend void printTree(const binaryTree &t, T flag);
private:
	struct Node {
		Node *left, *right;
		T data;

		Node() :left(nullptr), right(nullptr) {};
		Node(T item, Node *L = nullptr, Node *R = nullptr) :data(item), left(L), right(R) {};
		~Node() {};
	};
	Node *root;//根结点
public:
	binaryTree() :root(nullptr) {};
	binaryTree(T &x) { root = new Node(x); }
	~binaryTree();
	void clear();
	bool isEmpty() const;
	T Root(T flag) const;
	T lchild(T x, T flag);
	T rchild(T x, T flag);
	void delLeft(T x);
	void delRight(T x);
	void preOrder() const;
	void midOrder() const;
	void postOrder() const;

	void levelOrder();
	void createTree(T flag);
	T parent(T x, T flag) { return flag; }

	Node *find(T x, Node *t);
	void clear(Node *&t);
	void preOrder(Node *t) const;
	void midOrder(Node *t) const;
	void postOrder(Node *t) const;
};
template<class T>
bool binaryTree<T>::isEmpty()const
{
	return root == nullptr;
}
template<class T>
T binaryTree<T>::Root(T flag)const
{
	if (root == nullptr) return flag;
	else return root->data;
}
template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t)
{
	if (t == nullptr) return;
	clear(t->left);
	clear(t->right);
	delete t;
	t = nullptr;
}
template<class T>
void binaryTree<T>::clear()
{
	clear(root);
}
template<class T>
binaryTree<T>::~binaryTree()
{
	clear(root);
}
//前
template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t) const
{
	if (t == nullptr) return;
	std::cout << t->data << ' ';
	preOrder(t->left);
	preOrder(t->right);
}
template<class T>
void binaryTree<T>::preOrder() const
{
	std::cout << "\n preOrder:";
	preOrder(root);
}
//后
template<class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const
{
	if (t == nullptr) return;
	postOrder(t->left);
	postOrder(t->right);
	std::cout << t->data << ' ';
}
template<class T>
void binaryTree<T>::postOrder() const
{
	std::cout << "\n postOrder:";
	postOrder(root);
}
//中
template<class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const
{
	if (t == nullptr) return;
	midOrder(t->left);
	std::cout << t->data << ' ';
	midOrder(t->right);
}
template<class T>
void binaryTree<T>::midOrder() const
{
	std::cout << "\n midOrder:";
	midOrder(root);
}

template<class T>
void binaryTree<T>::levelOrder()
{
	linkQueue<Node *> que;
	Node *tmp;

	std::cout << "\n levelOrder:";
	que.enQueue(root);

	while (!que.isEmpty())
	{
		tmp = que.deQueue();
		std::cout << tmp->data << ' ';
		if (tmp->left)que.enQueue(tmp->left);
		if (tmp->right)que.enQueue(tmp->right);
	}
}
template<class T>
typename binaryTree<T>::Node *find(T x, typename binaryTree<T>::Node * t)
{
	typename binaryTree<T>::Node *tmp;
	if (t == nullptr) return nullptr;
	if (t->data == x) return t;
	if (tmp = find(x, t->left)) return tmp;
	else return find(x, t->right);
}
template<class T>
void binaryTree<T>::delLeft(T x)
{
	Node *tmp = find(x, root);
	if (tmp == nullptr) return;
	clear(tmp->left);
}
template<class T>
void binaryTree<T>::delRight(T x)
{
	Node *tmp = find(x, root);
	if (tmp == nullptr) return;
	clear(tmp->right);
}

template<class T>
T binaryTree<T>::lchild(T x, T flag)
{
	Node *tmp = find(x, root);
	if (tmp == nullptr || tmp->left == nullptr) return flag;

	return tmp->left->data;
}
template<class T>
T binaryTree<T>::rchild(T x, T flag)
{
	Node *tmp = find(x, root);
	if (tmp == nullptr || tmp->right == nullptr) return flag;

	return tmp->right->data;
}
template<class T>
void binaryTree<T>::createTree(T flag)
{
	linkQueue<Node *>que;
	Node *tmp;
	T x, ldata, rdata;
	std::cout << "\n type in root:";
	std::cin >> x;
	root = new Node(x);
	que.enQueue(root);

	while (!que.isEmpty())
	{
		tmp = que.deQueue();
		std::cout << "\n type in" << tmp->data << "'s two children(" << flag << " means empty):";
		std::cin >> ldata >> rdata;
		if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
		if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
	}

	std::cout << "create completed!\n";
}
template<class T>
void printTree(const binaryTree<T>&t, T flag)
{
	linkQueue<T> q;
	q.enQueue(t.root->data);
	std::cout << std::endl;
	while (!q.isEmpty())
	{
		char p, l, r;
		p = q.deQueue();
		l = t.lchild(p, flag);
		r = t.rchild(p, flag);
		std::cout << p << " " << l << " " << r << std::endl;
		if (l != '@') q.enQueue(l);
		if (r != '@') q.enQueue(r);
	}
}
#endif //PCH_H
