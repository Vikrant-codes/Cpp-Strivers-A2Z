/*
Leetcode - 2126. Destroying Asteroids : Medium

You are given an integer mass, which represents the original mass of a planet. 
You are further given an integer array asteroids, where asteroids[i] is the mass of the ith asteroid.
You can arrange for the planet to collide with the asteroids in any arbitrary order. 
If the mass of the planet is greater than or equal to the mass of the asteroid, 
the asteroid is destroyed and the planet gains the mass of the asteroid. Otherwise, the planet is destroyed.

Return true if all asteroids can be destroyed. Otherwise, return false.

Examples :-

Input: mass = 10, asteroids = [3,9,19,5,21] __ Output: true
Explanation: One way to order the asteroids is [9,19,5,3,21]:
- The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
- The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
- The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
- The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
- The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
All asteroids are destroyed.

Input: mass = 5, asteroids = [4,9,23,4] __ Output: false
Explanation: 
The planet cannot ever gain enough mass to destroy the asteroid with a mass of 23.
After the planet destroys the other asteroids, it will have a mass of 5 + 4 + 9 + 4 = 22.
This is less than 23, so a collision would not destroy the last asteroid.

Constraints :-
- 1 <= mass <= 10^5
- 1 <= asteroids.length <= 10^5
- 1 <= asteroids[i] <= 10^5
*/

#include<bits/stdc++.h>
using namespace std;

// Optimal Approach (Greedy) : Time Complexity : O(n * log n) __ Space Complexity : O(1)
bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
    sort(asteroids.begin(), asteroids.end());
        
    long long curr = mass;
        
    for (int x : asteroids) {
        if (curr < x) 
            return false;

        curr += x;
    }

    return true;
}

// Early Return condition (Constraint Analysis) 
/*
Constraints tell us that the max. weight of asteroids can be 10^5, so if the current weight curr has becomes >= 10^5,
then we know that all of the further asteroids can be tanked easily.
So, we can return true the moment curr becomes >= 10^5, no need to check any further.
Also, due to this early return, we don't need to declare curr as 'long long' since we return true when its value exceeds 10^5.
suppose curr value was 99999 (which is lesser than 10^5), then the next weight of asteroid could be at max 10^5.
Even at this weight, 99999 + 100000 = 199999. This would still be inside int range and true will be returned since
curr would exceed 10^5.
*/
bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
    sort(asteroids.begin(), asteroids.end());
        
    int curr = mass;
    for (int x : asteroids) {
        if (curr < x) return false;
        curr += x;
        if (curr >= 1e5) return true;       // early return condition
    }

    return true;
}

int main() {
    return 0;
}