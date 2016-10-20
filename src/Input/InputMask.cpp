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
:InputMask(input), brain3DScale(0,0,.1),brain3DRotationSpeed(0,0,.1)
{ }

void Brain3DInputMask::update(float dt)
{
    if(im != NULL)
    {
        brain3DScale.setTarget( 5 * im->getMIDIFader1() );
        brain3DRotationSpeed.setTarget( 5 * im->getMIDIFader2() );
    }
    brain3DScale.update(dt);
    brain3DRotationSpeed.update(dt);
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


FollowerMask::FollowerMask(InputManager* input)
:InputMask(input), speed(0,0,.01), size(0,0,.1), particleSize(0,0,.1)
{ }

void FollowerMask::update(float dt)
{
    if(im != NULL)
    {
        speed.setTarget( 1* im->getMIDIFader1() );
        size.setTarget( 2000.f * im->getMIDIFader2() );
        particleSize.setTarget(200.f * im->getMIDIFader3());
    }
    speed.update(dt);
    size.update(dt);
    particleSize.update(dt);
}


LightingMask::LightingMask(InputManager* input)
:InputMask(input), speed(0,0,.01), ambientLight(0,0,.1)
{ }

void LightingMask::update(float dt)
{
    if(im != NULL)
    {
        speed.setTarget( 1* im->getMIDIFader1() );
        ambientLight.setTarget( 2000.f * im->getMIDIFader2() );
    }
    speed.update(dt);
    ambientLight.update(dt);
}
