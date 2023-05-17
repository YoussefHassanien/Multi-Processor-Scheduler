#pragma once
#ifndef CYCLIC_QUEUE
#define CYCLIC_QUEUE
class Processor;
#include"Process.h"
#include<iostream>
#include "Node.h"
using namespace std;

template <typename T>
class CyclicQueue
{
private:
	Node<T>* backPtr; //Pointer to the back (last) element in the queue

public:
	int NodesCounter;
	//Default constructor 
	//sets backPtr to NULL
	CyclicQueue()
	{
		NodesCounter = 0;
		backPtr = nullptr;

	}


	//Checks whether the cyclic queue is empty oe not
	bool isEmpty() const
	{
		return (backPtr == nullptr);
	}


	//Add a new entry to the back of the queue 
	//and return a boolean indication the success or failure of the addition process.
	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
		{
			//make backPtr and its next point to the new node
			backPtr = newNodePtr;
			backPtr->setNext(newNodePtr);
			NodesCounter++;
		}
		else
		{
			newNodePtr->setNext(backPtr->getNext());
			backPtr->setNext(newNodePtr);
			backPtr = newNodePtr;
			NodesCounter++;
		}

		return true;
	}


	//Assign the parameter "FrontEntry" to the first item of the queue
	//then removes it from the queue 
	//and return a boolean indicating the success of failure of the removal process.
	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = backPtr->getNext();
		frntEntry = backPtr->getNext()->getItem();

		//special case: there is only one node in the queue
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		{
			backPtr = nullptr;
			delete nodeToDeletePtr;
			NodesCounter--;
			return true;
		}
		else
		{
			backPtr->setNext(backPtr->getNext()->getNext());
			delete nodeToDeletePtr;
			NodesCounter--;
			return true;
		}
	}


	//Assigns the parameter "FrontEntry" to the first item of the queue 
	//without removing it from the queue.
	T peek(T& frntEntry)  const
	{
		if (isEmpty())
			return NULL;

		frntEntry = backPtr->getNext()->getItem();
		return backPtr->getNext()->getItem();

	}


	//Prints the cyclic queue elements 
	void Print()
	{
		Node<T>* curPtr = backPtr;
		for (int i = 0; i < NodesCounter; i++) {
			cout << *curPtr->getItem() << ", ";
			curPtr = curPtr->getNext();
		}

	}


	
	
	// Destroys this queue and frees its memory.
	~CyclicQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}


	//Copy constructor
	CyclicQueue(const CyclicQueue<T>& CQ)
	{
		Node<T>* NodePtr = CQ.backPtr->getNext();
		if (CQ.backPtr == nullptr) //CQ is empty
		{
			backPtr = nullptr;
			return;
		}

		//insert the first node
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr = backPtr->getNext() = ptr;
		NodePtr = NodePtr->getNext();

		//insert remaining nodes
		while (NodePtr != CQ.backPtr->getnext())
		{
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			ptr->setNext(backPtr->getNext());
			backPtr->setNext(ptr);
			backPtr = ptr;
		}
	}




};
//end of CyclicQueue class

#endif
