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
void ColorFollower::update(float dt, FollowerMask* mask)
{
    //save the old pos
    lastPos = currentPos;
    
    ofVec3f tmp = getPositionForIndex(currentNum);
    float d = ofDist(currentPos[0],currentPos[1],tmp[0],tmp[1]);
    
    d/=maxDist; //normalize
    d = 1-d;
    float newSz = d*maxSize;
    
    currentSz =  ofLerp(currentSz,newSz,.5);
    currentPos = currentPos.getInterpolated(tmp,lerpSpeed);

    
    ofColor newc = getColorForIndex(currentNum);
    currentColor = currentColor.lerp(newc, .1);
    
    circleRadMultiplier = (1-mask->size.get());
}

void ColorFollower::draw(float sz)
{
    float add = 400 * sz;
    ofFill();
//    currentColor *= fade;
    ofSetColor(currentColor , 255*fade);
    
//    ofRotateZ(ofGetElapsedTimef()/3 * 360/TWO_PI);
    ofVec3f start = lastPos;
    ofVec3f end = currentPos;
    ofVec3f dir = end-start;
    
    int steps = 7;
    for(int i = 0; i < steps; i++)
    {
        float pct = (i+1)*1.f/steps;
        ofPushMatrix();
        ofTranslate(start+dir*pct);
        ofDrawSphere(0,0, fade*(currentSz+add));
        ofPopMatrix();
    }
    
}

void ColorFollower::setCurrentIndex(int index)
{
    currentNum = index;
}

ofVec3f ColorFollower::getPositionForIndex(int index)
{
    float rad = (index*1.f/8)*TWO_PI;
    ofVec3f halfScr((currentScreenSize.x/2.f),(currentScreenSize.y/2.f),0);
    ofVec3f unitCirc(cosf(rad),sinf(rad));
    float scale = circleRadMultiplier * (currentScreenSize.y/2.f-maxSize/2);
    
    return halfScr + unitCirc * scale;
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
