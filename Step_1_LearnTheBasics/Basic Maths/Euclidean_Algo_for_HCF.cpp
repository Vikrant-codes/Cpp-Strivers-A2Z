#include<iostream>
using namespace std;

// Brute Approach : Best, Average, Worst Case --> O(min(n1, n2)) 
int getHCF(int n1, int n2){
    // int hcf = 1;
    // int mn = min(n1, n2);
    // for(int i = 2; i <= mn; i++) {
    //     if (n1 % i == 0 && n2 % i == 0){
    //         hcf = i;
    //     }
    // }
    // return hcf;

    // Better Approach : Worst Case -->  O(min(n1, n2))
    // we start checking from min(n1,n2) till 1 and return the first common divisor (number which divides both the given numbers) as it is the GCD..
    // This way we don't need to keep track of all divisors since we are looping from greater to smaller so return the first common divisor encountered
    int mn = min(n1, n2);
    for(int i = mn; i >= 1; i--) {
        if (n1%i==0 && n2%i==0) return i;
    }
}

// Subtraction-Based Euclidean Algorithm : gcd(a,b) = gcd(a−b, b) if a>b
// Steps :-
// 1) Replace the bigger number by bigger-smaller
// 2) Repeat the process until one number becomes zero
// 3) The remaining nonzero number is the GCD.
// Ex - gcd(12,9) = gcd(12-9, 9) = gcd(3,9) = gcd(9,3) = gcd(9-3,3) = gcd(6,3) = gcd(6-3,3) = gcd(3,3) = gcd(3-3,3) = gcd(0,3) = 3
int subEuclidean(int n1, int n2){
    while (n1 != n2){
        if (n1 < n2) n2 = n2-n1;
        else n1 = n1-n2;
    }
    // We get zero when both the numbers are equal so we return either of the number 
    return n1;
}

// Euclidean algorithm : gcd(a,b) = gcd(b,a mod b)
// Steps :-
// 1) Given two numbers a and b (a > b), compute a mod b
// 2) Replace a with b and b with a mod b
// 3) Repeat until b becomes zero at which a is the gcd
// Ex - gcd(12,9) = gcd(9, 12%9) = gcd(9,3) = gcd(3, 9%3) = gcd(3,0) = 3
int Euclidean(int a, int b){
    while (a > 0 && b > 0){
        if (a > b) a = a % b;
        else b = b % a;
    }
    if (a == 0) return b;
    else return a;
}
// Time Complexity
// Subtraction-Based Euclidean Algorithm --> O(min(a, b))
// Euclidean algorithm --> O(log(min(a, b)))


int main() {
    int n1,n2;
    cout << "Enter the two numbers : ";
    cin >> n1 >> n2;
    int ans1 = getHCF(n1, n2);
    int ans2 = subEuclidean(n1, n2);
    int ans3 = Euclidean(n1, n2);
    cout << "Brute Approach : " << ans1 << endl;
    cout << "Subtraction-Based Euclidean Algorithm : " << ans2 << endl;
    cout << "Euclidean algorithm : " << ans3 << endl;

    return 0;
}