// In C++, pair is a utility class from the <utility> header that allows storing two values together, possibly of different types.
// Syntax : pair<T1, T2> name;          where: T1 = Type of first element, T2 = Type of second element

#include <iostream>
#include <utility>  // Required for pair
using namespace std;

int main() {
    pair<int, string> demo_pair(1, "Wizard");
    cout << "First: " << demo_pair.first << endl;  // Access first element
    cout << "Second: " << demo_pair.second << endl; // Access second element

    // Different Ways to Initialize a pair
    pair<int, double> p1(10, 3.14);  // Using constructor
    pair<int, string> p2 = make_pair(2, "Bob");  // Using make_pair() : make_pair() helps create pairs quickly.
    pair<char, bool> p3 = {'A', true};  // Using braces
    /* 
    Que ❓How make_pair() Helps Create Pairs Quickly?
    make_pair() automatically deduces the data types of the pair elements, making code cleaner and reducing the need for explicit type specification.
    */
    auto p = make_pair(1, "Alice");  // Type is automatically deduced
    cout << p.first << " " << p.second << endl;

    // Modifying Pair Values
    p1.first = 20;   // Change first element
    p1.second = 2.71; // Change second element

    // Nested Pairs : You can have pairs inside pairs!
    pair<int, int> inner_pair = {36, 63};
    pair<int, pair<int, int>> nested_pair = {1, inner_pair};
    pair<int, pair<string, double>> nested_two = {7, {"Wizard", 3.14}};
    cout << nested_pair.first << " " << nested_pair.second.first << " " << nested_pair.second.second << endl;
    cout << nested_two.first << " " << nested_two.second.first << " " << nested_two.second.second << endl;

    
    // Pair Array : Array having pairs as elements
    pair<int, int> arr[] = { {1,1}, {2,4}, {3,9} };
    cout << "Pair Array Elements" << endl;
    for(int i = 0; i<3; i++) {
        cout << "Pair " << i+1 << " : " << arr[i].first << " , " << arr[i].second << endl;

    }
    
    return 0;
}

