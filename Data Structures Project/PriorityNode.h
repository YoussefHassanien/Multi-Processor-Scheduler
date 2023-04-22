#pragma once
#ifndef PRIORITY_NODE
#define PRIORITY_NODE

template < typename T>
class PriorityNode
{
private:
	T item; // A data item
	int priority; //index indicating the priority of the node
	PriorityNode<T>* next; // Pointer to next node
public:

	//Default Constructor
	PriorityNode()
	{
		next = nullptr;
	}

	//Constructor that takes 2 parameter (the data item and its priority)
	PriorityNode(const T& r_Item, const int r_Priority)
	{
		item = r_Item;
		priority = r_Priority;
		next = nullptr;
	}

	//Constructor that takes 3 parameters (the data item, its priority and a pointer to the next node)
	PriorityNode(const T& r_Item, const int r_Priority, Node<T>* nextNodePtr)
	{
		item = r_Item;
		priority = r_Priority;
		next = nextNodePtr;
	}

	//Setter to the data member "item"
	void setItem(const T& r_Item)
	{
		item = r_Item;
	}

	//Setter to the data member "priority"
	void setPriority(const int& r_Priority)
	{
		priority = r_Priority;
	}

	//Setter to the data member "next"
	void setNext(PriorityNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	//Getter to the data member "item"
	T getItem() const
	{
		return item;
	}

	//Getter to the data member "priority"
	int getPriority() const
	{
		return priority;
	}

	//Getter to the data member "next"
	PriorityNode<T>* getNext() const
	{
		return next;
	}
}; // end Node
#endif