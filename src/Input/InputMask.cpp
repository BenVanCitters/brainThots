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
shaderVar2(.1,20*MIDI_EPSILON),
shaderVar3(.1,20*MIDI_EPSILON),
shaderVar4(.1,20*MIDI_EPSILON)
{ }

void ShaderInputMask::update(float dt)
{
    if(im != NULL)
    {
        blurAmount.setTarget( 25 * im->getMIDIFader1() );
        shaderVar1.setTarget( im->getMIDIFader2() );
        shaderVar2.setTarget( 20*im->getMIDIFader3() );
        shaderVar3.setTarget( im->getMIDIFader4() );
        shaderVar4.setTarget( 20*im->getMIDIFader5() );
    }
    blurAmount.update(dt);
    shaderVar1.update(dt);
    shaderVar2.update(dt);
    shaderVar3.update(dt);
    shaderVar4.update(dt);
}

RayMarcherInputMask::RayMarcherInputMask(InputManager* input)
:InputMask(input),
blurAmount(.1,25*MIDI_EPSILON),
shaderVar1(.1,MIDI_EPSILON),
shaderVar2(.1,20*MIDI_EPSILON),
shaderVar3(.1,20*MIDI_EPSILON),
timeMult(.1,20*MIDI_EPSILON),
renderDepth(.4,150)
{ }

void RayMarcherInputMask::update(float dt)
{
    isActive = (im != NULL);
    if(isActive)
    {
        shaderVar1.setTarget( im->getMIDIFader1() );
        shaderVar2.setTarget( im->getMIDIFader2() );
        shaderVar3.setTarget( im->getMIDIFader3() );
        timeMult.setTarget( im->getMIDIFader4() );
        renderDepth.setTarget( 20+100*(1-im->getMIDIFader5()));
    }
    shaderVar1.update(dt);
    shaderVar2.update(dt);
    shaderVar3.update(dt);
    timeMult.update(dt);
    renderDepth.update(dt);
}
/*
 class RayMarcherInputMask : public InputMask
 {
 public:
 ShaderInputMask(InputManager* input);
 SliderTrackingLerpedFloat blurAmount;
 SliderTrackingLerpedFloat shaderVar1;
 SliderTrackingLerpedFloat shaderVar2;
 SliderTrackingLerpedFloat shaderVar3;
 SliderTrackingLerpedFloat shaderVar4;
 SliderTrackingLerpedFloat renderDepth;
 
 void update(float dt);
 };
 */

Pillar3DInputMask::Pillar3DInputMask(InputManager* input)
:InputMask(input),
pillarSpeed(.1,MIDI_EPSILON),
pillarSpreadX(.1,5*MIDI_EPSILON),
pillarSpreadY(.1,5*MIDI_EPSILON),
pillarScale(.1,5*MIDI_EPSILON),
pillarRotationDiff(.1,5*MIDI_EPSILON)
{ }

void Pillar3DInputMask::update(float dt)
{
    if(im != NULL)
    {
        pillarSpreadX.setTarget( 1 * im->getMIDIFader1() );
        pillarSpreadY.setTarget( 1 * im->getMIDIFader2() );
        pillarScale.setTarget( 1 * im->getMIDIFader3() );
        pillarRotationDiff.setTarget( 1 * im->getMIDIFader4() );
        pillarSpeed.setTarget( 3 * im->getMIDIFader5() );
    }
    pillarSpreadX.update(dt);
    pillarSpreadY.update(dt);
    pillarScale.update(dt);
    pillarRotationDiff.update(dt);
    pillarSpeed.update(dt);
}


FollowerMask::FollowerMask(InputManager* input)
:InputMask(input),
speed(.03,MIDI_EPSILON),
size(.02,MIDI_EPSILON),
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


ChromaMask::ChromaMask(InputManager* input)
:InputMask(input),
speed(.3,MIDI_EPSILON*10),
offset(.2,MIDI_EPSILON*10)
{ }

void ChromaMask::update(float dt)
{
    if(im != NULL)
    {
        speed.setTarget( 10* im->getMIDIFader1() );
        float ofTarg = TWO_PI*im->getMIDIFader2();
        offset.setTarget( TWO_PI*im->getMIDIFader2() );
    }
    speed.update(dt);
    offset.update(dt);
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
        speed.setTarget( 5* im->getMIDIFader1() );
        ambientLight.setTarget( 255.f * im->getMIDIFader2() );
    }
    speed.update(dt);
    ambientLight.update(dt);
}

WaveFormMask::WaveFormMask(InputManager* input)
:InputMask(input),
amplitude(.07,1500*MIDI_EPSILON),
lineWeight(.1,20.f*MIDI_EPSILON),
shapeLerp(.1,MIDI_EPSILON)
{ }

void WaveFormMask::update(float dt)
{
    if(im != NULL)
    {
        amplitude.setTarget( 1500* im->getMIDIFader1() );
        lineWeight.setTarget( 20.f * im->getMIDIFader2() );
        shapeLerp.setTarget( im->getMIDIFader3() );
    }
    amplitude.update(dt);
    lineWeight.update(dt);
    shapeLerp.update(dt);
}

TriangleMask::TriangleMask(InputManager* input)
:InputMask(input),
size(.07,1500*MIDI_EPSILON),
zRotSpeed(.07,1500*MIDI_EPSILON),
extrusionOffset(.1,1500*MIDI_EPSILON),
extrusionAmt(.1,1500*MIDI_EPSILON),
count(.1,1500*MIDI_EPSILON)
{ }

void TriangleMask::update(float dt)
{
    if(im != NULL)
    {
        size.setTarget( 1* im->getMIDIFader1() );
        zRotSpeed.setTarget( 90* im->getMIDIFader2() );
        extrusionOffset.setTarget( 30 * im->getMIDIFader3() );
        extrusionAmt.setTarget( 20.f * im->getMIDIFader4() );
        count.setTarget(5+ 50 *im->getMIDIFader5() );
    }
    size.update(dt);
    zRotSpeed.update(dt);
    extrusionOffset.update(dt);
    extrusionAmt.update(dt);
    count.update(dt);
}

/*
 SliderTrackingLerpedFloat ;
 SliderTrackingLerpedFloat ;
 SliderTrackingLerpedFloat ;
 SliderTrackingLerpedFloat count;*/