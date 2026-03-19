#include <bits/stdc++.h>
using namespace std;

/*
>> 🧠 What is operator()?
- It is a special function inside a class/struct that lets us call an object like a function.
- It lets an object behave like a function.

✅ Basic Example
    class Add {
    public:
        int operator()(int a, int b) {
            return a + b;
        }
    };

Usage:
    Add obj;
    cout << obj(2, 3);  // 5

🔍 How it works?
    obj(2, 3);
👉 This looks like a function call
But actually it is:
    obj.operator()(2, 3);

🧠 So: operator() defines what happens when you write obj(...)

🚀 What is a Functor?
- A functor (function object) is: A class/struct that defines operator() → so its objects behave like functions
👉 Functor = Objects that behave like functions
In the above example, the class 'Add' is a functor.
*/

/*
🔥 Difference: operator() vs Constructor

| Feature                      | `operator()`                          | Constructor             |
| ---------------------------- | ------------------------------------- | ----------------------- |
| Purpose                      | Makes object callable like a function | Initializes object      |
| Name                         | Always `operator()`                   | Same as class name      |
| Return type                  | Has return type                       | No return type          |
| When called                  | When you do `obj()`                   | When object is created  |
| Can take arguments           | Yes                                   | Yes                     |
| Can be called multiple times | Yes                                   | Only once at creation   |

⚡ Key intuition
- Constructor → “object is being created”
- operator() → “object is being used like a function”
*/

// Example to show the difference between constructor and operator
struct Demo {
    // Constructor
    Demo(int x) {
        cout << "Constructor called with " << x << endl;
    }

    // operator()
    void operator()(int y) {
        cout << "operator() called with " << y << endl;
    }
};


int main() {
    Demo d(10);   // constructor called
    d(20);        // operator() called

    return 0;
}