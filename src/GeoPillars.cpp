//
//  GeoPillars.cpp
//  brainThots
//
//  Created by Ben Van Citters on 8/23/16.
//
//

#include "GeoPillars.h"

GeoPillars::GeoPillars()
{
    
    maxIndex = 8;
    maxDist = sqrt(ofGetWindowWidth()*ofGetWindowWidth()+ofGetWindowHeight()*ofGetWindowHeight());
}
void GeoPillars::update(float dt, Pillar3DInputMask* mask)
{
    //save the old pos
    lastPos = currentPos;
    
    ofVec3f tmp = ofVec3f(0,0,0);//getPositionForIndex(currentNum);
    float d = ofDist(currentPos[0],currentPos[1],tmp[0],tmp[1]);
    
    d/=maxDist; //normalize
    d = 1-d;
    float newSz = d*maxSize;
    
    currentSz =  ofLerp(currentSz,newSz,.5);
    currentPos = currentPos.getInterpolated(tmp,lerpSpeed);

    
    ofColor newc = ofColor::aliceBlue;// getColorForIndex(currentNum);
    currentColor = currentColor.lerp(newc, .1);
    currentSpread= ofVec2f(mask->pillarSpreadX.get(),mask->pillarSpreadY.get());
    
    circleRadMultiplier = (1-mask->pillarSpreadX.get());
}

void GeoPillars::draw(float sz)
{
    float add = 400 * sz;
    ofFill();
    ofSetColor(currentColor);
    

    
    ofVec2f mid = currentScreenSize/2;
    
    
    int steps = 7;
    
    ofVec2f spacing((currentScreenSize.x-100)/(steps*2),
                    (currentScreenSize.y-200)/(steps*2));
    for(int i = -steps; i < steps; i++)
    {
        for(int j = -steps; j < steps; j++)
        {
            float pct = (i+1)*1.f/steps;
            ofPushMatrix();
            ofTranslate(spacing.x*i,spacing.y*j);
            ofTranslate(mid);
            
    //        ofDrawSphere(0,0, fade*(currentSz+add));
            ofRotateY(currentSpread.y*90*(j*1.f/steps)+ ofGetElapsedTimef()/3 * 360/TWO_PI);
    //        ofDrawBox(0, 0, 0, 50, 50, 50);
            
            ofDrawBox(currentSz+add);
            ofPopMatrix();
        }
    }
    
}

