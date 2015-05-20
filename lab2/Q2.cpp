#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 15;
    int *p1, *p2;
    
    p1 = &x;
    cout << "x: " << x << ";  y: " << y << endl;
    p2 = &y;
    cout << "x: " << x << ";  y: " << y << endl;
    *p1 = 5;
    cout << "x: " << x << ";  y: " << y << endl;
    *p1 = *p2;
    cout << "x: " << x << "; y: " << y << endl;
    p2 = p1;
    cout << "x: " << x << "; y: " << y << endl;
    *p1 = *p2+10;
    cout << "x: " << x << "; y: " << y << endl;
    
    return 0;
}
