#pragma once
#include <iostream>
using namespace std;


template<typename T>
struct node
{
	T key;
	unsigned char height;
	node<T>* left;
	node<T>* right;
	node(T k) { key = k; left = right = nullptr; height = 1; }
};



template<class T>
class Tree
{
public:
	Tree();
	~Tree();


	void			insert(T k);
	void			print() const;
	void			remove(T k);
	T				get_min() const;
	T				get_max() const;

private:
	node<T>*		tree;


private:
	int				bfactor(node<T>* p);
	unsigned char	height(node<T>* p);
	void			fix_height(node<T>* p);

	node<T>*		rotate_right(node<T>* p);
	node<T>*		rotate_left(node<T>* q);
	node<T>*		balance(node<T>* p);
	node<T>*		insert_private(node<T>* p, T k);
	node<T>*		find_min(node<T>* p) const;
	node<T>*		removemin(node<T>* p);
	node<T>*		remove(node<T>* p, T& k);
	void			delete_(node<T>* p);
	void			print(node<T>* p,int yrov) const;
	T				get_max(node<T>* p) const;

};



template<class T>
inline Tree<T>::Tree()
{
	tree = nullptr;
}

template<class T>
inline Tree<T>::~Tree()
{
	delete_(tree);
}

template<class T>
inline void Tree<T>::insert(T k)
{
	tree = insert_private(tree, k);
}

template<class T>
inline void Tree<T>::print() const
{
	print(tree, 0);
}

template<class T>
inline void Tree<T>::remove(T k)
{
	tree = remove(tree, k);
}

template<class T>
inline T Tree<T>::get_min() const
{
	return find_min(tree)->key;
}

template<class T>
inline T Tree<T>::get_max() const
{
	return get_max(tree);
}

template<class T>
inline T Tree<T>::get_max(node<T>* p) const
{
	return p->right == nullptr ? p->key : get_max(p->right);
}


template<class T>
inline int Tree<T>::bfactor(node<T>* p)
{
	return height(p->right) - height(p->left);
}

template<class T>
inline unsigned char Tree<T>::height(node<T>* p)
{
	return p != nullptr ? p->height : 0;
}

template<class T>
inline void Tree<T>::fix_height(node<T>* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

template<class T>
inline node<T>* Tree<T>::rotate_right(node<T>* p)
{
	node<T>* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

template<class T>
inline node<T>* Tree<T>::rotate_left(node<T>* q)
{
	node<T>* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

template<class T>
inline node<T>* Tree<T>::balance(node<T>* p)
{
	fix_height(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p;
}

template<class T>
inline node<T>* Tree<T>::insert_private(node<T>* p, T k)
{
	if (!p) return new node<T>(k);
	if (k < p->key)
		p->left = insert_private(p->left, k);
	else
		p->right = insert_private(p->right, k);
	return balance(p);
}

template<class T>
inline node<T>* Tree<T>::find_min(node<T>* p) const
{
	return p->left ? find_min(p->left) : p;
}

template<class T>
inline node<T>* Tree<T>::removemin(node<T>* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

template<class T>
inline node<T>* Tree<T>::remove(node<T>* p, T& k)
{
	if (p == nullptr) return nullptr;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else 
	{
		node<T>* q = p->left;
		node<T>* r = p->right;
		delete p;
		if (!r) return q;
		node<T>* min = find_min(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

template<class T>
inline void Tree<T>::delete_(node<T>* p)
{
	if (p != nullptr)
	{
		delete_(p->right);
		delete_(p->left);
		delete p;
	}
}

template<class T>
inline void Tree<T>::print(node<T>* p, int yrov) const
{
	if (p != nullptr)
	{
		print(p->left, yrov + 1);
		for (int i = 0; i < yrov; i++) cout << "| ";
		cout << p->key << endl;
		print(p->right, yrov + 1);
	}
}
