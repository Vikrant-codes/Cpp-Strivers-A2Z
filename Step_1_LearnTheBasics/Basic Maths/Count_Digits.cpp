#include<bits/stdc++.h>
#include<cmath>         // for log10 function
using namespace std;

// Time Complexity = O( log10 (n) ) 

int countDigits(int n){
    int cnt = 0;
    // while (n>0) {
    //     int d = n%10;
    //     cnt++;
    //     n = n/10;
    // }
    cnt = (int)(log10(n)+ 1);
    return cnt;
}

int main() {
    vector<int> digits;
    int n;
    cout << "Enter no : ";
    cin >> n;
    
    int ct = countDigits(n);
    cout << "Count of digits : " << ct << endl;

    return 0;
}