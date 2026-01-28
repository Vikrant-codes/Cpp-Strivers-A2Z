#include <iostream>
using namespace std;

/*
<-- struct -->
• | A struct is a user-defined data type that groups different types of variables under one name.
• members : variables in struct are known as "members". 
• These members can be accessed with the dot operator (.) (also called "Class Member Access Operator").

### Basic syntax
struct structure_name {
    data_type member1;
    data_type member2;
    .....
};

• The members are declared inside the struct. By initializing the members, we can set default values for the members.

Example - 
----------------------------------
struct Student {
    int id;
    string name;
    float marks;
};
----------------------------------

>> Structure Variable : a variable defined with a user-defined struct.

### Declaration of struct variables
Syntax: structure_name variable_name;

Example - 
----------------------------------
Student s;
----------------------------------

### Initialization of structure variables
There are different ways to initialize struct variables

1️⃣ Declare first, assign later
----------------------------------
Student s;
s.id = 1;
s.name = "Rahul";
s.marks = 85.5;
----------------------------------
✔ Most basic
✔ Easy to understand
✘ Slightly verbose

2️⃣ Aggregate initialization (order matters)

----------------------------------
Student s = {1, "Rahul", 85.5};
----------------------------------

Or (modern style):
----------------------------------
Student s{1, "Rahul", 85.5};
----------------------------------
✔ Short
⚠ Order must match struct definition

3️⃣ Partial initialization
----------------------------------
Student s = {1, "Rahul"};
----------------------------------
Remaining members:
• marks → 0 (default-initialized)
✔ Useful when not all values are known

4️⃣ Using designated initializers (C++20)
----------------------------------
Student s = {
    .id = 1,
    .name = "Rahul",
    .marks = 85.5
};
----------------------------------
✔ Order doesn’t matter
✔ Very readable
⚠ Requires C++20

5️⃣ Using constructor
----------------------------------
struct Student {
    int id;
    string name;
    float marks;

    Student(int i, string n, float m) {
        id = i;
        name = n;
        marks = m;
    }
};

Student s(1, "Rahul", 85.5);
----------------------------------
✔ Best for complex logic
✔ Safer initialization

6️⃣ Default constructor (auto initialization)
----------------------------------
struct Student {
    int id = 0;
    string name = "NA";
    float marks = 0.0;
};

Student s;   // auto initialized
----------------------------------
✔ Clean
✔ Avoids uninitialized data

7️⃣ Copy initialization
----------------------------------
Student s1 = {1, "Rahul", 85.5};
Student s2 = s1;
----------------------------------
✔ Copies all members

8️⃣ Dynamic allocation (heap)
----------------------------------
Student* s = new Student{1, "Rahul", 85.5};
----------------------------------

Access:
----------------------------------
cout << s->name;
----------------------------------
⚠ Remember to delete s; (or prefer smart pointers)


### Quick comparison
| Method          | When to use               |
| --------------- | ------------------------- |
| Assign later    | Learning / clarity        |
| Aggregate `{}`  | Competitive programming   |
| Designated init | Readability (C++20)       |
| Constructor     | Real-world programs       |
| Default values  | Safety                    |
| Copy init       | Duplication               |
| Dynamic         | When lifetime must extend |
*/

struct Student {
    int rollNo;
    string name;
    float marks = 33.33;
    // by initializing a member, we can set a default value.
    // This value would remain same for all structure variables unless we explicitly change it for some particular variable
};

int main() {
    Student s1;
    s1.rollNo = 1;
    s1.name = "Alice";
    s1.marks = 83.42;
    
    Student s2 = {2, "Bob", 87.16};

    Student s3{3, "Charlie"};
    // marks for student s3 is not intialized so it would store default value which is 33.33

    cout << "Student 1 -> " << s1.rollNo << " __ " << s1.name << " __ " << s1.marks << '\n'; 
    cout << "Student 2 -> " << s2.rollNo << " __ " << s2.name << " __ " << s2.marks << '\n'; 
    cout << "Student 3 -> " << s3.rollNo << " __ " << s3.name << " __ " << s3.marks << '\n'; 

    return 0;
}