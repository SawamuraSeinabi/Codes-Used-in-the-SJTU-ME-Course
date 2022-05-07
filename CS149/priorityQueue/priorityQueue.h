#pragma once
#include "virtualQueue.h"
template <class Type>
class priorityQueue :public queue<Type>
{
private:
	int currentSize;
	Type *array;
	int maxSize;

	void doubleSpace();
	void buildHeap();  //构建堆
	void percolateDown(int hole);   //向下过滤
public:
	priorityQueue(int capacity = 100)
	{
		array = new Type[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const Type *items, int size);
	~priorityQueue() { delete[] array; }
	bool isEmpty() const { return currentSize == 0; }
	void enQueue(const Type& x);
	Type deQueue();
	Type getHead() { return array[1]; }
};
template <class Type>
void priorityQueue<Type>::enQueue(const Type& x)
{
	if (currentSize == maxSize - 1)  doubleSpace();

	// 向上过滤
	int hole = ++currentSize; //hole为空结点所在数组位置
	for (; hole > 1 && x < array[hole / 2]; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}
template <class Type>
Type priorityQueue<Type>::deQueue()
{
	Type minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);  //向下过滤，参数为出队元素所在位置
	return minItem;
}
template <class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
	int child; Type tmp = array[hole];

	for (; hole * 2 <= currentSize; hole = child) //每次循环，hole转到孩子上
	{
		child = hole * 2; //将child置为hole的左孩子
		if (child != currentSize && array[child + 1] < array[child]) //若右孩子比左孩子小
			child++; //转到右孩子
		if (array[child] < tmp)   array[hole] = array[child];
		else    break;
	}
	array[hole] = tmp;
}
template <class Type>
void priorityQueue<Type>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}
template <class Type>
priorityQueue<Type>::priorityQueue(const Type* items, int size): maxSize(size + 10), currentSize(size)
{
	array = new Type[maxSize];
	for (int i = 0; i < size; i++)
		array[i + 1] = items[i];
	buildHeap();
}
template <class Type>
void priorityQueue<Type>::doubleSpace()
{
	Type* tmp = array;
	maxSize = maxSize * 2;
	array = new Type[maxSize];
	for (int i = 0; i <= currentSize; ++i)
		array[i] = tmp[i];
	delete[]tmp;
}