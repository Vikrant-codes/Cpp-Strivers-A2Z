#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter Array Size : ";
    cin >> n;
    int arr[n];
    cout << "Enter " << n << " elements : ";
    for(int i=0; i<n; i++) cin >> arr[i];

    // Precompute : Make a hash array or frequency array
    // Hash array has as many indexes as the maximum element so to avoid collisions
    // Here we are considering that max element is 12 so we only taking 13 indices in hash array (0 till 12)
    int hash[13] = {0};
    // for each element of the array we increment the value at that index of hash array by 1 
    for(int i=0; i<n; i++) hash[arr[i]] += 1;

    int q;
    do{
        int x;
        cout << "Enter the number whose frequency to check : ";
        cin >> x;
        cout << "Frequency of x in array : " << hash[x] << endl;
        cout << "Enter 0 to exit --> ";
        cin >> q;
    } while(q != 0);

    // the max integer array size that can be defined inside of main is 10^6, bool array is 10 ^ 7 
    // trying to assign higher size array will give segmentation fault
    // global array sizes -- int array = 10 ^ 7 __ bool array = 10 ^ 8
    // so suppose we need to store numbers like 10^7 then it would be problematic to create hash array since it can't have that many indices

    return 0;
}