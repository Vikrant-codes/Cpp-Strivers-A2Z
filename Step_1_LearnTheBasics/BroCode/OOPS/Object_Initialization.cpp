#include <iostream>
using namespace std;

// <-- Initialization of class objects -->
/*
1. Member-wise assignment after declaration
------------------------------------
    class Student {
    public:
        int id;
    }

    Student s;
    s.id = 10;
------------------------------------

2. Using constructors (most common)
------------------------------------
    class Student {
    public:
        int id;
        Student(int i) {
            id = i;
        }
    };

    Student s(10);
------------------------------------

3. Default constructor
------------------------------------
    class Student {
    public:
        Student() {
            id = 0;
        }
        int id;
    };

    Student s;
------------------------------------

4. Using default member initializers
------------------------------------
    class Student {
    public:
        int id = 0;
    };

    Student s;
------------------------------------

5. Copy initialization (copy constructor)
------------------------------------
    Student s1(10);
    Student s2 = s1;
------------------------------------

6. Dynamic allocation (heap)
------------------------------------
    Student* s = new Student(10);
------------------------------------

7. Uniform initialization (brace with constructor)
------------------------------------
    Student s{10};
------------------------------------
*/

// class having constructor
class Student1{
public:
    int id;
    string name;

    // constructor
    Student1(int i, string n) {
        id = i;
        name = n;
    }
};

// class having default constructor
class Student2{
public:
    int id;
    string name;

    // default constructor
    Student2() {
        id = 0;
        name = "no-name";
    }
};

// class with default member initializers
class Student3{
public:
    int id = 0;
    string name = "no-name";
};


// ### Comparison between different methods for initialization of struct variables & class objects
/*
| Aspect                                   | `struct` variable initialization            | `class` object initialization        |
| ---------------------------------------- | ------------------------------------------- | ------------------------------------ |
| Constructor-based initialization         | Optional                                    | ✅ Primary method                    |
| Member-wise assignment after declaration | ✅ Allowed                                  | ❌ Not allowed if constructor exists |
| Aggregate `{}` initialization            | ✅ Allowed (if no user-defined constructor) | ❌ Not allowed if constructor exists |
| Designated initializers (C++20)          | ✅ Allowed                                  | ❌ Not allowed                       |
| Default member initializers              | ✅ Allowed                                  | ✅ Allowed                           |
| Copy initialization                      | ✅ Allowed                                  | ✅ Allowed                           |
| Dynamic allocation with `{}`             | ✅ Allowed                                  | ⚠ Only via constructors              |
*/

int main() {
    // Constructor-based initialization
    Student1 s1(1, "Alice");
    cout << s1.id << " : " << s1.name << '\n';
    
    // Copy initialization (copy constructor)
    Student1 s2 = s1;
    cout << s2.id << " : " << s2.name << '\n';

    // Default constructor based initialization
    Student2 s3;
    cout << s3.id << " : " << s3.name << '\n';

    // Using default member initializers
    Student3 s4;
    cout << s4.id << " : " << s4.name << '\n';

    // Member-wise assignment after declaration
    Student3 s5;
    s5.id = 2;
    s5.name = "Bob";
    cout << s5.id << " : " << s5.name << '\n';

    return 0;
}