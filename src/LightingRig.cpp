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
    
    pointLight.setDirectional();
    pointLight.setSpotlight(1000,.05);
}

void LightingRig::enable()
{
    ofEnableLighting();
    pointLight.enable();
    ambientLight.enable();
}

void LightingRig::disable()
{
    pointLight.disable();
    ambientLight.disable();
    ofDisableLighting();
}


void LightingRig::update(float dt, LightingMask* inputMask)
{
    lightTime += dt* inputMask->speed.get();
    float t = lightTime;
    ofVec2f halfWin = windowSize/2;
    pointLight.setPosition(halfWin.x *(1+cos(t)),halfWin.y *(1+sin(t)), 500);
    float ambientColor = inputMask->ambientLight.get();
    cout << "ambient: " << ambientColor << endl;
//    ofSetGlobalAmbientColor(ofColor(ambientColor,ambientColor,ambientColor).operator*(fade));
//    ambientLight.setPointLight();
//    ambientLight.setDiffuseColor(ofColor::black);
//    ambientLight.setSpecularColor(ofColor::black);
    ambientLight.setAmbientColor(ofColor(ambientColor,ambientColor,ambientColor).operator*(fade));
    
    pointLight.setDiffuseColor(ofColor(128.f, 128.f, 128.f).operator*(fade));
    pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f).operator*(fade));
}