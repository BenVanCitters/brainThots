//
//  LightingRig.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/19/16.
//
//

#include "LightingRig.h"

LightingRig::LightingRig(ofVec2f wxh)
:windowSize(wxh)
{
    pointLight.setPosition(windowSize.x/2.f, windowSize.y/2.f, 500);
    pointLight.setDiffuseColor(ofColor(128.f, 128.f, 128.f));
    pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    pointLight.setDirectional();
    pointLight.setSpotlight(1000,.05);
}

void LightingRig::enable()
{
    ofEnableLighting();
    pointLight.enable();

}

void LightingRig::diable()
{
    pointLight.disable();
    ofDisableLighting();
}


void LightingRig::update(float dt, LightingMask* inputMask)
{
    float t = ofGetElapsedTimef()*3;
    ofVec2f halfWin = windowSize/2;
    pointLight.setPosition(halfWin.x *(1+cos(t)),halfWin.y *(1+sin(t)), 500);
}