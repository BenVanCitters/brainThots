//
//  InputMask.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#include "InputMask.h"

#define MIDI_RANGE 128.f
#define MIDI_EPSILON 40.f/MIDI_RANGE
InputMask::InputMask(InputManager* input)
{
    im = input;
}

void InputMask::update(float dt){ }

ShaderInputMask::ShaderInputMask(InputManager* input)
:InputMask(input),
blurAmount(.1,25*MIDI_EPSILON),
shaderVar1(.1,MIDI_EPSILON),
shaderVar2(.1,20*MIDI_EPSILON)
{ }

void ShaderInputMask::update(float dt)
{
    if(im != NULL)
    {
        blurAmount.setTarget( 25 * im->getMIDIFader1() );
        shaderVar1.setTarget( im->getMIDIFader2() );
        shaderVar2.setTarget( 20*im->getMIDIFader3() );
    }
    blurAmount.update(dt);
    shaderVar1.update(dt);
    shaderVar2.update(dt);
}

Brain3DInputMask::Brain3DInputMask(InputManager* input)
:InputMask(input),
brain3DScale(.1,5*MIDI_EPSILON),
brain3DRotationSpeed(.1,100*MIDI_EPSILON),
brain3DRotationAxis(.1,MIDI_EPSILON)
{ }

void Brain3DInputMask::update(float dt)
{
    if(im != NULL)
    {
        brain3DScale.setTarget( 5 * im->getMIDIFader1() );
        float rotSpd = im->getMIDIFader2()*2-1;
        brain3DRotationSpeed.setTarget( 100 * rotSpd );
        brain3DRotationAxis.setTarget(im->getMIDIFader3() );
    }
    brain3DScale.update(dt);
    brain3DRotationSpeed.update(dt);
    brain3DRotationAxis.update(dt);
}

RBGInputMask::RBGInputMask(InputManager* input)
:InputMask(input),
amplitude(.04,MIDI_EPSILON),
lineLength(.1,3000*MIDI_EPSILON),
lineThickness(.1,20*MIDI_EPSILON),
shapeLerp(.07,MIDI_EPSILON)
{ }

void RBGInputMask::update(float dt)
{
    if(im != NULL)
    {
        lineLength.setTarget( 3000.f * im->getMIDIFader1() );
        amplitude.setTarget( 1* im->getMIDIFader2() );
        lineThickness.setTarget(20 * im->getMIDIFader3());
        shapeLerp.setTarget(1 * im->getMIDIFader4());
    }
    amplitude.update(dt);
    lineLength.update(dt);
    lineThickness.update(dt);
    shapeLerp.update(dt);
}


FollowerMask::FollowerMask(InputManager* input)
:InputMask(input),
speed(.03,MIDI_EPSILON),
size(.05,MIDI_EPSILON),
particleSize(.1,20*MIDI_EPSILON)
{ }

void FollowerMask::update(float dt)
{
    if(im != NULL)
    {
        speed.setTarget( 1* im->getMIDIFader1() );
        size.setTarget( im->getMIDIFader2() );
        particleSize.setTarget(20.f * im->getMIDIFader3());
    }
    speed.update(dt);
    size.update(dt);
    particleSize.update(dt);
}


LightingMask::LightingMask(InputManager* input)
:InputMask(input),
speed(.07,50*MIDI_EPSILON),
ambientLight(.1,255*MIDI_EPSILON)
{ }

void LightingMask::update(float dt)
{
    if(im != NULL)
    {
        speed.setTarget( 50* im->getMIDIFader1() );
        ambientLight.setTarget( 255.f * im->getMIDIFader2() );
    }
    speed.update(dt);
    ambientLight.update(dt);
}
