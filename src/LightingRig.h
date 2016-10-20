//
//  LightingRig.hpp
//  brainThots
//
//  Created by Ben Van Citters on 10/19/16.
//
//

#ifndef LightingRig_h
#define LightingRig_h

#include <stdio.h>
#include "ofMain.h"
#import "InputMask.h"

class LightingRig
{
public:
    LightingRig(ofVec2f wxh);
    void enable();
    void diable();
    void update(float dt, LightingMask* inputMask);
    void setWindowSize(ofVec2f wxh) {windowSize=wxh;}
    
    ofLight pointLight;
    
    
private:
    ofVec2f windowSize;
};
#endif /* LightingRig_h */
