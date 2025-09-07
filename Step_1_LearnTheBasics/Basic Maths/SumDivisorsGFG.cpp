/*
GFG <-- Sum 1 to n Divisors --> Difficulty: Easy

Given a positive integer n, The task is to find the value of Σi F(i) where i is from 1 to n and 
function F(i) is defined as the sum of all divisors of i.

Examples:-

Input: n = 4                Output: 15
Explanation:
F(1) = 1, F(2) = 1 + 2 = 3, F(3) = 1 + 3 = 4, F(4) = 1 + 2 + 4 = 7
So, F(1) + F(2) + F(3) + F(4) = 1 + 3 + 4 + 7 = 15

*/
#include<bits/stdc++.h>
using namespace std;

// Brute Force : Complexity --> O(n✓n)
int sumOfDivisors(int n) {
    int sum = 0;
    for(int i=1; i <= n; i++){
        int sum_div = 0;
        cout << "Divisors of " << i << " : ";
        for(int j=1; j*j <= i; j++){
            if(i % j == 0){
                cout << j << " ";
                sum_div += j;
                if(i/j != j){
                    sum_div += i/j;
                    cout << i/j << " ";
                }
            }
        }
        cout << "__ Sum : " << sum_div << endl;
        sum += sum_div;
    }
    return sum;
}

// Better Approach : Complexity --> O(n)
int sumDivisors(int n) {
    int sum = 0;
    for(int i = 1; i<=n; i++){
        // a number i will have exactly (int)(n/i) multiples upto 'n' ... so it will be a divisor of (int)(n/i) numbers upto n
        // thus while calculating sum of divisors the number i will be included (int)(n/i) this many times .... 
        // Now sum of the number 'i' '(int)(n/i)' times will be i * (int)(n/i)
        // For ex --> let n = 4 and i = 3... now (int)(n/i) = 1 ... thus 3 is a divisor of only one number in the range [1,n] 
        // so it would be added (int)(n/i) times while calculating sum of Divisors.. Thus its total contribution to the sum would be i * (int)(n/i)
        // i.e. 3 * (int)(4/3) = 1
        // For i=1 : Contribution of 1 = 1 * (int)(4/1) = 4.. multiples are (1,2,3,4) , thus it's a divisor of (1,2,3,4) and hence would be added 4 times
        // For i=2 : Contribution of 2 = 2 * (int)(4/2) = 4.. multiples are (2,4) , thus it's a divisor of (2,4) and hence would be added 2 times
        // For i=3 : Contribution of 3 = 3 * (int)(4/3) = 3.. multiple are (3) , thus it's a divisor of (3) and hence would be added 1 time
        // For i=4 : Contribution of 4 = 4 * (int)(4/4) = 4.. multiple are (4) , thus it's a divisor of (4) and hence would be added 1 time
        // Total sum = 4 + 4 + 3 + 4 = 15

        sum += i * (int)(n/i);
    }
    return sum;
}

int main(){
    int no;
    cout << "Enter the number : ";
    cin >> no;
    int ans = sumOfDivisors(no);
    cout << "Sum 1 to n Divisors : " << ans << endl;
    return 0;
}