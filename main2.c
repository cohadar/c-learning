//
//  main2.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/28/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "main2.h"

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>


union Njak {
    int32_t i;
    float f;
} njak, njak2;

union Zrak {
    int64_t i;
    double d;
} zrak, zrak2;

float nextFloat(float f) {
    union Njak njak;
    njak.f = f;
    njak.i++;
    return njak.f;
}

float sub2( float a, float  b ) {
    return a - b;
}

float calct( float segmentEnd, float segmentLength, float time ) {
    float segmentStart = segmentEnd - segmentLength;
    float t = ( time - segmentStart ) / segmentLength;
    return t;
}

float calct2( float segmentStart, float segmentEnd, float segmentLength, float time ) {
    float t = ( time - segmentStart ) / segmentLength;
    return t;
}

int main2() {
    char buff[8192];
    njak.f = FLT_MIN;
    printf("%08X", njak.i);
    while ( njak.f < 2.0 ) {
        float temp = 0.0;
        sprintf(buff, "%1.8e", njak.f);
        sscanf(buff, "%f", &temp);
        if ( njak.f != temp ) {
            printf( "\n%1.8e %1.8e", njak.f, temp );
        }
        njak.i++;
    }
    printf("\n Done.");
    return 0;
}
