//
//  InputMarshaller.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/18/16.
//
//

#include "InputMarshaller.h"

InputMarshaller::InputMarshaller(InputManager* im)
:shaderMask(im), pillar3DMask(im), followerMask(im),lightingMask(im),
audioMask(im), chromaMask(im), rayMarcherMask(im), triMask(im)
{
    activeMask = &shaderMask;
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
    cout << "Color Mode" << endl;
    activeMask = &chromaMask;
}
void InputMarshaller::PAD2NoteOn(ofxMidiMessage& msg)
{
    cout << "Shader Mode" << endl;
    activeMask = &shaderMask;
}
void InputMarshaller::PAD3NoteOn(ofxMidiMessage& msg)
{
    cout << "3D Pillar Mode" << endl;
    activeMask = &pillar3DMask;
}
void InputMarshaller::PAD4NoteOn(ofxMidiMessage& msg)
{
    cout << "Follower Mode" << endl;
    activeMask = &followerMask;
}
void InputMarshaller::PAD5NoteOn(ofxMidiMessage& msg)
{
    cout << "Lighting Mode" << endl;
    activeMask = &lightingMask;
}
void InputMarshaller::PAD6NoteOn(ofxMidiMessage& msg)
{
    cout << "WaveForm Mode" << endl;
    activeMask = &audioMask;
}

void InputMarshaller::PAD7NoteOn(ofxMidiMessage& msg)
{
    cout << "rayMarching Mode" << endl;
    activeMask = &rayMarcherMask;
}

void InputMarshaller::PAD8NoteOn(ofxMidiMessage& msg)
{
    cout << "Trianlge Mode" << endl;
    activeMask = &triMask;
}
