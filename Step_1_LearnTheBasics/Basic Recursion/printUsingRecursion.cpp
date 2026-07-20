#include <iostream>
using namespace std;

// print name n times using recursion
void printName(int n) {
    // Base Condition
    if (n == 0) 
        return;

    cout << "Vikrant \n";
    printName(n-1);
    // we could also call it as printName(--n), but using post-decrement i.e., printName(n--) would be problematic 🤔
}

// print 1 to n using recursion
// while calling the function inside main, we will need to pass i as 1
void print1toN(int i, int n) {
    if (i > n)
        return;

    cout << i << " ";
    print1toN(i+1, n);
    // we can also call as print1toN(++i, n), but using post-increment i.e., print1toN(i++, n) would be problematic 🤔
}

// print n to 1 using recursion
void printNto1(int n) {
    if (n == 0)
        return;

    cout << n << " ";

    printNto1(--n);
    // printNto1(n-1);
}

// print 1 to n using backtracking
void print1toNBacktrack(int n) {
    if (n == 0)
        return;
    
    print1toNBacktrack(n-1);

    cout << n << " ";
}

// print n to 1 using backtracking
// while calling the function inside main, we will need to pass i as 1
void printNto1Backtrack(int i, int n) {
    if (i > n)
        return;
    
    printNto1Backtrack(i+1, n);

    cout << i << " ";
}

int main() {
    // printName(5);
    // print1toN(1, 5);
    // printNto1(5);
    // print1toNBacktrack(5);
    // printNto1Backtrack(1, 5);

    return 0;
}