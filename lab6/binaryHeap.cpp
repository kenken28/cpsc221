#include <iostream>
#include <vector>
#include "math.h"

#define TRUE 1
#define FALSE 0

using namespace std;

int* heap = NULL;
int size = 100;

// PRE:  data between subscript top+1 and numElements-1 is a heap.
// POST: data between subscript top and numElements-1 is a heap.
void ReheapDown( int* heap, int top, int numElements )  {
	int leftChild = 2 * top + 1;
	int rightChild = 2 * top + 2;
	int minChild;
	if( leftChild < size ) {
 		// find subscript of smallest child
		if( rightChild >= numElements || heap[leftChild] < heap[rightChild] )
			minChild = leftChild;
		else
			minChild = rightChild;
		// if data at top is greater than smallest
		// child then swap and continue
		if (heap[top] > heap[minChild]) {
			swap( heap[top], heap[minChild] );
			ReheapDown( heap, minChild, numElements );
		}
	}
}

//PRE:	heap is a ptr to an array
//		current == subscript of the node to be considered
//		0 <= current < the capacity of the array pointed to by heap
//POST:	data in heap[current] has been moved up through the heap to its 	
//		appropriate location
void ReheapUp( int* heap, int current )  {
	int parent;
	
	if(current >= 0 && current < size) {
		parent = (current - 1)/2; // get parent of current
		// if parent is greater than child swap and start again from parent index
		if(heap[parent] > heap[current]) {
			swap( heap[parent], heap[current]);
			ReheapUp(heap, parent);
		}
	}
	
}
	
//PRE:  data points to an array
//POST: The first size elements of arr are a minimum heap.
void BuildMinHeap( int* arr, int numElements) {
	int index;
	for( index = (numElements - 2) / 2; index >= 0; index-- )
		ReheapDown( arr, index, numElements );
}

//PRE:  The capacity of the array pointed to by heap
//POST: The first size elements of data have been sorted in descending order. 
void sort( int* heap, int numElements) {
	int swpIndx;
	BuildMinHeap( heap, numElements );  // Heapify algorithm	
	for( swpIndx = numElements - 1; swpIndx > 0; swpIndx-- )
	{
		swap( heap[0], heap[swpIndx] );
		ReheapDown( heap, 0, swpIndx );
	}
}

//PRE:  The capacity of the array pointed to by heap
//POST: The first size elements of heap are printed to the screen.
void printList( int* heap, int numElements )  {
	for( int i = 0; i < numElements; i++ )
		cout << heap[i] << " ";
	cout << endl;
}

//PRE:	heap is a ptr to an array
//		key is the value to be added to the heap
//		last is the subscript of the last element in the heap
//POST:	key has been added to the heap
void insert( int* heap, int key, int last) {
	++size;
	heap[++last] = key;
	ReheapUp(heap, last);
	printList(heap, size);
}

//PRE:	Element at top (root) of heap is to be removed from the heap
//POST:	Element has been removed from heap and true returned,
//		or the heap was empty and false returned
bool remove( int* heap, int last, int numElements) {
	if (heap[0] == NULL) return FALSE;
	
	heap[0] = heap[last];
	heap[last] = NULL;
	--size;
	ReheapDown(heap, 0, size);
	printList(heap, size);
	
	return TRUE;
}


int main() {
	int array[] = {7,6,5,4,3,2,1};
	heap = array;
	
	size = sizeof(heap)-1;
	
	BuildMinHeap(heap, size);
	printList(heap, size);
	
	insert(heap, 8, size-1);
	
	int temp = size;
	for(int i=0; i<temp; i++)
		remove(heap, size-1, size);
	
	for(int i=temp; i>0; i--)
		insert(heap, i, size-1);
	
	insert(heap, 0, size-1);
	insert(heap, -1, size-1);
	
	system("PAUSE");
	return 0;
}