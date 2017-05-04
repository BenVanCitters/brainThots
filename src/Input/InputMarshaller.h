//
//  InputMarshaller.h
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
    RayMarcherInputMask rayMarcherMask;
    Pillar3DInputMask pillar3DMask;
    FollowerMask followerMask;
    LightingMask lightingMask;
    WaveFormMask audioMask;
    ChromaMask chromaMask;
    TriangleMask triMask;
    
    void PAD1NoteOn(ofxMidiMessage& msg);
    void PAD2NoteOn(ofxMidiMessage& msg);
    void PAD3NoteOn(ofxMidiMessage& msg);
    void PAD4NoteOn(ofxMidiMessage& msg);
    void PAD5NoteOn(ofxMidiMessage& msg);
    void PAD6NoteOn(ofxMidiMessage& msg);
    void PAD7NoteOn(ofxMidiMessage& msg);
    void PAD8NoteOn(ofxMidiMessage& msg);
    void update(float dt);
};
#endif /* InputMarshaller_h */
