#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#define LEN_OF_KEY 8
using namespace std;

string genKey() {
  char key[LEN_OF_KEY];
  char alphaCAP[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i=0; i<LEN_OF_KEY; ++i) {
    key[i] = alphaCAP[rand() % (sizeof(alphaCAP) - 1)];
  }
  string keyStr(key, LEN_OF_KEY);
  return keyStr;
}


int main ( int argc, char **argv ) {
  int numOfKeys;
  ofstream myfile;
  srand(time(0));
  
  if(argc == 3) {
    numOfKeys = atoi(argv[1]);
    myfile.open(argv[2]);
    if (myfile.is_open()){
      for (int i=0; i<numOfKeys; ++i) {
        myfile << genKey() << " " << i+1 << "\n";
      }
      myfile.close();
    } else {
      cerr << "Unable to open file"<< endl;
      return(-1);
    }
    return 0;
  } else {
    cerr << "Usage: ./" << argv[0] << " numberOfKeys filename" << endl;
    return(-1);
  }
}