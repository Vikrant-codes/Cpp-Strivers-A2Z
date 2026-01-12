#include <iostream>
#include <cmath>    // for math functions like pow

using namespace std;

int main() {
    // max() & min() functions are available in std namespace
    cout << "max of 3 & 5 : " << max(3,5) << '\n';
    cout << "min of 3 & 5 : " << min(3,5) << '\n';

    cout << "2 raised to the power 3 : " << pow(2, 3) << '\n'; 
    cout << "square root of 100 : " << sqrt(100) << '\n';

    cout << "absolute value of -13 : " << abs(-13) << '\n';

    cout << "rounded value of 7.9 : " << round(7.9) << '\n';
    cout << "ceil value of 7.9 : " << ceil(7.9) << '\n';
    cout << "floor value of 7.9 : " << floor(7.9) << '\n';

    // Practice problem to find hypotenuse of a right-angled traingle given its base & perpendicular
    int a, b;
    cout << "Enter the two sides of the triangle : ";
    cin >> a >> b;

    // c ^ 2 = a ^ 2 + b ^ 2     <->    hypotenuse ^ 2 = base ^ 2 + perpendicular ^ 2
    double c = sqrt(pow(a, 2) + pow(b, 2));
    cout << "Base : " << a << " & Perpendicular : " << b << '\n';
    cout << "Hypotenuse : " << c;

    return 0;
}