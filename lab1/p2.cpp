#include <iostream>

using namespace std;

float circle_area(float radius); // declare function before main()

int main(void) {
    float circle_radius;
    cout << "Enter radius:" << endl;
    cin >> circle_radius;
    cout << circle_area(circle_radius) << endl;
    return 0;
}

float circle_area(float radius) {
    return 3.14159 * radius * radius; // = pi * r^2
}
