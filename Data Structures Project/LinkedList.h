#pragma once

#include "Node.h"
#include<iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	
	
public:
	int NodesCounter; //Counter for the actual number of nodes in the list

	//Constructor
	LinkedList()
	{
		Head = nullptr;
		NodesCounter = 0;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{

		Node<T>* p = Head;

		while (p)
		{
			cout << * p->getItem() << ", ";
			p = p->getNext();
		}
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		NodesCounter++;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		NodesCounter = 0;
	}



	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		Node<T>* N = new Node<T>(data);
		Node<T>* tmpPtr = Head;

		//Special case:teh node added is the first node
		if (Head == nullptr)
		{
			Head = N;
			NodesCounter++;
		}
		else 
		{
			while (tmpPtr->getNext() != nullptr)
			{
				tmpPtr = tmpPtr->getNext();
			}
			tmpPtr->setNext(N);
			N->setNext(nullptr);
			NodesCounter++;
		}
		
	}

	//searches for a given value in the list, returns true if found; false otherwise.
	int Find(int& Key)
	{
		int position = 0;
		Node<T>* ptr = Head;
		//This is how to iterate over a linked list using for loop, NO i++ here (ptr = ptr->next)
		for (ptr; ptr; ptr = ptr->getNext()) //the second ptr means while ptr!= NULL
		{
			position++;
			if (ptr->getItem() == Key)
			{
				return position;
			}
		}
		return 0;
	}


	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count = 0;
		Node<T>* tmpPtr = Head;
		while (tmpPtr != NULL) {
			if (tmpPtr->getItem() == value) {
				count++;
			}
			tmpPtr = tmpPtr->getNext();
		}
		return count;
	}


	//Deletes the first node in the list
	void DeleteFirst(T& tmp)
	{
		if (!Head)
			return;
		Node<T>* tmpPtr = Head;
		Head = Head->getNext();
		tmp = tmpPtr->getItem();
		delete tmpPtr;
		NodesCounter--;
	}



	//Deletes the last node in the list
	void DeleteLast()
	{
		T tmp;
		Node<T>* tmpPtr = Head;
		if (!Head)
			return;
		if (!Head->getNext()) {
			DeleteFirst(tmp);
			NodesCounter--;
			return;
		}

		while (tmpPtr->getNext()->getNext())
			tmpPtr = tmpPtr->getNext();

		delete tmpPtr->getNext();
		tmpPtr->setNext(NULL);
		NodesCounter--;
	}


	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	

	bool DeleteNode(const T& value)
	{
		Node<T>* p = Head;
		if (Head == nullptr)
		{
			return false;
		}
		if (Head->getItem() == value)
		{
			Head = Head->getNext();
			delete p;
			NodesCounter--;
			return true;
		}
		while (p->getNext())
		{
			if (p->getNext()->getItem() == value)
			{
				Node<T>* temp = p->getNext();
				p->setNext(temp->getNext());
				delete temp;
				NodesCounter--;
				return true;
			}
			p = p->getNext();
		}
		return false;
	}




	void DeleteNodeAtPosition(T& deletednode,int index) //Deletes a node at a certain position 
	{
		if (index == 0 || index > NodesCounter)
			return;

		Node<T>* p = Head;
		if (index == 1)
		{
			Head = Head->getNext();
			deletednode = p->getItem();
			delete p;
			NodesCounter--;
			return;
		}
		for (int i = 1; i < index-1; i++)
			p = p->getNext();
		Node<T>* temp = p->getNext();
		p->setNext(temp->getNext());
		Node<T>* copytemp = new Node<T>;
		copytemp = temp;
		deletednode = copytemp->getItem();
		delete temp;
		NodesCounter--;
		return;

	}

	//Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L) {
		Node<T>* tmpPtr = Head;
		while (tmpPtr->getNext())
			tmpPtr = tmpPtr->getNext();
		tmpPtr->setNext(L.Head);
		Head = this->Head;

	}

	// Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		Node<T>* previous = NULL, * following = NULL;
		Node<T>* current = Head;

		while (current != NULL) {
			//the following pointer points at the next of the current pointer
			following = current->getNext();
			//reverse the next pointer of the current node to point at the previous one
			current->setNext(previous);
			//shifts the previous pointer to point at the same node as the current pointer
			previous = current;
			//shifts the current pointer to the next one
			current = following;
		}
		Head = previous;
	}
	bool isEmpty() const
	{
		if (Head == nullptr)
			return true;
		else
			return false;
	}

	bool peek(T& value) {
		if (isEmpty())
			return false;
		
		value = Head->getItem();
		return true;
	}
	

};