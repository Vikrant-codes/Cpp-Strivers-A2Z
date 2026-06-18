#include <bits/stdc++.h>
using namespace std;

// Comparators
/*
#1️. What is a Comparator?

A comparator is a function that tells sort how to decide the order between two elements.
For any two elements a and b, the comparator answers:
Should a come before b?
It returns:
- true → a should come before b
- false → b should come before a
So the comparator defines the sorting rule.

#2 Why do we need it?

By default, sort() arranges elements in ascending order using <.
Example:
    vector<int> v = {4, 1, 7, 2};
    sort(v.begin(), v.end());
Result: 1 2 4 7
Because default rule is: a < b
But what if we want:
- descending order?
- sort by absolute value?
- sort by frequency?
- sort pairs by second value?
Then we need a custom comparator.

#3. Why does sort have 3 parameters?

The general form is: sort(start_iterator, end_iterator, comparator);
Parameters:
start_iterator → where sorting starts => v.begin()
end_iterator → where sorting ends => v.end()
comparator (optional) → custom rule for ordering
If the comparator is not provided, sort uses the default rule:
    - ascending order (<)
    - for pair, it sorts by first element, then second.

#4. Very Important Understanding
Think of comparator like this:
When sorting two elements a and b, sort asks:
| "Should a be placed before b?"
The comparator function answers that.
If it returns true, a goes before b.
*/

// custom comparator to sort elements according to last digit
bool cmp (int a, int b) {
    int lda = a % 10;           // last digit of a
    int ldb = b % 10;           // last digit of b

    return lda < ldb;
    // returns true if last_digit of a < last_digit of b, i.e. if b's last_digit is greater
    // Thus, if false (if a's last_digit is greater), then, a comes after b.
    // if true (if a's last_digit is smaller), then, a comes before b.
    // Thus, this return statement sorts the vector in increasing order according to last digit of numbers

    // return lda > ldb;
    // returns true if last_digit of a > last_digit of b
    // Thus, a comes before b, if a's last digit is greater than b.
    // Thus, this return statement sorts the vector in decreasing order according to last digit of numbers
}

int main() {
    vector<int> v = {9,1,5,3,6,4,8,2,7};
    for (int &x : v) cout << x << " ";
    cout << '\n';
    
    // Normal Sorting
    sort(v.begin(), v.end());
    for (int &x : v) cout << x << " ";
    cout << '\n';

    // Lambda Function
    /*
    A lambda function is just a function written directly inside another function.
    Instead of writing:
        bool cmp(int a, int b) {
            return a > b;
        }
    You can write it inline:
        [](int a, int b) {
            return a > b;
        }
    This is called a lambda expression.
    
    # General lambda syntax
        [capture](parameters) {
            body
        }
    
    >> Why Use Lambda Instead of Normal Function?
    Normal function: Defined separately, Reusable, Takes more space
    Lambda: Written where needed, Cleaner, Used when comparator is small
    In competitive programming, lambdas are preferred because they are quick and clean.
    */

    // Sorting in descending order using lambda function as custom comparator
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    /*
    What is happening?
    During sorting, sort() does comparisons like:
    cmp(9, 1) → 9 > 1 → true.  --> So 9 should come before 1.
    cmp(1, 5) → 1 > 5 → false. --> So 5 should come before 1.
    */
    for (int &x : v) cout << x << " ";
    cout << '\n';

    // sorting by last digit using custom comparator 
    vector<int> v2 = {91, 83, 72, 48, 54};
    sort(v2.begin(), v2.end(), cmp);

    for (int &x : v2) cout << x << " ";
    cout << '\n';

    // Capture in lambda ?
    /*
    The [ ] part in a lambda is called the capture list.
    It tells the lambda:
    | Which variables from the outside scope it is allowed to use, and how.

    #1️. Why capture is needed
    A lambda is like a small function written inside another function.
    Normally, a function cannot access local variables of another function unless they are passed as parameters.
    Example:
        int x = 10;
        auto f = []() {
            cout << x;   // ❌ error
        };
        This gives an error because the lambda does not know what x is.
        To allow access, we capture it.
    
    #2. Capture by value [x]
        int x = 10;
        auto f = [x]() {
            cout << x;
        };
    Now the lambda gets a copy of x.
    Important:
    - The lambda uses its own copy.
    - Changing inside lambda does NOT change original variable

    #3️. Capture by reference [&x]
    The lambda refers to the original variable. Thus, change done inside the lambda function will appear outside

    #4. Capture all variables
    -> Capture all by value [=] : All used outer variables are copied. Example-
          int a = 5, b = 10;
          auto f = [=]() {
              cout << a + b;
          };

    -> Capture all by reference [&] : All variables are used by reference. Example- 
          auto f = [&]() {
            a++;
            b++;
          };

    #5. When capture becomes useful (real example)
    Suppose we want to sort a vector of numbers depending on how close the numbers are to some integer k.
        int k = 5;
        sort(v.begin(), v.end(), [k](int a, int b) {
            return abs(a - k) < abs(b - k);
        });
    The comparator in this example needs an external variable k and this is used inside the lambda expression by capturing it.

    # Simple intuition
    Think of capture list as:
    |"What outside variables should this lambda carry with it?"
    • [x] → take copy
    • [&x] → use original
    • [=] → copy everything used
    • [&] → reference everything used
    • [ ] → take nothing
    */

    // sorting a vector depending on how close the elements are to some integer k
    int k = 20;
    vector<int> v3 = {0, 3, 15, 18, 19, 21, 27, 31, 52};
    
    sort(v3.begin(), v3.end(), [k](int a, int b) {
        return abs(a - k) < abs (b - k);
        // abs(a - k) will be smaller than abs(b - k) if a is closer to k than b
        // Thus, a comes before b after sorting, if a is closer to k than b.
    });

    for (int &x : v3) cout << x << " ";
    cout << '\n';

    return 0;
}