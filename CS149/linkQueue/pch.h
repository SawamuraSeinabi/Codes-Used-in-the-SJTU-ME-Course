#ifndef PCH_H
#define PCH_H
#include <cstdio>
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
		node(const elemType &x, node *N = NULL)
		{
			data = x; next = N;
		}
		node() :next(NULL) {}
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
	front = rear = NULL;
}
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear == NULL)
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
	if (front == NULL) rear = NULL;
	delete tmp;
	return value;
}
template <class elemType>
bool linkQueue<elemType>::isEmpty()
{
	return front == NULL;
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
	while (front != NULL)
	{
		tmp = front;
		front = front->next;
		delete tmp;
	}
}
#endif //PCH_H
