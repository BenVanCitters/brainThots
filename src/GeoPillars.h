//
//  GeoPillars.h
//  brainThots
//
//  Created by Ben Van Citters on 8/23/16.
//
//

#ifndef GeoPillars_h
#define GeoPillars_h

#include <stdio.h>
#include "ofMain.h"
#include "InputMask.h"

class GeoPillars
{
    public:
    GeoPillars();
    void update(float dt, Pillar3DInputMask* mask);
    void draw(float sz);

    ofVec2f currentScreenSize;
     ofVec2f currentSpread;
    ofColor currentColor;
    
    ofVec3f currentPos;
    float fade;
    float lerpSpeed = .2;
private:

    
    float currentSz = 10;
    float maxSize = 35;
    int currentNum; //current seeked index
    float maxDist; // max distance points could be apart from one another
    int maxIndex = 8;
    
    float circleRadMultiplier;
    
    ofVec3f lastPos;
};
#endif /* ColorFollower_h */
