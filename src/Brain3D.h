//
//  Brain3D.h
//  brainThots
//
//  Created by Ben Van Citters on 9/25/16.
//
//

#ifndef Brain3D_h
#define Brain3D_h


#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "InputMask.h"

class Brain3D
{

public:
    Brain3D();
    
    void draw();
    void update(float dt, Brain3DInputMask* bim);
    
    void addSamples(float* samples);
    void setScale(float s);
    
    double currentRotation;
private:
    ofxAssimpModelLoader model;
    
};


#endif /* Brain3D_h */
