#pragma once
#include "dynamicsearchtable.h"
template <class KEY, class OTHER>
class BinarySearchTree :public dynamicSearchTable<KEY, OTHER>
{
private:
	struct BinaryNode
	{
		SET<KEY, OTHER> data;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode(const SET<KEY, OTHER>& thedata, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
			: data(thedata), left(lt), right(rt) { }
	};
	BinaryNode* root;

public:
	BinarySearchTree() { root = nullptr; }
	~BinarySearchTree() { makeEmpty(root); }
	SET<KEY, OTHER>* find(const KEY& x) const { return find(x, root); }
	void insert(const SET<KEY, OTHER>& x) { insert(x, root); }
	void remove(const KEY& x) { remove(x, root); }
	OTHER findmax() { return findmax(root); }
	OTHER findmin() { return findmin(root); }
private:
	void insert(const SET<KEY, OTHER>& x, BinaryNode*& t)
	{
		if (t == nullptr)
			t = new BinaryNode(x, nullptr, nullptr);
		else if (x.key < t->data.key)
			insert(x, t->left);
		else if (t->data.key < x.key)
			insert(x, t->right);
	}
	void remove(const KEY& x, BinaryNode*& t)
	{
		if (t == nullptr) return;
		if (x < t->data.key) remove(x, t->left);
		else if (t->data.key < x) remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr) {    //有两个孩子
			BinaryNode* tmp = t->right;
			while (tmp->left != nullptr) tmp = tmp->left;
			t->data = tmp->data;
			remove(t->data.key, t->right);
		}
		else {                                          //被删结点是叶结点或只有一个孩子
			BinaryNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
	}
	SET<KEY, OTHER>* find(const KEY& x, BinaryNode* t) const
	{
		if (t == nullptr || t->data.key == x)
			return (SET<KEY, OTHER>*) t;
		if (x < t->data.key)   return find(x, t->left);
		else return find(x, t->right);
	}
	void makeEmpty(BinaryNode* t)
	{
		if (t == nullptr) return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	OTHER findmax(BinaryNode*& t)
	{
		if (t == nullptr)return false;
		while (t->right != nullptr)t = t->right;
		SET<KEY, OTHER> max=t;
		return max.other;
	}
    OTHER findmin(BinaryNode*& t)
	{
		if (t == nullptr)return false;
		while (t->left != nullptr)t = t->left;
		SET<KEY,OTHER> min=t;
		return min.other;
	}
};
