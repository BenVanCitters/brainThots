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
    void draw();
    
    void setCurrentIndex(int index);
    private:
    ofVec3f getPositionForIndex(int index);
    ofColor getColorForIndex(int index);
    
    float currentSz = 10;
    float maxSize = 20;
    int currentNum; //current seeked index
    float maxDist; // max distance points could be apart from one another
    int maxIndex = 8;
    
    ofVec3f lastPos;//={0,0};
    ofVec3f currentPos;//={0,0};
    ofColor currentColor;// ={0,0,0};
};
#endif /* ColorFollower_h */
