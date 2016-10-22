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
#include "InputMask.h"

class RawBrainGraphic
{
public:
    RawBrainGraphic(int count);
    void update(float dt, RBGInputMask* inputMask);
    void draw(ofVec2f screenDims, float alpha);
    void addSample(int index, float newSample);
    void addSamples(float* newSample);
    
    void setTransform(int index, aiMatrix4x4 t);
    void setBrainAmplitude(float amplitude);
    void setBrainLineLength(float length);
    float brainLineThickness = 0;
private:
    void printVecs();
    vector <vector <float>> brainBuffers;
    ofMatrix4x4 mTransformations[LINE_COUNT];
    ofVboMesh mMesh[LINE_COUNT];
    int maxFloatLen = 120;
    
    float brainLen = 0;    //'scale' or total length of the line
    float brainAmp = 0;
    float shapeLerp = 0;
};
#endif /* RawBrainGraphic_h */
