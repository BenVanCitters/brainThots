//
//  InputMarshaller.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/18/16.
//
//

#include "InputMarshaller.h"

InputMarshaller::InputMarshaller(InputManager* im)
:shaderMask(im),rbgLinesMask(im), brain3DMask(im)
{
    activeMask = &rbgLinesMask;
    im->addMIDIPADListener(this);
}

void InputMarshaller::update(float dt)
{
    if(activeMask!= NULL)
    {
        activeMask->update(dt);
    }
}

void InputMarshaller::PAD1NoteOn(ofxMidiMessage& msg)
{
    activeMask = &rbgLinesMask;
}
void InputMarshaller::PAD2NoteOn(ofxMidiMessage& msg)
{
    activeMask = &shaderMask;
}
void InputMarshaller::PAD3NoteOn(ofxMidiMessage& msg)
{
    activeMask = &brain3DMask;
}
void InputMarshaller::PAD4NoteOn(ofxMidiMessage& msg)
{
    
}
void InputMarshaller::PAD5NoteOn(ofxMidiMessage& msg)
{
    
}
void InputMarshaller::PAD6NoteOn(ofxMidiMessage& msg)
{
    
}