#include <ctime>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "linkedQueue.h"

using namespace std;

const int numberOfBuckets = 36;  // const int numberOfBuckets = 10;
const int arraySize = 1000000;

operationTypes queueOperations;

void printOperations( operationTypes operations );
int mapToBucket( char ch );
void outputDataArray( string data[ ], int length );
void radixSort( string inArray[ ], int arrayLength, int maxLength );

int main( ) {
	srand( time( 0 ) );
	string* list1 = new string[ arraySize ];

	char buffer[ 11 ];

	cout << "building the list..." << endl;
	for ( int i = 0; i < arraySize; i++ ) {
		// build an element and assignto array element
		sprintf_s( buffer, "%c%c%06d%c%c", 'a' + rand( ) % 26, 'a' + rand( ) % 26,
			rand( ) % 100000, 'a' + rand( ) % 26, 'a' + rand( ) % 26 );

		list1[ i ] = buffer;
	}

	cout << "sorting the list..." << endl;
	radixSort( list1, arraySize, 10 );

	// only print very short lists
	if ( arraySize < 50 ) {
		for ( int i = 0; i < arraySize; i++ ) {
			cout << list1[ i ] << endl;
		}
	}

	printOperations( queueOperations );

	delete[ ] list1;
	list1 = nullptr;
	return 0;
}

void printOperations( operationTypes queueOperations ) {
	cout << std::setw( 25 ) << "Operations Performed During Sorting:" << endl;
	cout << std::setw( 25 ) << "Comparisons Made:" << queueOperations.timesCompared << endl;
	cout << std::setw( 25 ) << "Assignments Made:" << queueOperations.timesAssigned << endl;
	cout << std::setw( 25 ) << "Items Mapped to Buckets:" << queueOperations.itemsMapped << endl;
	cout << std::setw( 25 ) << "Queues Deleted:" << queueOperations.itemsDeleted << endl;
	cout << std::setw( 25 ) << "Buckets Initialized:" << queueOperations.bucketsInitialized << endl;
}

void outputDataArray( string data[ ], int length ) {
	for ( int i = 0; i < length; i++ ) {
		cout << ( data[ i ] ) << endl;
	}
}

int mapToBucket( char ch ) {
	// every time the loop restarts it is another comparison
	queueOperations.timesCompared += 1;

	if ( isdigit( ch ) ) {
		return ( static_cast< int >( ch ) & 0x0f );  // map 48..57 -> 0..9
	}
	else {
		return ( static_cast< int >( ch & ~32 ) - 55 );  // toUpper() and map 65..90 -> 10..36
	}
}


void radixSort( string inArray[ ], int arrayLength, int maxLength ) {
	linkedQueueType<string> buckets[ numberOfBuckets ];

	/*  This was moved out of the loop below as when debugging
		I noticed that queueFirst and queueLast were both always 
		nullptr. After spending a few minutes analyzing the code 
		and debugging it I noticed this to be the reason as to why 
		only thing i noticed with results was bucketsInitialized is
		36 now instead of 360 since not being run in the loop of 10 */

	for ( int i = 0; i < numberOfBuckets; i++ ) { // clear the buckets
		buckets[ i ].initializeQueue( ); // initializing a bucket here
		queueOperations.bucketsInitialized += 1; // so increment aswell
	}

	// for each position to be sorted
	for ( int charPos = maxLength - 1; charPos >= 0; charPos-- ) {

		queueOperations.timesCompared += 1;
		for ( int i = 0; i < arrayLength; i++ ) { // add each element to proper bucket
			// map to bucket
			queueOperations.itemsMapped += 1;
			buckets[ mapToBucket( inArray[ i ].at( charPos ) ) ].addQueue( inArray[ i ] );
		}

		// 'restack' input array from buckets
		int arrayPosition = 0;
		int bucketNumber = 0;

		while ( bucketNumber < numberOfBuckets ) { // *COMPARISON*
			queueOperations.timesCompared += 1;

			while ( !( buckets[ bucketNumber ].isEmptyQueue( ) ) ) {

				queueOperations.timesAssigned += 1; // assigning value here
				inArray[ arrayPosition ] = buckets[ bucketNumber ].front( );

				queueOperations.itemsDeleted += 1;	// deleting bucket
				buckets[ bucketNumber ].deleteQueue( );

				arrayPosition++;
			}
			bucketNumber++;
		}
	}
}
