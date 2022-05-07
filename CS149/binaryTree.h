#pragma once
#include"linkQueue.h"

template<class T>
class BinaryTree {
private:
	struct Node {

		Node *left, *right;
		T data;
		Node() :left(nullptr), right(nullptr) {}
		Node(T item, Node*L = nullptr, Node *R = nullptr) :
			data(item), left(L), right(R) {}
		~Node() {}
	};

	Node *root;
public:
	BinaryTree() :root(nullptr) {}
	BinaryTree(const T& value) { root = new Node(value); }	
	BinaryTree(const Node* p) { root = p;}
	~BinaryTree() { clear(); }

	T getRoot() const { return root->data; }
	T getLeft() const { return root->left->data; }
	T getRight() const { return root->right->data; }

	void makeTree(const T &x, BinaryTree & lt, BinaryTree&rt) {
		root = new Node(x, lt.root, rt.root);
		lt.root = nullptr;
		rt.root = nullptr;
	}

	bool isEnpty() const { return root == nullptr;}

	void clear() { if (root != nullptr) clear(root); root = nullptr; }
	int size()const { return size(root); }
	int height()const { return height(root); }

	void preOrder()const {
		if (root != nullptr) {
			preOrder(root);
			cout << endl;
		}
	}


	void midOrder()const {
		if (root != nullptr) {
			midOrder(root);
			cout << endl;
		}
	}


	void layerOrderS() {
		if (root != nullptr) {
			int h = height();
			linkQueue<char> *ques = new linkQueue<char>[h];
			layerOrderS(root, ques, 0);
			for (int i = 0; i < h; i++) {
				ques[i].traverse();
				cout << endl;
			}
		}
	}



	void createTree(T flag);

	void isComplete() {
		int currentMax = 0;
		maxNum(root, 1, currentMax);
		cout << "The max number is: "<<currentMax << endl;
		if (currentMax == size()) cout << "This tree is complete" << endl;
		else cout << "This tree is not complete" << endl;
	}

private:
	void clear(Node* t) {
		if (t->left != nullptr) clear(t->left);
		if (t->right != nullptr) clear(t->right);
		delete t;
	}

	int height(Node* t)const {
		if (t == nullptr)return 0;
		else{
			int lt = 1 + height(t->left), rt = height(t -> right);
			return ((lt > rt) ? lt : rt);
		}
	}

	int size(Node *t) const {
		if (t == nullptr) return 0;
		return 1 + size(t->left) + size(t->right);
	}

	void maxNum(Node *t, int rootNum, int& max){
		if (rootNum > max) max = rootNum;
		if (t->left != nullptr) maxNum(t->left, rootNum*2, max);
		if (t->right != nullptr) maxNum(t->right, rootNum*2+1, max);
	}

	void preOrder(Node *t)const {
		if (t != nullptr) {
			cout << t->data << "  ";
			preOrder(t->left);
			preOrder(t->right);
		}
	}

	void midOrder(Node *t)const {
		if (t != nullptr) {
			midOrder(t->left);
			cout << t->data << "  ";
			midOrder(t->right);
		}
	}

	void layerOrderS(Node *t, linkQueue<char> *ques, int i) {
		ques[i].enQueue(t->data);
		if (t->left != nullptr) layerOrderS(t->left, ques, i + 1);
		if (t->right != nullptr) layerOrderS(t->right, ques, i);
	}
};



template<class T>
void BinaryTree<T>::createTree(T flag) {
	linkQueue<Node*>que;
	Node* tmp;
	T x, ldata, rdata;

	cout << "Input the root:" << endl;
	cin >> x;
	root = new Node(x);
	que.enQueue(root);

	while (!que.isEmpty()) {
		tmp = que.deQueue();
		cout << "Input two sons of " << tmp->data << "(" << flag << " represents the null)" << endl;
		cin >> ldata >> rdata;
		if (ldata != flag)que.enQueue(tmp->left = new Node(ldata));
		if (rdata != flag)que.enQueue(tmp->right = new Node(rdata));
	}

	cout << "create completed!" << endl;
}