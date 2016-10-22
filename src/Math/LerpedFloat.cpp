//
//  LerpedFloat.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#include "LerpedFloat.h"
#include "ofMain.h"

LerpedFloat::LerpedFloat(float cur, float targ, float eas)
{
    currentValue = cur;
    targetValue = targ;
    easing = eas;
}

void LerpedFloat::update(float dt)
{
    currentValue = ofLerp(currentValue, targetValue, easing);
}

void LerpedFloat::setTarget(float targ)
{
    targetValue = targ;
}