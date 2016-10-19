//
//  InputMask.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#include "InputMask.h"

InputMask::InputMask(InputManager* input)
{
    im = input;
}

void InputMask::update(float dt){ }

ShaderInputMask::ShaderInputMask(InputManager* input)
:InputMask(input), blurAmount(0,0,.1),shaderVar1(0,0,.1)
{ }

void ShaderInputMask::update(float dt)
{
    if(im != NULL)
    {
        blurAmount.setTarget( 25 * im->getMIDIFader1() );
        shaderVar1.setTarget( im->getMIDIFader2() );
    }
    blurAmount.update(dt);
    shaderVar1.update(dt);
}

Brain3DInputMask::Brain3DInputMask(InputManager* input)
:InputMask(input), brain3DScale(0,0,.1)
{ }

void Brain3DInputMask::update(float dt)
{
    if(im != NULL)
    {
        brain3DScale.setTarget( 5 * im->getMIDIFader1() );
    }
    brain3DScale.update(dt);
}

RBGInputMask::RBGInputMask(InputManager* input)
:InputMask(input), amplitude(0,0,.01), lineLength(0,0,.1)
{ }

void RBGInputMask::update(float dt)
{
    if(im != NULL)
    {
        amplitude.setTarget( 1* im->getMIDIFader2() );
        lineLength.setTarget( 2000.f * im->getMIDIFader1() );
    }
    amplitude.update(dt);
    lineLength.update(dt);
}