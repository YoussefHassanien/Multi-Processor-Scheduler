#pragma once
#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
public:

	//Default Constructor
	Node()
	{
		next = nullptr;
	}

	//Constructor that takes 1 parameter (the data item)
	Node(const T& r_Item)
	{
		item = r_Item;
		next = nullptr;
	}

	//Constructor that takes 2 parameters( the data item and a pointer to the next node)
	Node(const T& r_Item, Node<T>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}

	//Setter to the data member "item"
	void setItem(const T& r_Item)
	{
		item = r_Item;
	}

	//Setter to the data member "next"
	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	//getter to the data member "item"
	T getItem() const
	{
		return item;
	}

	//Getter to the data member "next"
	Node<T>* getNext() const
	{
		return next;
	}
}; // end Node
#endif