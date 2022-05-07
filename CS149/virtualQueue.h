#pragma once

class emptyQueue {};

template <class T>
class queue {
public:
	virtual bool isEmpty() = 0;
	virtual void enQueue(const T &x) = 0;
	virtual T deQueue() = 0;
	virtual T getHead() = 0;
	virtual ~queue() {};
};
