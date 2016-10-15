//
//  RawBrainGraphic.h
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#ifndef RawBrainGraphic_h
#define RawBrainGraphic_h

#define LINE_COUNT 16
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
    
    void setTransform(int index, aiMatrix4x4 t);
//    void addSample(float newSample);
    
private:
    void printVecs();
    vector <vector <float>> brainBuffers;
    ofMatrix4x4 mTransformations[LINE_COUNT];
    ofVboMesh mMesh[LINE_COUNT];
//    vector <float> brainBuffer;
//    int currentIndex;
    int maxFloatLen = 50;
};
#endif /* RawBrainGraphic_h */
