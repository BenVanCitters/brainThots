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
class InputMask : public MIDIPADListener
{
public:
    InputMask(InputManager* input);
    void update(float dt);
    
    LerpedFloat brain3DScale;
    LerpedFloat blurAmount;
    
    void PAD1NoteOn(ofxMidiMessage& msg);

    void PAD2NoteOn(ofxMidiMessage& msg);

    void PAD3NoteOn(ofxMidiMessage& msg);

    void PAD4NoteOn(ofxMidiMessage& msg);

    void PAD5NoteOn(ofxMidiMessage& msg);

    void PAD6NoteOn(ofxMidiMessage& msg);
    
private:
    InputManager* im;
};
#endif /* InputMask_h */
