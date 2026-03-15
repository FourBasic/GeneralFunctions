#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H
#include <Arduino.h>
	// used to build an array of ascending 'in' values and their corresponding 'out' values
	struct TableDataPoint {
   		float in,out;
	};
	bool withinRange(int a, int b, int tol);
	int limit(int mn, int val, int mx);
	float limitFloat(float mn, float val, float mx);
	float scaleFloat(float in, float minIn, float maxIn, float minOut, float maxOut);
	float scaleFloatByTable(float _in, struct TableDataPoint table[], uint16_t len);
#endif