#include "GeneralFunctions.h"
#include <Arduino.h>

// Returns true of 'a' in range of 'b' +- tolerance
bool withinRange(int a, int b, int tol) {
 return abs(a-b) < tol;
}

// Limits a value within a range
int limit(int mn, int val, int mx) {
    if (val < mn) {
        return mn;
    } else if (val > mx) { 
        return mx;
    } else {
        return val;
    }
}



