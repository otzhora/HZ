#pragma once 

using namespace std;


template<typename T>
class Node
{
public:

	Node<T>() 
	{
		right = nullptr;
		left = nullptr;
		prev = nullptr;
	}

	Node<T>(T& elem)
	{
		right = nullptr;
		left = nullptr;
		prev = nullptr;
		val = elem;
	}

	Node<T>* getright();

	Node<T>* getleft();

	Node<T>* getprev();

	void setleft(Node<T>* chld);

	void setright(Node<T>* chld);

	T& getval();

	void setval(T& val);

	~Node() 
	{

	}
private:
	Node<T>* right;
	Node<T>* left;
	Node<T>* prev;
	T val;
};

template<typename T>
class Tree
{
public:
	class iterator
	{
	public:
		iterator() 
		{
			val = nullptr;
		}
		iterator(Node<T>* item)
		{
			val = item;
		}

		Node<T> operator++() 
		{
			val = val->getright();
			return *val;
		}
		Node<T> operator--() 
		{
			val = val->getleft();
			return *val;
		}
		Node<T> operator-=(size_t i) 
		{
			val = val->getprev();
			return *val;
		}
		T& getval()
		{
			return val->getval();
		}

	private:
		Node<T>* val;
	};

	void add(T& elem, Node<T>* curr);

	void add(T& elem);

	bool find(T& elem);

	bool find(T& elem, Node<T>* curr);

	void print();

	void print(Node<T>* elem);
	Tree()
	{
		root = nullptr;
		size = 0;
	}

	~Tree()
	{
		clear(root);
	}

	void clear(Node<T>* curr);

	Node<T>* getroot()
	{
		return root;
	}
private:
	Node<T>* root;
	size_t size;
};

#include "tree.h"

template<typename T>
Node<T>* Node<T>::getleft()
{
	return left;
}

template<typename T>
Node<T>* Node<T>::getright()
{
	return right;
}

template<typename T>
Node<T>* Node<T>::getprev()
{
	return prev;
}

template<typename T>
T& Node<T>::getval()
{
	return val;
}

template<typename T>
void Node<T>::setleft(Node<T>* clhd)
{
	left = clhd;
}

template<typename T>
void Node<T>::setright(Node<T>* clhd)
{
	right = clhd;
}

template<typename T>
void Node<T>::setval(T& elem)
{
	val = elem;
}
template<typename T>
void Tree<T>::add(T& elem)
{
	add(elem, root);
}

template<typename T>
void Tree<T>::add(T& elem, Node<T>* curr)
{
	if (size == 0)
	{
		Node<T>* new_root = new Node<T>(elem);
		root = new_root;
		size++;
	}
	else
	{
		if (elem < curr->getval())
		{
			if (curr->getleft() == nullptr)
			{
				Node<T>* new_node = new Node<T>(elem);
				curr->setleft(new_node);
				return;
			}
			else
			{
				add(elem, curr->getleft());
			}
		}
		else if (elem > curr->getval())
		{

			if (curr->getright() == nullptr)
			{
				Node<T>* new_node = new Node<T>(elem);
				curr->setright(new_node);
				return;
			}
			else
			{
				add(elem, curr->getright());
			}
		}
	}
}

template<typename T>
bool Tree<T>::find(T& elem)
{
	return find(elem, root);
}

template<typename T>
bool Tree<T>::find(T& elem, Node<T>* curr)
{
	if (curr == nullptr)
		return false;
	if (elem == curr->getval())
	{
		return true;
	}
	else if (elem < curr->getval())
	{
		if (curr->getleft() == nullptr)
			return false;
		else return find(elem, curr->getleft());
	}
	else
	{
		if (curr->getright() == nullptr)
			return false;
		else return find(elem, curr->getright());
	}
}

template<typename T>
void Tree<T>::clear(Node<T>* curr)
{
	if (curr)
	{
		clear(curr->getleft());
		clear(curr->getright());
		delete curr;
	}
}

template<typename T>
void Tree<T>::print()
{
	print(root);
}

template<typename T>
void Tree<T>::print(Node<T>* elem)
{
	std::cout << elem->getval() << std::endl;
	if (elem->getleft() != nullptr)
		print(elem->getleft());
	if(elem->getright() != nullptr)
		print(elem->getright());
}