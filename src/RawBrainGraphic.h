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

class RawBrainGraphic
{
public:
    RawBrainGraphic(int count);
    void update();
    void draw();
    void addSample(int index, float newSample);
//    void addSample(float newSample);
    
private:
    vector <vector <float>> brainBuffers;
//    vector <float> brainBuffer;
//    int currentIndex;
    int maxFloatLen = 200;
};
#endif /* RawBrainGraphic_h */
