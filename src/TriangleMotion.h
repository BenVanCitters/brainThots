//
//  TriangleMotion.h
//  brainThots
//
//  Created by Ben Van Citters on 5/3/17.
//
//

#ifndef TriangleMotion_h
#define TriangleMotion_h

#include <stdio.h>
#include "ofMain.h"
#include "InputMask.h"

class TriangleMotion
{
    double localTime;
    
    // inputs
    double size;
    double zRotSpeed;
    double extrusionOffset;
    double extrusionAmt;
    int count;
    
    //
    
    double zRotation;
    double extrusionRotation;
public:
    void update(float dt, TriangleMask& mask);
    void draw();
};
#endif /* TriangleMotion_h */
