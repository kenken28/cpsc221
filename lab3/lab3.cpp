#include <iostream>
#include <time.h>
#define NUM_ELEMENTS 5

using namespace std;

int bs( int* array );
int bs_optimized( int* array );
void swap( int& a, int& b );
void genArray( int* array );
void printArray( int* array );

int main() {
	int* A = new int[NUM_ELEMENTS];
	genArray(A);
	int* B = new int[NUM_ELEMENTS];
	
	for(int i=0; i<NUM_ELEMENTS; i++){
		B[i]=A[i];
	}
	
	printArray(A);
	int comps = bs(A);
	printArray(A);
	cout << "number of comparisons A: " << comps << endl;
	
	comps = bs_optimized(B);
	printArray(B);
	cout << "number of comparisons B: " << comps << endl;
	
	delete []A;
	delete []B;
    return 0;
}


int bs( int* array ) {
	bool swapped;
	int numComps = 0;
	do{
		swapped = false;
		for(int i=0; i<(NUM_ELEMENTS-1); i++) {
			if (array[i] > array[i+1]) {
				swap(array[i], array[i+1]);
				swapped = true;				
			}
			numComps++;
		}
	} while(swapped);
	
	return numComps;
}

int bs_optimized( int* array ) {
	bool swapped;
	int numComps = 0, n = NUM_ELEMENTS;
	
	do{
		n--;
		cout << "n: " << n << endl;
		swapped = false;
		for(int i=0; i<n; i++) {
			if (array[i] > array[i+1]) {
				swap(array[i], array[i+1]);
				swapped = true;				
			}
			printArray(array);
			numComps++;
			cout << "numComps: " << numComps << endl;
		}
	} while(swapped);
	
	return numComps;
}

void swap( int& a, int& b ) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void genArray( int* array ) {
	srand(time(0));
	for (int i=0; i<NUM_ELEMENTS; i++) {
		array[i] = rand()%(20)-10;
		cout << array[i] << endl;
	}
}

void printArray( int* array ) {
	for (int i=0; i<NUM_ELEMENTS; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}