#pragma once
#include"virtualQueue.h"

template <typename T>
class linkQueue : public queue<T> {
protected:
	struct node {
		T data;
		node *next;
		node(const T&x, node *n = nullptr)
		{
			data = x;
			next = n;
		}

		node() :next(nullptr) {}
		~node() {}
	};
	node *head, *front, *rear;
	int currentLength;

public:
	linkQueue();
	~linkQueue();
	void clear();
	int length() const { return currentLength; }
	bool isEmpty() { return (currentLength == 0); }
	void enQueue(const T &x);
	T deQueue();
	T getHead();
	void traverse();
};



template<class T>
linkQueue<T>::linkQueue() {
	head = new node;
	head->next = nullptr;
	front = rear = head;
	currentLength = 0;
}


template<class T>
linkQueue<T>::~linkQueue() {
	clear();
	//用for循环搭配currentLength，避免讨论队列是否为空的情况。
	delete head;
}


template<class T>
void linkQueue<T>::clear(){
	for (int i = 0; i < currentLength; i++) {
		node* tmp = front;
		front = front->next;
		delete tmp;
	}
	front = rear = head;
	currentLength = 0;
}


template<class T>
void linkQueue<T>::enQueue(const T&x) {
	node *tmp;
	tmp = new node(x);
	rear->next = tmp;
	rear = tmp;
	if (currentLength == 0)front = rear;
	currentLength++;
}

template<class T>
T linkQueue<T>::deQueue() {
	if (isEmpty()) throw emptyQueue();
	node* tmp;
	tmp = head -> next;
	T data = front->data;
	head->next = front->next;
	if (front == rear) front = rear = head;
	else front = head->next;
	delete tmp;
	currentLength--;
	return data;
}

template<class T>
T linkQueue<T>::getHead() {
	if (isEmpty()) throw emptyQueue();
	return front->data;
}

template<class T>
void linkQueue<T>::traverse() {
	node* p = front;
	cout << "Head   ";
	for (int i = 0; i < currentLength; i++) {
		cout << p->data << ' ';
		p = p->next;
	}
	cout << "   Rear" << endl;
}