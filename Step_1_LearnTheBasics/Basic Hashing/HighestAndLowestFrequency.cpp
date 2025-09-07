#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cout << "Enter Array Size : ";
    cin >> n;
    int arr[n];
    unordered_map<int, int> mpp;
    cout << "Enter the elements : ";
    for(int i=0; i<n; i++) {
        cin >> arr[i];
        mpp[arr[i]]++;
    }

    int mxFreq = 0, mnFreq = n;
    int mx = 0, mn = 0;
    for(auto x : mpp){
        if(x.second > mxFreq){
            mxFreq = x.second;
            mx = x.first;
        }
        if(x.second < mnFreq){
            mnFreq = x.second;
            mn = x.first;
        } 
    }

    cout  << "Highest Frequency : " << mx << " with frequency " << mxFreq << endl;
    cout  << "Lowest Frequency : " << mn << " with frequency " << mnFreq << endl;
}