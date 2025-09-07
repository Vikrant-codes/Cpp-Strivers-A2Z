#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

int main() {
    /*
        maps take logarithmic time for both storing and fetching. This logarithmic complexity is due to storing in sorted order.
        But unordered_map stores without order so it can perform the operations in O(1), hence unordered_map is preferred over map for hashing.

        Complexity Ananlysis -->
        map : Best, Average & Worst Case --> O(log n)
        unordered_map : Best & Average Case --> O(1) , Worst Case --> O(n).. Worst case happens due to internal collisions

        Even though the worst case complexity of unordered_map is higher than map but we still prefer unordered_map since worst cases are very rare
        Map is used for hashing only when we get TLE using unordered_map (worst case occuring) 
    */ 
    // In maps we can even take pairs or any data structure as keys but in unordered_map we can't take complex data structures as keys ...
    // only int, double, char, long etc can be used as keys for unordered_map


    int n;
    cout << "Enter Array Size : ";
    cin >> n;
    int arr[n];
    unordered_map<int, int> mpp;
    cout << "Enter the elements : ";

    // equivalent to : for(int i=0; i<n; i++) cin >> arr[i]; for(int i=0; i<n; i++) mpp[arr[i]]++;
    // Instead of using 2 loops (one for entering array elements and other for entering key-value pair in map), the functioning is done in 1 loop only
    for(int i=0; i<n; i++){
        cin >> arr[i];
        mpp[arr[i]]++;
    }

    int q;
    do{
        int x;
        cout << "Enter the element : ";
        cin >> x;
        cout << "Frequency of " << x << " is : " << mpp[x] << endl;
        cout << "Press 1 to continue .... Any other key to exit : ";
        cin >> q;
    } while (q == 1);

    return 0;
}