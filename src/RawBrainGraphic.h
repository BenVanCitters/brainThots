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
    void update();
    void draw();
    void addSample(float newSample);
    
private:
    vector <float> brainBuffer;
    int currentIndex;
};
#endif /* RawBrainGraphic_h */
