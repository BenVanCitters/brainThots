//
//  SliderTrackingLerpedFloat.hpp
//  brainThots
//
//  Created by Ben Van Citters on 10/22/16.
//
//

#ifndef SliderTrackingLerpedFloat_h
#define SliderTrackingLerpedFloat_h

#include <stdio.h>
#include "LerpedFloat.h"

class SliderTrackingLerpedFloat : public LerpedFloat
{
public:
    SliderTrackingLerpedFloat(float cur, float targ, float eas);
    SliderTrackingLerpedFloat(float eas,float epsilon);
    void update(float dt);
    void setTarget(float targ);
    float midiEpsilon = 5.f/128.f;
private:
    float lastTrackedVal;
};
#endif /* SliderTrackingLerpedFloat_h */
