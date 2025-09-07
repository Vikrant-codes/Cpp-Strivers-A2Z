#include <bits/stdc++.h>
using namespace std;

bool isPerfectSquare(int x, int &st) {
    for (int i = st; i <= x/i; i++) {
        if (i * i == x) {
            return true;
            st++;
        }
    }
    return false;
}

int bulbSwitch(int n) {
    // int cnt = 0;
    // int st = 1;
    // for(int i = 1; i <= n; i++) {
    //     if (isPerfectSquare(i, st)) {
    //         cnt++;
    //         cout << i << " ";
    //     }
    // }
    // return cnt;

    return sqrt(n);

    // we need the count of all perfect squares upto n 
    // now imagine the number is n then say if k ^ 2 is the largest perfect square upto n then k * k <= n --> k <= sqrt(n) i.e. floor(sqrt(n))
    // since k ^ 2 is the largest integer perfect square then all the numbers 1,2,3,....,k all these numbers sqaure lie in the range of n. 
    // so the count of all the perfect sqaures upto n is the count of integers 1,2,3,..,k such that k <= sqrt(n) and this count is k itself
    // so we return sqrt(n) itself as the total count of perfect squares upto n
}

int main() {
    int bulbs = 1000;
    cout << bulbSwitch(bulbs);
}