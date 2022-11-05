// Header file linkedQueue.h

#ifndef H_linkedQueue
#define H_linkedQueue

#include <cassert>
#include <iostream>

#include "queueADT.h"

using namespace std;

// Definition of the node
template <class Type>
struct nodeType {
	Type info;
	nodeType<Type>* link;
};

struct operationTypes {
	int timesCompared;
	int timesAssigned;

	int itemsMapped;
	int itemsDeleted;
	int bucketsInitialized;
}; extern operationTypes queueOperations;

template <class Type>
class linkedQueueType : public queueADT<Type> {
public:
	const linkedQueueType<Type>& operator=( const linkedQueueType<Type>& );
	// Overload the assignment operator.

	bool isEmptyQueue( ) const;
	// Function to determine whether the queue is empty.
	// Postcondition: Returns true if the queue is empty,
	//               otherwise returns false.

	bool isFullQueue( ) const;
	// Function to determine whether the queue is full.
	// Postcondition: Returns true if the queue is full,
	//               otherwise returns false.

	void initializeQueue( );
	// Function to initialize the queue to an empty state.
	// Postcondition: queueFront = NULL; queueRear = NULL

	Type front( ) const;
	// Function to return the first element of the queue.
	// Precondition: The queue exists and is not empty.
	// Postcondition: If the queue is empty, the program
	//               terminates; otherwise, the first
	//               element of the queue is returned.

	Type back( ) const;
	// Function to return the last element of the queue.
	// Precondition: The queue exists and is not empty.
	// Postcondition: If the queue is empty, the program
	//               terminates; otherwise, the last
	//               element of the queue is returned.

	void addQueue( const Type& queueElement );
	// Function to add queueElement to the queue.
	// Precondition: The queue exists and is not full.
	// Postcondition: The queue is changed and queueElement
	//               is added to the queue.

	void deleteQueue( );
	// Function  to remove the first element of the queue.
	// Precondition: The queue exists and is not empty.
	// Postcondition: The queue is changed and the first
	//               element is removed from the queue.

	linkedQueueType( );
	// Default constructor

	linkedQueueType( const linkedQueueType<Type>& otherQueue );
	// Copy constructor

	~linkedQueueType( );
	// Destructor

private:
	nodeType<Type>* queueFront;  // pointer to the front of
								 // the queue
	nodeType<Type>* queueRear;  // pointer to the rear of
								// the queue
};

// Default constructor
template <class Type>
linkedQueueType<Type>::linkedQueueType( ) {
	queueFront = nullptr;  // set front to null
	queueRear = nullptr;   // set rear to null
	queueOperations.timesAssigned += 2; // assign below compare above
}  // end default constructor

template <class Type>
bool linkedQueueType<Type>::isEmptyQueue( ) const {
	// comparing queueFront to nullptr
	queueOperations.timesCompared += 1;
	return ( queueFront == nullptr );
}  // end

template <class Type>
bool linkedQueueType<Type>::isFullQueue( ) const {
	return false;
}  // end isFullQueue

template <class Type>
void linkedQueueType<Type>::initializeQueue( ) {
	nodeType<Type>* temp;
	
	queueOperations.timesCompared += 1;
	while ( queueFront != nullptr )  // while there are elements left
	{
		queueOperations.timesCompared += 1; // increment both because
		queueOperations.timesAssigned += 2;

		temp = queueFront;  // set temp to point to current node
		queueFront = queueFront->link;  // advance first to next node

		delete temp;  // deallocate memory occupied by temp
	}

	queueRear = nullptr;  // set rear to NULL
	queueOperations.timesAssigned += 1;
}  // end initializeQueue

template <class Type>
void linkedQueueType<Type>::addQueue( const Type& newElement ) {
	nodeType<Type>* newNode;

	newNode = new nodeType<Type>;  // create the node

	newNode->info = newElement;  // store the info
	newNode->link = nullptr;     // initialize the link field to NULL
	queueOperations.timesAssigned += 3;

	queueOperations.timesCompared += 1;
	if ( queueFront == nullptr )  // if initially the queue is empty
	{
		queueFront = newNode;
		queueRear = newNode;
		queueOperations.timesAssigned += 2;
	}
	else  // add newNode at the end
	{
		queueRear->link = newNode;
		queueRear = queueRear->link;
		queueOperations.timesAssigned += 2;
	}
}  // end addQueue

template <class Type>
Type linkedQueueType<Type>::front( ) const {
	queueOperations.timesCompared += 1;
	assert( queueFront != nullptr );
	return queueFront->info;
}  // end front

template <class Type>
Type linkedQueueType<Type>::back( ) const {
	queueOperations.timesCompared += 1;
	assert( queueRear != nullptr );
	return queueRear->info;
}  // end back

template <class Type>
void linkedQueueType<Type>::deleteQueue( ) {
	nodeType<Type>* temp;

	// performing comparison below
	queueOperations.timesCompared += 1;
	if ( !isEmptyQueue( ) ) {
		temp = queueFront;  // make temp point to the first node (1)
		queueFront = queueFront->link;  // advance queueFront (2)
		delete temp;  // delete the first node

		// assignment above compare below
		queueOperations.timesCompared += 1;
		if ( queueFront == nullptr ) // if queue is empty
			queueRear = nullptr;  // set queueRear to NULL (3)

		queueOperations.timesAssigned += 3;
	}
	else
		cout << "Cannot remove from an empty queue" << endl;
}  // end deleteQueue

// Destructor
template <class Type>
linkedQueueType<Type>::~linkedQueueType( ) {
	// Write the definition of the destructor
}  // end destructor

template <class Type>
const linkedQueueType<Type>& linkedQueueType<Type>::operator=( const linkedQueueType<Type>& otherQueue ) {
	nodeType<Type>* temp = queueFront;
	queueOperations.timesAssigned += 1;

	// while temp's link doesnt point to nullptr
	while ( temp->link != nullptr ) {

		// add temp->info to end of queue
		addQueue( temp->info );

		// advance temp
		temp = temp->link;
		queueOperations.timesAssigned += 1;
	}

	delete temp;
}  // end assignment operator

// copy constructor
template <class Type>
linkedQueueType<Type>::linkedQueueType(	const linkedQueueType<Type>& otherQueue ) {
	this = otherQueue;
	queueOperations.timesAssigned += 1;
}  // end copy constructor

#endif
