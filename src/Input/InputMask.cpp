//
//  InputMask.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#include "InputMask.h"

InputMask::InputMask(InputManager* input)
:blurAmount(0,0,.01), brain3DScale(0,0,.1)
{
    im = input;
    im->addMIDIPADListener(this);
}

void InputMask::update(float dt)
{
    if(im != NULL)
    {
        blurAmount.setTarget( 50 * im->getMIDIFader3() );
        brain3DScale.setTarget( 5 * im->getMIDIFader4() );
    }
    blurAmount.update(dt);
    brain3DScale.update(dt);
}

#pragma

void InputMask::PAD1NoteOn(ofxMidiMessage& msg)
{
    cout << " i fucn got called like a boss" << endl;
}
void InputMask::PAD2NoteOn(ofxMidiMessage& msg)
{
    
}
void InputMask::PAD3NoteOn(ofxMidiMessage& msg)
{
    
}
void InputMask::PAD4NoteOn(ofxMidiMessage& msg)
{
    
}
void InputMask::PAD5NoteOn(ofxMidiMessage& msg)
{
    
}
void InputMask::PAD6NoteOn(ofxMidiMessage& msg)
{
    
}