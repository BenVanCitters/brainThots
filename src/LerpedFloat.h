//
//  LerpedFloat.h
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#ifndef LerpedFloat_h
#define LerpedFloat_h

#include <stdio.h>

class LerpedFloat
{
public:
    LerpedFloat(float cur, float targ, float eas);
    inline float get(){return currentValue;}
    virtual void setTarget(float targ);
    virtual void update(float dt);
    
protected:
    float currentValue;
    float targetValue;
    float easing;
};
#endif /* LerpedFloat_h */
