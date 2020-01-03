#pragma once
#include "Data.h"
template<class T>
struct Node
{
	T* dat;
	Node* next;
	Node* pr;
	Node(Node* pred, T* data) { pr = pred, dat = data, next = nullptr; }
};

template<class T>
class List
{
public:
	List();
	List(int size);
	List(const List<T>& obj);


	~List();
public:
	void		push_end(T* data);
	void		push_start(T* data);
	T*			pop_end();
	T*			get_end() const;
	T*			pop_start();
	T*			get_start() const;
	T*			get(int num) const;
	Node<T>*	get_node(int num) const;
	void		set(int num, T* data);
	int			size() const;
	void		resize(int size);
	void		sort();

public:
	static void	swap(Node<T>* one, Node<T>* two);

private:
	Node<T>*	head;
	int			siz;


private:
	Node<T>*	insert_end(Node<T>* pred, Node<T>* node, T* data);
	void		remove(Node<T>* node);
	void		insert(T* data, int num);



};

template<class T>
inline List<T>::List()
{
	head = nullptr;
	siz = 0;
}

template<class T>
inline List<T>::List(int size)
{
	head = nullptr;
	siz = 0; 
	for (int i = 0; i < size; i++)
	{
		push_end(nullptr);
	}
	siz = size;
}

template<class T>
inline List<T>::List(const List<T>& obj)
{
	head = nullptr;
	siz = obj.siz;
	for (int i = 0; i < obj.siz; i++)
	{
		head = insert_end(nullptr, head, obj.get(i));
	}
}

template<class T>
inline List<T>::~List()
{
	Node<T>* curr = head;
	while (curr != nullptr)
	{
		Node<T>* tmp = curr;
		curr = curr->next;
		delete tmp;
	}
}

template<class T>
inline void List<T>::push_end(T* data)
{
	head = insert_end(nullptr, head, data);
}

template<class T>
inline void List<T>::push_start(T* data)
{
	int tmp = siz + 1;
	resize(tmp);
	insert(data, 0);
}

template<class T>
inline T* List<T>::pop_end()
{
	if (head == nullptr) return nullptr;
	siz--;
	Node<T>* curr = head;
	while (true)
	{
		if (curr->next == nullptr) break;

		curr = curr->next;
	}
	T* tmp = curr->dat;
	if (curr->pr != nullptr) curr->pr->next = nullptr;
	delete curr;
	curr = nullptr;
	return tmp;
}

template<class T>
inline T* List<T>::get_end() const
{
	if (head == nullptr) return nullptr;
	Node<T>* curr = head;
	while (true)
	{
		if (curr->next == nullptr) break;

		curr = curr->next;
	}
	return curr->dat;
}

template<class T>
inline T* List<T>::pop_start()
{
	if (head == nullptr) return nullptr;
	siz--;
	Node<T>* tmp1 = head;
	head = head->next;

	T* tmp2 = tmp1->dat;
	delete tmp1;
	return tmp2;
}

template<class T>
inline T* List<T>::get_start() const
{
	if (head == nullptr) return nullptr;
	return head->dat;
}

template<class T>
inline Node<T>* List<T>::insert_end(Node<T>* pred, Node<T>* node, T* data)
{
	if (node == nullptr)
	{
		node = new Node<T>(pred, data);
		siz++;
	}
	else
	{
		node->next = insert_end(node, node->next, data);
	}
	return node;
}

template<class T>
inline void List<T>::remove(Node<T>* node)
{
	if (node->pr != nullptr)
		node->pr->next = node->next;
	if (node->next != nullptr)
		node->next->pr = node->pr;
	delete node;
}

template<class T>
inline void List<T>::insert(T* data, int num)
{
	Node<T>* curr = head;
	int n = num;

	while (true)
	{
		if (n == 0)
		{
			if (curr->dat == nullptr)
			{
				curr->dat = data;
			}
			else
			{
				delete curr->dat;
				curr->dat = data;
			}
			break;
		}
		curr = curr->next;
		n--;
	}
}

template<class T>
inline void List<T>::swap(Node<T>* one, Node<T>* two)
{
	T* tmp = one->dat;
	one->dat = two->dat;
	two->dat = tmp;
}

template<class T>
inline T* List<T>::get(int num) const
{
	if (num > siz || head == nullptr) return nullptr;
	Node<T>* curr = head;
	for (int i = 0; i < num; i++)
		curr = curr->next;
	
	return curr->dat;
}

template<class T>
inline Node<T>* List<T>::get_node(int num) const
{
	if (num > siz || head == nullptr) return nullptr;
	Node<T>* curr = head;
	for (int i = 0; i < num; i++)
		curr = curr->next;

	return curr;
}

inline object* List<object>::get(int num) const
{
	if (num > siz || head == nullptr) return nullptr;
	Node<object>* curr = head;
	for (int i = 0; i < num; i++)
		curr = curr->next;

	return curr->dat;
}

template<class T>
inline void List<T>::set(int num, T* data)
{
	if (num > siz) return;
	insert(data, num);
}

template<class T>
inline int List<T>::size() const
{
	return siz;
}

template<class T>
inline void List<T>::resize(int size)
{
	int resiz = siz - size;
	if (resiz > 0)
	{
		for (int i = 0; i < resiz; i++)
		{
			T* tmp = pop_end();
			delete tmp;
		}
	}
	else if (resiz < 0)
	{
		resiz = -resiz;
		for (int i = 0; i < resiz; i++)
		{
			push_end(nullptr);
		}
	}
}

template<class T>
inline void List<T>::sort()
{
	bool swapped;
	for (int i = 0; i < size() - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < size() - i - 1; j++)
		{
			if (get(j) == nullptr)
			{
				swap(get_node(j), get_node(j + 1));
				swapped = true;
			}
			else if (get(j + 1) == nullptr)
			{

			}
			else if (*get(j) > *get(j + 1))
			{
				swap(get_node(j), get_node(j + 1));
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}

inline void List<object>::sort()
{
	bool swapped;
	for (int i = 0; i < size() - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < size() - i - 1; j++)
		{
			if (get(j) == nullptr)
			{
				swap(get_node(j), get_node(j + 1));
				swapped = true;
			}
			else if (get(j + 1) == nullptr)
			{

			}
			else if (get(j)->cmp(*get(j + 1)) == 1)
			{
				swap(get_node(j), get_node(j + 1));
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}
