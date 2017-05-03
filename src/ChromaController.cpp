//
//  ChromaController.cpp
//  brainThots
//
//  Created by Ben Van Citters on 5/2/17.
//
//

#include "ChromaController.h"

void ChromaController::update(float dt, ChromaMask* inputMask)
{
    float curSpeed =inputMask->speed.get();
    currentTime += curSpeed*dt;
    float off =inputMask->offset.get();
    currentColor = ofColor(255*(sin( 7+off+currentTime/1.5f)+1)/2.f,
                           255*(sin(13+off+currentTime/1.3f)+1)/2.f,
                           255*(sin(17+off+currentTime/1.2f)+1)/2.f);
    
}