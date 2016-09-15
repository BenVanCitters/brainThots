//
//  RawBrainGraphic.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#include "RawBrainGraphic.h"


void RawBrainGraphic::update()
{
    
}

void RawBrainGraphic::draw()
{
    
    for(int i = 0; i < brainBuffer.size(); i++)
    {
        
    }
}

void RawBrainGraphic::addSample(float newSample)
{
    brainBuffer[currentIndex] = newSample;
    currentIndex++;
}