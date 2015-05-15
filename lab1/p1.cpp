#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(void) {
    ifstream in("first_file"); // Open for reading
    ofstream out("copy_of_first"); // Open for writing
    string s;
    while(getline(in, s)) // Discards newline char
        out << s << "\n"; // ... add it to the new file
    cout << "End of program\n";
    return 0;
}
