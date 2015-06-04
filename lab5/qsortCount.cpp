#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

<<<<<<< HEAD
int * x;
int comps = 0;

void swap( int & a, int & b ) {
  int tmp = a;
  a = b;
  b = tmp;
}

int randint( int a, int b ) {
  return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
  int i, m;
  if (a >= b) return;
  swap(x[a], x[randint(a,b)]);
  m = a;
  for (i = a+1; i <= b; i++) {
    if (x[i] < x[a])
      swap(x[++m], x[i]);
	comps++;
  }
  swap(x[a],x[m]);
  quicksort(a, m-1);
  quicksort(m+1, b);
}

int qc(int n) {
	if (n<=1) return 0;
	int i = randint(0, n);
	return n-1 + qc(i) + qc(n-i-1); //recurrence relation yay wikipedia
}

int main( int argc, char *argv[] ) {
  srand(time(0));

  // change the following code
  x = new int[1000];
  
  for(int j=0; j<100; ++j) {
	  for( int i=0; i<1000; ++i ) {
		x[i] = rand() % 1000;
	  }

	  quicksort(0, 1000);
	  /*for( int i=0; i<1000; ++i ) {
		cout << x[i] << " ";
	  }*/
  }
  comps /= 100;
  cout << endl;
  cout << "Number of Comparisons:" << comps << endl;
  comps = qc(1000);
  cout << "Number of Predicted Comparisons:" << comps << endl;

  delete[] x;
  return 0;
}
=======
int * x, comps = 0;

void swap( int & a, int & b ) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint( int a, int b ) {
	return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
	int i, m;
	
	if (a >= b) return;
	
	swap(x[a], x[randint(a,b)]);
	m = a;
	
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a])
			swap(x[++m], x[i]);
		comps++;
	}
	
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}


int qc(int n) {
	if (n<=1) return 1;
	int i = randint(0, n);
	return (n-1 + qc(i)+qc(n-i-1));
}


int main( int argc, char *argv[] ) {
	srand(time(0));

	// change the following code
	x = new int[1000];

	for( int j=0; j<100; ++j ) {
		for( int i=0; i<1000; ++i ) {
			x[i] = rand() % 1000;
		}

		quicksort(0, 999);
	}
	comps /= 100;
	
	
	cout << "last sorted array: " << endl;
	for( int i=0; i<1000; ++i ) {
		cout << x[i] << " ";
	}

	delete[] x;

	cout << endl << "average comps = " << comps << endl
			 << "calculated comps = " << qc(999)<< endl;

	return 0;
}
>>>>>>> origin/master
