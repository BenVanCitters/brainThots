//
//  ColorFollower.h
//  brainThots
//
//  Created by Ben Van Citters on 8/23/16.
//
//

#ifndef ColorFollower_h
#define ColorFollower_h

#include "ofMain.h"
#include <stdio.h>

class ColorFollower
{
    public:
    ColorFollower();
    void update();
    void draw(float sz);
    
    void setCurrentIndex(int index);
    ofVec3f getCurrentPosition(){return currentPos;};
    
    ofColor currentColor;
    
    float lerpSpeed = .2;
private:
    ofVec3f getPositionForIndex(int index);
    ofColor getColorForIndex(int index);
    
    float currentSz = 10;
    float maxSize = 35;
    int currentNum; //current seeked index
    float maxDist; // max distance points could be apart from one another
    int maxIndex = 8;
    
    ofVec3f lastPos;     
    ofVec3f currentPos;
};
#endif /* ColorFollower_h */
