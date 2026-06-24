// Print all prime factors of a number (positive integer) n

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// helper method to check whether a number is prime or not
bool isPrime(int x) {
    if (x < 2) return false;

    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;

    return true;
}

// Naive Approach :- Time Complexity : O(n * sqrt(n)) __ Space Complexity : O(1)
/*
For each number in range 1 to n
- Check if it is a divisor of n and is a prime number.
- Add such prime factors to the answer vector or display them.

>> Complexity Analysis
-> Time Complexity : O(n * sqrt(n))
- O(n) to check for every number in range [1, n].
- prime check takes O(sqrt(n))
- Thus, overall O(n * sqrt(n))

-> Space Complexity : O(1)
- A ans vector is used to store the prime factors : O(k), where k = no. of prime factors of n
- No other extra space is used
- Since ans vector is used to store the answer, it is not considered as extra space
- Thus, Space Complexity : O(1)
*/
void printPrimeFactorsNaive(int n) {
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && isPrime(i)) {
            ans.push_back(i);
        }
    }
    
    // print the factors
    for (int x : ans) 
        cout << x << " ";
    cout << endl;
}

// Better Approach :- Time Complexity : O(sqrt(n) * 2 * sqrt(n)) = O(2 * n) ~ O(n) __ Space Complexity : O(1)
/*
We already know how to get all the divisors of a number in O(sqrt(n)) time. 
So, we use that approach to get the divisors quickly.
If one of the divisors is 'i', then other will be 'n/i'. These i & n/i can be together called as divisor pairs of n.
Out of these two divisors from the pair, we will add only those divisors in the ans vector which are prime.
So, we need to check prime for both of the divisors for each divisor pair iteration.

>> Time Complexity Analysis 
- The outer loop runs for O(sqrt(n)) iterations : O(sqrt(n))
- Prime Check will be done only if the current number of the iteration is a divisor of n.
  Prime check takes another O(sqrt(n)) but it is not necessary that this will be checked for all numbers in the iterations.
  If in the range [1, sqrt(n)] there are k divisors, then for those k divisors, 
  prime check will be done twice (once for divisor 'i' & another time for divisor 'n/i').
  So, total two prime checks for each divisor pair : O(2 * sqrt(n))
  But, this check will not be done for all iteration of the outer loop since prime check will be done only for divisors.
- So, the exact time complexity of the code can't be guessed. 
- Appromixate Time Complexity = O(sqrt(n) * 2 * sqrt(n)) = O(2 * sqrt(n) * sqrt(n)) = O(2 * n)  
*/
void printPrimeFactorsBetter(int n) {
    vector<int> ans;

    for (int i = 1; i*i <= n; i++) {
        // find a divisor pair ... if a number i divides 'n', then its divisor pair is 'n / i'
        if (n % i == 0) {
            // check if i is prime
            if (isPrime(i)) 
                ans.push_back(i);

            // check for n/i
            if (n / i != i && isPrime(n/i)) 
                ans.push_back(n/i);
        }
    }

    sort(ans.begin(), ans.end());       // optional, used to just sort the prime factors
    // print the factors
    for (int x : ans) 
        cout << x << " ";
    cout << endl;
}

// Efficient Approach :- Time Complexity : Worst-case -- O(n)
/*
This approach is implemented like how we used to find the prime factorization of a number.
We used to divide it with a prime factor till division was possible and then would would move to next divisors.
Ex- assume n = 780
since 780 is divisible by 2, we divide it by 2, n becomes 780 / 2 = 390
again divide by 2, n becomes 390 / 2 = 195
Can't divide by 2 anymore, so we move to 3
now divide by 3, n becomes 195 / 3 = 65
Can't divide by 3 anymore, so move to 4... 4 doesn't divide 65 so move to 5
divide by 5, n becomees 65 / 5 = 13
Now no other numbers till 13 will divide 13, we skip the numbers 6 to 12 and move to 13
divide by 13, n becomes 13 / 13 = 1.

While dividing, we add all the divisors which divided n to the answer vector.

So, for a large number like 780, we only needed to check for divisors upto 13 only.
This works efficiently but there is a small issue.
For large numbers which are prime like n = 37, the number 'n' won't be divisible by any other number in the range [2, n).
So, for that case, the code will run for complete 'n' iterations, thus making the worst case complexity O(n) 
*/
void printPrimeFactorsEff(int n) {
    vector<int> ans;

    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(i);

            while (n % i == 0) 
                n = n / i;
        }
    }

    // my implementation
    /*
    int i = 2;
    while (n != 1) {
        if (n % i == 0) {
            ans.push_back(i);

            while (n % i == 0) 
                n = n / i;
        }
    }
    */

    // print the factors
    for (int x : ans) 
        cout << x << " ";
    cout << endl;
}

// Optimal Approach :- Time Complexity : O(sqrt(n) * log n)
/*
This approach corrects the short-comings of the previous approach. 
Instead of looping till n while updating n's value. We loop till sqrt(n), 
that way would still give us the prime divisors if available.
As for the case when n itself is prime, the loop will run for sqrt(n) and n would remain unchanged instead of becoming 1
So outside the loop, we will check if n is not equal to 1, 
in that case, we will add this current value of n to the answer vector.
*/

void printPrimeFactors(int n) {
    vector<int> ans;

    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(i);

            while (n % i == 0) 
                n = n / i;
        }
    }

    if (n != 1) ans.push_back(n);

    // print the factors
    for (int x : ans) 
        cout << x << " ";
    cout << endl;
}


int main() {

    return 0;
}