#include <iostream>     /* cout, endl */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define num_elements 10

using namespace std;

void fill_array_old();
void fill_array(int first, int inc);
int RNG();

int *array1 = new int[num_elements];

int main(void) {
    int answer, myGuess;
    
    cout << "\nPart 1:" << endl;
    //fill_array_old();
    fill_array(4,2);
    delete []array1;
    cout << endl;
    
    cout << "Part 4:" << endl << "Make a guess between 1 and 10: ";
    answer = RNG();
    do {
        cin >> myGuess;
        
    } while (myGuess != answer);
    cout << "Correct! " << answer << " is the right answer.\n" << endl;
    
    return 0;
}


void fill_array_old() {
    for (int i=0; i<num_elements; i++) {
        array1[i] = 1 + i;
        cout << "array1[" << i << "] = " << array1[i] << endl;
    }
}

void fill_array(int first, int inc){
    for (int i=0; i<num_elements; i++) {
        array1[i] = first + i*inc;
        cout << "array1[" << i << "] = " << array1[i] << endl;
    }
}

int RNG() {
    srand(time(0));
    return (1 + rand()%10); //format is (stating_number + rand()%range_of_number)
}