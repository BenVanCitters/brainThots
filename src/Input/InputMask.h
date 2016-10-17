//
//  InputMask.hpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#ifndef InputMask_h
#define InputMask_h

#include <stdio.h>
#include "LerpedFloat.h"
#include "InputManager.h"
//class to handle tasks associated with grabbing and updating input
class InputMask
{
public:
    InputMask(InputManager* input);
    void update(float dt);
    
    LerpedFloat brain3DScale;
    LerpedFloat blurAmount;
    
private:
    InputManager* im;
};
#endif /* InputMask_h */
