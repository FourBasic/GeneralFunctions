#include "GeneralFunctions.h"
#include <Arduino.h>

struct table {

};

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

// Limits a floating point value within a range 
float limitFloat(float mn, float val, float mx) {
    if (val < mn) {
        return mn;
    } else if (val > mx) { 
        return mx;
    } else {
        return val;
    }
}

// 
float scaleFloat(float in, float minIn, float maxIn, float minOut, float maxOut) {
    float maxDiff = maxIn - minIn;
    if (maxDiff != 0) {
        float m = (maxOut - minOut) / maxDiff;
        float offs = minOut - (minIn * m);
        return (in * m) + offs;
    } else {
        return 0;
    }
}

// Use a table non linear data points to scale input value
// Eventually, one day, at some point in the future, add weighted smoothing.
float scaleFloatByTable(float _in, struct TableDataPoint table[], uint16_t len) {
    // Compare _in to each ascending value in the array.
    // Find the first element _in is less than, then use element[i] and element[i-1] to interpolate
    for (uint16_t i=0; i<len; i++) {
        if (_in == table[i].in) {
            // _in is equal. No scaling needed. Just return the table value.
            return table[i].out;
        } else if (_in < table[i].in) {
            // elem[i-1] --> _in --> elem[i] --> elem[i+1]
            bool elemExistsN1 = i > 0;
            bool elemExistsP1 = (i + 1) < len;
            if (elemExistsN1) {
                // scale between elemN1 and elem
                return scaleFloat(_in, table[i-1].in, table[i].in, table[i-1].out, table[i].out);

            } else if (elemExistsP1) {
                // scale between elem and elemP1
                return scaleFloat(_in, table[i].in, table[i+1].in, table[i].out, table[i+1].out);

            } else {
                // scale between assumed 0 point and elem
                return scaleFloat(_in, 0, table[i].in, 0, table[i].out);
            }            
        }
    }
    // _in is not smaller than anything in the table.
    return scaleFloat(_in, 0, table[len-1].in, 0, table[len-1].out);;
}