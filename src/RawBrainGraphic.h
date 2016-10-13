//
//  RawBrainGraphic.h
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#ifndef RawBrainGraphic_h
#define RawBrainGraphic_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class RawBrainGraphic
{
public:
    RawBrainGraphic(int count);
    void update();
    void draw();
    void addSample(int index, float newSample);
    void addSamples(float* newSample);
    
    void setTransform(int index, aiMatrix4x4 transformation);
//    void addSample(float newSample);
    
private:
    vector <vector <float>> brainBuffers;
    aiMatrix4x4 mTransformations[16];
//    vector <float> brainBuffer;
//    int currentIndex;
    int maxFloatLen = 10;
};
#endif /* RawBrainGraphic_h */
