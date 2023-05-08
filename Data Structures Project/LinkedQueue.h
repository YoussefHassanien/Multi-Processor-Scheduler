#pragma once

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include <vector>
using namespace std;


template <typename T>
class LinkedQueue
{
private:

	Node<T>* backPtr;  //Pointer to the fornt(first) element of the queue
	Node<T>* frontPtr; //Pointer to the back(last) element of the queue
	

public:

	int NodesCounter;

	//Default constructor 
	//sets backPtr and frontPtr to NULL
	LinkedQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
		NodesCounter = 0;

	}

	
	//Checks whether the linked list is empty oe not
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}


	//Add a new entry to the back of the queue 
	//and return a boolean indication the success or failure of the addition process.
	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert	
		{
			frontPtr = newNodePtr; // The queue is empty
			NodesCounter++;
		}
		else
		{
			backPtr->setNext(newNodePtr); // The queue was not empty
			NodesCounter++;
		}

		backPtr = newNodePtr; // New node is the last node now
		return true;
	}


	//Assign the parameter "FrontEntry" to the first item of the queue
	//then removes it from the queue 
	//and return a boolean indicating the success of failure of the removal process.
	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;


		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		NodesCounter--;
		return true;

	}


	//Assigns the parameter "FrontEntry" to the first item of the queue 
	//without removing it from the queue.
	bool peek(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;

	}
	void Print()
	{
		Node<T>* curPtr = frontPtr;
		for (int i = 0; i < NodesCounter; i++) {
			cout << *curPtr->getItem() << ", ";
			curPtr = curPtr->getNext();
		}
	}


	// Destroys this queue and frees its memory.
	~LinkedQueue()
	{
		T temp;
		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}


	//Copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ)
	{
		Node<T>* NodePtr = LQ.frontPtr;
		if (!NodePtr) //LQ is empty 
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		frontPtr = backPtr = ptr;
		NodePtr = NodePtr->getNext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			backPtr->setNext(ptr);
			backPtr = ptr;
			NodePtr = NodePtr->getNext();
		}
	}
	bool Find(T value)
	{
		Node<T>* curPtr = frontPtr;
		for (int i = 0; i < NodesCounter; i++) {
			if (value == curPtr->getItem())
				return true;
			curPtr = curPtr->getNext();
		}
		return false;
	}
	bool IterativePeek(T& frntEntry, int index)
	{
		if (isEmpty() || index > NodesCounter)
			return false;
		if (index == 1)
			return peek(frntEntry);
		else
		{
			Node<T>* Temp = frontPtr;
			for (int i = 0; i < (index - 1); i++)
				Temp = Temp->getNext();
			frntEntry = Temp->getItem();
			return true;
		}
	}
};
//end LinkedQueue

#endif
