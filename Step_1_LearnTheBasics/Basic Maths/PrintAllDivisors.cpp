// GFG - All divisors of a Number : Easy

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// <-- printing all divisors of a number n -->

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
// Check for all numbers from 1 to n and print the number if it divides n completely.
void printDivisors(int n) {
    for (int i = 1; i <= n; i++)
        if (n % i == 0)
            cout << i << " ";
}

// Efficient Approach :- Time Complexity : O(sqrt(n)) __ Space Complexity : O(1)
// we can find the factors in pairs. For example, if 2 is a factor of 20, then 20/2 = 10 is also a factor of 20.
// using this, we can iterate from 1 to sqrt(n) and for every factor, we can print both the factors in the pair.
void printDivisors2(int n) {
    vector<int> factors;

    // O(sqrt(n)) -- finding factors in pairs
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (n / i != i) 
                factors.push_back(n / i);
        }
    }
    // Sort the factors in ascending order __ O(k log k) where k is the number of factors
    sort(factors.begin(), factors.end());

    // Print the factors __ O(k)
    for (int factor : factors) {
        cout << factor << " ";
    }
}

/*
GFG - All divisors of a Number : Easy

Given an integer n, return all the divisors of n in the ascending order.
 
Examples :-

Input : n = 20 __ Output: 1 2 4 5 10 20
Explanation: 20 is completely divisible by 1, 2, 4, 5, 10 and 20.

Input: n = 21191 __ Output: 1 21191
Explanation: As 21191 is a prime number, it has only 2 factors(1 and the number itself).

Constraints:- 1 ≤ n ≤ 10^9
*/

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
vector<int> getDivisorsNaive(int n) {
    vector<int> factors;
        
    for (int i = 1; i <= n; i++)
        if (n % i == 0)
            factors.push_back(i);
        
    return factors;
}

// Efficient Approach :- Time Complexity : O(sqrt(n)) + O(k log k) __ Space Complexity : O(1)
// where k is the number of factors
vector<int> getDivisors(int n) {
    vector<int> factors;
    
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            
            if (n / i != i)
                factors.push_back(n / i);
        }
    }
    
    sort(factors.begin(), factors.end());
    
    return factors;
}

/*
The below approach uses the vector::insert() method to insert the factors in the correct position in the vector, 
thus eliminating the need for sorting at the end. 
However, this approach is less efficient than the previous one 
because inserting elements in the middle of a vector has a time complexity of O(k),
where k is the number of elements in the vector, 
leading to an overall time complexity of O(sqrt(n) * k) which can be worse than O(sqrt(n) + k log k) when k is large.

vector<int> getDivisors(int n) {
    vector<int> v;
    int pos = 0;
    for(int i=1; i*i <= n; i++) {
        if (n % i == 0) {
            v.insert(v.begin()+pos, i);
            pos++;
            if (n/i != i) {
                v.insert(v.begin()+pos, n/i);
            }
        }
    }
    return v;
}
*/

// Using two vectors to store the smaller and larger factors separately, and then merging them at the end.
/*
Notice:
For n = 36
When iterating:
i = 1  -> 1, 36
i = 2  -> 2, 18
i = 3  -> 3, 12
i = 4  -> 4, 9
i = 6  -> 6

The small divisors (1,2,3,4,6) are already generated in increasing order.
The large divisors (36,18,12,9) are generated in decreasing order.

So, we can use 2 vectors to store the small and large divisors separately, 
and then merge them at the end to get the final list of divisors in increasing order.

This gives divisors in sorted order with:
- No sorting
- No costly inserts

This uses an extra vector to store the large divisors, 
but it is more efficient than sorting or inserting in the middle of the vector.
*/
vector<int> getDivisors(int n) {
    vector<int> small, large;
        
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            small.push_back(i);
            
            if (n / i != i)
                large.push_back(n / i);
        }
    }
    
    for (int i = large.size()-1; i >= 0; i--)
        small.push_back(large[i]);
    
    return small;
}

int main() {
    
    return 0;
}