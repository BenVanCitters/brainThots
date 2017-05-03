//
//  AudioVisual.hpp
//  brainThots
//
//  Created by Ben Van Citters on 10/20/16.
//
//

#ifndef AudioVisual_h
#define AudioVisual_h

#include <stdio.h>
#include "ofMain.h"
#include "InputMask.h"

class AudioVisual
{
public:
    AudioVisual(int sampleCount);
    ~AudioVisual();
    void update(float dt, WaveFormMask* inputMask);
    void draw();
    
    void setSamples(vector<float> vec);
    
    float amplitude;
    int sampleCount;
    float* samples;
    ofVec2f currentScreenSz;
    ofColor currentColor;
private:
    ofVboMesh mMesh;
};
#endif /* AudioVisual_h */
