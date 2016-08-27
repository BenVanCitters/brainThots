//
//  ColorFollower.cpp
//  brainThots
//
//  Created by Ben Van Citters on 8/23/16.
//
//

#include "ColorFollower.h"

ColorFollower::ColorFollower()
{
    
    maxIndex = 8;
    maxDist = sqrt(ofGetWindowWidth()*ofGetWindowWidth()+ofGetWindowHeight()*ofGetWindowHeight());
}
void ColorFollower::update()
{
    //save the old pos
    lastPos = currentPos;
    
    ofVec3f tmp = getPositionForIndex(currentNum);
    float d = ofDist(currentPos[0],currentPos[1],tmp[0],tmp[1]);
    
    d/=maxDist; //normalize
    d = 1-d;
    float newSz = d*maxSize;
    
    currentSz =  ofLerp(currentSz,newSz,.5);
    float lerpAmt = .2;
    currentPos = currentPos.getInterpolated(tmp,lerpAmt);

    
    ofColor newc = getColorForIndex(currentNum);
    currentColor = currentColor.lerp(newc, .1);
}

void ColorFollower::draw()
{

    ofFill();
    ofSetColor(currentColor);
//    ofDrawEllipse(currentPos.x, currentPos.y, currentSz, currentSz);
    ofDrawSphere(currentPos.x, currentPos.y, currentSz);
//    ofDrawLine(lastPos,currentPos);
}

void ColorFollower::setCurrentIndex(int index)
{
    currentNum = index;
}

ofVec3f ColorFollower::getPositionForIndex(int index)
{
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    float rad = ofGetElapsedTimef()/3 + (index*1.f/8)*TWO_PI;
    return ofVec3f((width/2.f) + (height/2.f-maxSize/2) *cosf(rad),
                   (height/2.f) + (height/2.f-maxSize/2) *sinf(rad),
                    0 );
}

ofColor ColorFollower::getColorForIndex(int index)
{
    ofColor color;
    float f = color.limit();
    color.setHsb(index*f/maxIndex,f,f,f);
    return color;
//    colorMode(HSB, 256);
//    return color(index*256/maxIndex,256,256);
}
