#include "hash.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Hash::Hash(int _m) {
  //constructor
  m = _m;
  totalProbes = 0;
  numInserts = 0;
  table = new int [m];
  for( int i=0; i<m; i++ ) {
    table[i] = EMPTY;
  }
}

Hash::~Hash() {
  //deconstructor
  delete[] table;
}

void Hash::tallyProbes(int p) {
  // Add the number of probes, p, for one insert operation to the tally.
  totalProbes += p;
  numInserts++;
}

void Hash::printStats() {
  cout << "Average probes/insert = " <<
    (float)totalProbes / (float)numInserts << " = " <<
    totalProbes << "/" << numInserts << endl;
}

void Hash::qinsert(int k) {
  // Insert k in the hash table. 
  // Use open addressing with quadratic probing and hash(k) = k % m.
  int hashIndex = k % m;
  int newIndex = hashIndex;
  int prob = 0;
  
  while (table[newIndex] != EMPTY) {
    if (table[newIndex] == k || prob == m-1)
      return;
    newIndex = (hashIndex + ++prob*prob) % m;
  }
  
  table[newIndex] = k;
  tallyProbes(prob);
}

void Hash::linsert(int k) {
  // Insert k in the hash table. 
  // Use open addressing with linear probing and hash(k) = k % m.
  int hashIndex = k % m;
  int newIndex = hashIndex;
  int prob = 0;
  
  while (table[newIndex] != EMPTY) {
    if (table[newIndex] == k || prob == m-1)
      return;
    newIndex = (hashIndex + ++prob) % m;
  }
  
  table[newIndex] = k;
  tallyProbes(prob);
}

void Hash::print() {
  // Print the content of the hash table.

  for (int i=0; i<m; i++) {
    cout<<"["<<i<<"] ";
    if( table[i] != EMPTY )
      cout << table[i];
    cout << endl;
  }
}

int main( int argc, char *argv[] ) {
  int n, m;

  srand(time(0));

  if( argc == 4 && argv[1][0] == 'q' ) {	// quadratic
    n = atoi(argv[2]);
    m = atoi(argv[3]);
    Hash H(m);
    for( int i=0; i<n; ++i ) {
      H.qinsert( rand() + 1 );
    }
    //    H.print();
    cout << "Quadratic: ";
    H.printStats();
  } else if( argc == 3 ) {			// linear
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    Hash H(m);
    for( int i=0; i<n; ++i ) {
      H.linsert( rand() + 1 );
    }
    //    H.print();
    cout << "Linear: ";
    H.printStats();
  } else {
    cerr << "Usage: " << argv[0] << " [q] numberOfKeys sizeOfTable" << endl;
    exit(-1);
  }
}
