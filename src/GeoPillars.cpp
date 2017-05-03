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
    
    currentSz =  75;
    
    ofColor newc = ofColor::aliceBlue;// getColorForIndex(currentNum);
    currentColor = currentColor.lerp(newc, .1);
    currentSpread= ofVec2f(mask->pillarSpreadX.get(),mask->pillarSpreadY.get());
    
    circleRadMultiplier = (1-mask->pillarSpreadX.get());
    
    
    boxScale = mask->pillarScale.get();
    rotationAmt = mask->pillarRotationDiff.get();
}

void GeoPillars::draw(float sz)
{
    float add = 800 * sz;
    ofFill();
    ofSetColor(ofColor::white);
    
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
            ofTranslate(currentSpread.x*spacing.x*(i+.5),currentSpread.y*spacing.y*(j+.5));
            ofTranslate(mid);
            
            ofRotateY(currentSpread.y*rotationAmt*360*(j*1.f/steps)+ ofGetElapsedTimef()/3 * 360/TWO_PI);
            ofScale(boxScale, boxScale);
            ofDrawBox(currentSz+add);
            ofPopMatrix();
        }
    }
    
}

