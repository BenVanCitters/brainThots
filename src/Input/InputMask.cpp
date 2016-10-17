//
//  InputMask.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#include "InputMask.h"

InputMask::InputMask(InputManager* input)
:blurAmount(0,0,.01)
{
    im = input;
    
}

void InputMask::update(float dt)
{
    if(im != NULL)
    {
        blurAmount.setTarget( 50 * im->getMIDIFader3() );
    }
    blurAmount.update(dt);
}