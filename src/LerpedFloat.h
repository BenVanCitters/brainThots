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
    void setTarget(float targ);
    void update(float dt);
    
private:
    float currentValue;
    float targetValue;
    float easing;
};
#endif /* LerpedFloat_h */
