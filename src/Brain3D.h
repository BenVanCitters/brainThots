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
#include "RawBrainGraphic.h"

class Brain3D
{

public:
    void draw();
    void update();
    void addSamples(float* samples);
        Brain3D();
private:
    ofxAssimpModelLoader model;
    
    RawBrainGraphic rawBrainGraphic;
};


#endif /* Brain3D_h */
