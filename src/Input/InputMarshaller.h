//
//  InputMarshaller.hpp
//  brainThots
//
//  Created by Ben Van Citters on 10/18/16.
//
//

#ifndef InputMarshaller_h
#define InputMarshaller_h


#include <stdio.h>
#include "InputManager.h"
#include "InputMask.h"

class InputMarshaller : public MIDIPADListener
{
    
public:
    InputMarshaller(InputManager* im);
    InputMask* activeMask;
    ShaderInputMask shaderMask;
    RBGInputMask rbgLinesMask;
    Brain3DInputMask brain3DMask;
//    InputMask brain3DMask;
    
    void PAD1NoteOn(ofxMidiMessage& msg);
    void PAD2NoteOn(ofxMidiMessage& msg);
    void PAD3NoteOn(ofxMidiMessage& msg);
    void PAD4NoteOn(ofxMidiMessage& msg);
    void PAD5NoteOn(ofxMidiMessage& msg);
    void PAD6NoteOn(ofxMidiMessage& msg);
    void update(float dt);
};
#endif /* InputMarshaller_h */
