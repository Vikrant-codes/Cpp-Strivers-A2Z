#include <bits/stdc++.h>
using namespace std;

/*
1️⃣ Non-Static Members
- These belong to each object of the class.
- Every object gets its own copy.

Example:
    #include <iostream>
    using namespace std;

    class Student {
    public:
        string name;   // non-static variable

        void show() {  // non-static function
            cout << name << endl;
        }
    };

Usage:
    Student s1;
    Student s2;

    s1.name = "Vikrant";
    s2.name = "Rahul";

    s1.show();   // Vikrant
    s2.show();   // Rahul
    
What happens in memory?
- s1 has its own name
- s2 has its own name
Each object stores its own data.

2️⃣ Static Members
- These belong to the class itself, not to objects.
- Only one copy exists in memory.
- Shared by all objects.

Example:
    class Student {
    public:
        static int totalStudents;
    };

    int Student::totalStudents = 0;   // definition outside class

Usage:
    Student s1, s2;
    Student::totalStudents = 2;
    cout << Student::totalStudents;

Only one totalStudents exists — shared by all objects.

--> Static Function Example
    class Math {
    public:
        static int add(int a, int b) {
            return a + b;
        }
    };

Usage:
    cout << Math::add(2, 3);

- No object needed to use static members.

🔥 Key Difference
| Feature                       | Non-Static     | Static         |
| ----------------------------- | -------------- | -------------- |
| Belongs to                    | Object         | Class          |
| Copies in memory              | One per object | Only one total |
| Has `this` pointer            | Yes            | No             |
| Can access non-static members | Yes            | No             |
| Needs object to call          | Yes            | No             |

✅ When to Use Non-Static
When data is different for every object
Example:
- Student name
- Account balance
- Node value in linked list
Each object must have its own copy.

✅ When to Use Static
When data is common to all objects
Examples:
- Count of objects created
- Utility/helper functions
- Shared configuration
- Global-like data but scoped inside class

Example Showing Why Static Matters

    class Counter {
    public:
        static int count;

        Counter() {
            count++;
        }
    };

    int Counter::count = 0;

Usage:
    Counter c1;
    Counter c2;
    Counter c3;

    cout << Counter::count;  // 3

If count was non-static:
- Every object would have its own count
- It would always be 1
That would defeat the purpose.
*/

class Student {
public:
    static int totalStudents;

    int id;
    string name;

    Student(int x, string n) {
        id = x;
        name = n;
        totalStudents++;
    }
};

int Student::totalStudents = 0;             // definition outside class

int main() {
    cout << "Total Students : " << Student::totalStudents << '\n';
    
    Student s1(1, "Alice");
    Student s2(2, "Bob");
    
    cout << "Total Students : " << Student::totalStudents << '\n';

    return 0;
}