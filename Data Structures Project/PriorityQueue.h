#pragma once


#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include"Process.h"
#include<iostream>
#include "PriorityNode.h"
#include <vector>
using namespace std;


template <typename T>
class PriorityQueue
{
private:

	PriorityNode<T>* backPtr;  //Pointer to the fornt(first) element of the queue
	PriorityNode<T>* frontPtr; //Pointer to the back(last) element of the queue

public:
	int NodesCounter;
	//Default constructor 
	//sets backPtr and frontPtr to NULL
	PriorityQueue()
	{
		NodesCounter = 0;
		backPtr = nullptr;
		frontPtr = nullptr;

	}


	//Checks whether the linked list is empty oe not
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}


	//Add a new entry to the back of the queue 
	//and return a boolean indication the success or failure of the addition process.
	bool enqueue(const T& newEntry, const int& pri)
	{
		//Create the new node
		PriorityNode<T>* newNodePtr = new PriorityNode<T>(newEntry, pri);
		//Create a temp node to traverse the list
		PriorityNode<T>* temp = frontPtr;
		if (isEmpty())
		{
			frontPtr = backPtr = newNodePtr;
			NodesCounter++;
		}

		//insert the new node

		//special case if this is the first node to insert 
		//or the priority of the new node is less than the priority of the front node
		else if (newNodePtr->getPriority() < frontPtr->getPriority())
		{
			temp = newNodePtr;
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
			NodesCounter++;
		}
		else
		{
			//while the queue is not empty 
			//and the node has a priority higher than or equal the new node
			while (temp->getNext() && temp->getNext()->getPriority() <= newNodePtr->getPriority())
				temp = temp->getNext();
			newNodePtr->setNext(temp->getNext());
			temp->setNext(newNodePtr);
			NodesCounter++;
			
			//special case if the new inserted node is the last node in queue
			if (newNodePtr->getNext() == nullptr)
			{
				backPtr = newNodePtr;
			}
		}
		return true;
	}


	//Assign the parameter "FrontEntry" to the first item of the queue
	//then removes it from the queue 
	//and return a boolean indicating the success of failure of the removal process.
	bool dequeue(T & frntEntry)
	{
		if (isEmpty())
			return false;

		PriorityNode<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		{
			backPtr = nullptr;
		}

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


	// Destroys this queue and frees its memory.
	~PriorityQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}

	
	
	//Prints the priority queue elements 
	void Print()
	{
		PriorityNode<T>* curPtr = frontPtr;
		for (int i = 0; i < NodesCounter; i++) {
			cout << *curPtr->getItem() << ", ";
			curPtr = curPtr->getNext();
		}
	}


	//Copy constructor
	PriorityQueue(const PriorityQueue<T>& PQ)
	{
		PriorityNode<T>* PriNodePtr = PQ.frontPtr;
		if (!PriNodePtr) //PQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		PriorityNode<T>* ptr = new PriorityNode<T>(PriNodePtr->getItem(), PriNodePtr->getPriority());
		frontPtr = backPtr = ptr;
		PriNodePtr = PriNodePtr->getNext();

		//insert remaining nodes
		while (PriNodePtr)
		{
			PriorityNode<T>* ptr = new PriorityNode<T>(PriNodePtr->getItem(), PriNodePtr->getPriority());
			backPtr->setNext(ptr);
			backPtr = ptr;
			PriNodePtr = PriNodePtr->getNext();
		}
	}
	bool Find(T value)
	{
		PriorityNode<T>* curPtr = frontPtr;
		for (int i = 0; i < NodesCounter; i++) {
			if (value == curPtr->getItem())
				return true;
			curPtr = curPtr->getNext();
		}
		return false;
	}
};
//end PriorityQueue

#endif
