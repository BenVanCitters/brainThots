//
//  SliderTrackingLerpedFloat.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/22/16.
//
//

#include "SliderTrackingLerpedFloat.h"
#include "ofMain.h"

//cur - current value
//targ - target value
//easing how quickly the value goes towards the target from the current value - used as the param in 'lerp'
SliderTrackingLerpedFloat::SliderTrackingLerpedFloat(float cur, float targ, float eas)
:LerpedFloat(cur,targ,eas)
{
    lastTrackedVal = cur;
}
//epsilon represents the largest allowable change(delta) that is allowed between target updates
SliderTrackingLerpedFloat::SliderTrackingLerpedFloat(float eas,float epsilon)
:LerpedFloat(0,0,eas)
{
    lastTrackedVal = 0;
    midiEpsilon = epsilon;
}

void SliderTrackingLerpedFloat::update(float dt)
{
    currentValue = ofLerp(currentValue, targetValue, easing);
}

//we assume that the incoming value is on the scale of 0-1
void SliderTrackingLerpedFloat::setTarget(float targ)
{
    //largest allowable delta before diff is ignored
    
    //if we sweep over our target then we should update
    bool crossedVal = (0 > (targetValue-targ) * (targetValue-lastTrackedVal));
    if(abs(targ-targetValue) < midiEpsilon || crossedVal)
    {
        targetValue = targ;
    }
    lastTrackedVal = targ;
}