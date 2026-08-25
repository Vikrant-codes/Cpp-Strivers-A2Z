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

    // <-- Pre-Increment, Post-Increment, Pre-Decrement and Post-Decrement -->

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

    // <-- Bitwise Shift Operators -->

    // left shift (<<) : shifts the bits to the left by specified number of positions, fill the vacant places by zero.

    // right shift (>>) : shifts the bits to the left by specified number of positions, 
    // the vacant places introduced due to shifting are filled with the MSB of original number,
    // thus if original number was negative (MSB is 1), doing (>>), fills the vacant places with 1
    // for positive number (MSB is 0), so right shift fills the vacant places with 0

    // left shift by 1 bit operation is equivalent to multiplying by 2.
    // right shift by 1 bit operation is equivalent to dividing by 2.

    // thus, left shift `n` bits -> equivalent to -> multiplying by 2^n
    // right shift `n` bits -> equivalent to -> dividing by 2^n

    int b = 1;
    b = b << 31;    
    // bits are shifted 31 positions to left, initially b was 1, in binary terms: 00000000 00000000 00000000 00000001
    // left shifting by 31 bits made it:- 10000000 00000000 00000000 00000000
    // Now, this new value has MSB set to 1, which means it is a negative number, 
    // the compiler will thus now read it as -2147483648 (which is INT_MIN)
    // we can also understanding it as, left shift 31 bits is equivalent to multiplying by 2^31.
    // now, 1 * 2^31 = 1 * 2147483648 = 2147483648, but this value is beyond int range, 
    // so, the value is wrapped around and the value becomes -2147483648.

    cout << b << endl;      // -2147483648

    // now any further left shifts will results in zero
    b = b << 1;     // again doing left shift, makes the MSB 1 bit go to left and hence discarded, the number becomes 0
    cout << b << endl;      // 0

    // so, left shifting `1` total 31 + 1 = 32 bits gave us zero, but we performed it in two steps, first 31 shifts, then 1 shift

    // In C++, trying to left shift a standard 32-bit int by 32 bits or more results in Undefined Behavior (UB).
    // so we can't guarantee what happens when we do int_var << 32

    int c = 1;
    c = c << 32;
    // compiler gives warning: `warning: left shift count >= width of type [-Wshift-count-overflow]` 
    cout << c << endl;      // undefined behavior

    unsigned int a = 2147483648;        // 2147483648 = 2 ^ 31
    cout << (a >> 30) << endl;          // equivalent to 2147483648 / (2 ^ 30) = (2 ^ 31) / (2 ^ 30) = 2

    return 0;
}