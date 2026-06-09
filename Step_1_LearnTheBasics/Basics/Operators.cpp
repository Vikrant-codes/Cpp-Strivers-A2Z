#include <iostream>
using namespace std;

/*
1️⃣ Arithmetic Operators
| Operator | Meaning                            |
| -------- | ---------------------------------- |
|  +       | Addition                           |
|  -       | Subtraction                        |
|  *       | Multiplication                     |
|  /       | Division                           |
|  %       | Modulus (remainder, integers only) |

2️⃣ Relational (Comparison) Operators
| Operator | Meaning               |
| -------- | --------------------- |
|  ==      | Equal to              |
|  !=      | Not equal to          |
|  >       | Greater than          |
|  <       | Less than             |
|  >=      | Greater than or equal |
|  <=      | Less than or equal    |

3️⃣ Logical Operators
| Operator | Meaning     |
| -------- | ----------- |
|  &&      | Logical AND |
|  ||      | Logical OR  |
|  !       | Logical NOT |

4️⃣ Bitwise Operators
| Operator | Meaning     |
| -------- | ----------- |
|  &       | Bitwise AND |
|  |       | Bitwise OR  |
|  ^       | Bitwise XOR |
|  ~       | Bitwise NOT |
|  <<      | Left shift  |
|  >>      | Right shift |

5️⃣ Assignment Operators
| Operator | Meaning                |
| -------- | ---------------------- |
|  =       | Assign                 |
|  +=      | Add and assign         |
|  -=      | Subtract and assign    |
|  *=      | Multiply and assign    |
|  /=      | Divide and assign      |
|  %=      | Modulo and assign      |
|  <<=     | Left shift and assign  |
|  >>=     | Right shift and assign |
|  &=      | Bitwise AND and assign |
|  |=      | Bitwise OR and assign  |
|  ^=      | Bitwise XOR and assign |

6️⃣ Increment / Decrement Operators
| Operator | Meaning        |
| -------- | -------------- |
|  ++      | Increment by 1 |
|  --      | Decrement by 1 |
(Both prefix and postfix) --> ++x : pre-increment, x++ : post-increment, --x : pre-decrement, x-- : post-decrement

7️⃣ Conditional (Ternary) Operator
| Operator | Meaning               |
| -------- | --------------------- |
|  ?:      | Short form of if-else |
syntax -->  condition ? (expression if true) : (expression if false);
*/

/*
8️⃣ Size / Type Operators
| Operator           | Meaning                     |
| ------------------ | --------------------------- |
|  sizeof            | Size of variable/type       |
|  typeid            | Type information            |
|  static_cast       | Compile-time cast           |
|  dynamic_cast      | Runtime cast (polymorphism) |
|  const_cast        | Add/remove const            |
|  reinterpret_cast  | Low-level cast              |

9️⃣ Member / Scope Operators
| Operator | Meaning                   |
| -------- | ------------------------- |
|  .       | Access member             |
|  ->      | Access member via pointer |
|  ::      | Scope resolution          |
:: scope resolution operator is used to access a global variable when a local variable has the same name, 
or to access class members, namespaces, etc.

🔟 Special Operators
| Operator | Meaning              |
| -------- | -------------------- |
|  &       | Address-of operator  |
|  *       | Dereference operator |
|  []      | Array subscript      |
|  ()      | Function call        |
|  ,       | Comma operator       |
|  new     | Dynamic allocation   |
|  delete  | Deallocation         |
*/

int main() {

    // Pre-Increment, Post-Increment, Pre-Decrement and Post-Decrement
    /*
    In C++, the increment (++) and decrement (--) operators come in two forms:
        Pre-increment / Pre-decrement: ++x, --x
        Post-increment / Post-decrement: x++, x--
    The difference is when the value is changed and what value the expression returns.
    */

    // 1. Pre-Increment (++x) :- How it works :- Increment x. Return the new value.
    int x = 10;
    int y = ++x;        // x : 11, y : 11  => y = ++x => x = x + 1 (x becomes 11) and then y = x (y also becomes 11)
    // equivalent to x = x + 1 and then y = x.

    // 2. Post-Increment (x++) :- How it works :- Return the old value. Increment x.
    x = 10;
    y = x++;            // x : 11, y : 10  => y = x++ => y = x (y becomes 10) and then x = x + 1 (x becomes 11)
    // equivalent to y = x and then x = x + 1.

    // 3. Pre-Increment (--x) :- How it works :- Decrement x. Return the new value. 
    x = 10;
    y = --x;            // x : 9, y : 9  => y = --x => x = x - 1 (x becomes 9) and then y = x (y also becomes 9)
    // equivalent to x = x - 1 and then y = x.

    // Post-Decrement (x--) :- How it works :- Return the old value. Decrement x.
    x = 10;
    y = x--;            // x : 9, y : 10  => y = x-- => y = x (y becomes 10) and then x = x - 1 (x becomes 9)
    // equivalent to y = x and then x = x - 1.

    // more examples 
    x = 5;
    cout << x++ << endl;        // output : 5, then x becomes 6
    cout << ++x << endl;        // output : 7, x = 7

    y = x++ + 2;        // x initial value = 7, y = x++ + 2 => y = 7 + 2 = 9 and x = x+1 = 8
    cout << y << " " << x << endl;


    // Guess the output
    x = 10;
    x = x++;   // x++ makes x value 11 but returns old value 10 which is assigned to x, so ultimately x remains 10
    x = x++;   // x remains 10
    x = x++;   // x remains 10
    x = ++x;   // ++x makes x value 11 and returns 11 which is assigned to x, so x becomes 11
    x = x++;   // x++ makes x value 12 but returns old value 11 which is assgined to x, so ultimately x remains 11
    cout << x << endl;  // 11

    // Guess the output 
    int i = 0;
    while (i--) {
        cout << i << " ";
    }
    cout << i << endl;
    // Output : -1
    // Reason :- Initially i = 0, in while condition, when checking for 1st time, it does i--,
    // so i-- returns value 0 and then decrements i by 1 making it -1. 
    // this returned 0 works as boolean false and exits the while loop (while loop don't iterate even for once).
    // after the loop, i is printed and its value is -1.

    return 0;
}