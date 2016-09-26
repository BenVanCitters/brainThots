//
//  InputManager.hpp
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxMidi.h"
class InputManager : public ofxMidiListener
{
public:
    void newMidiMessage(ofxMidiMessage& msg);
    void setupMIDI();
    void setupAudioInput();
    void audioIn(float * input, int bufferSize, int nChannels);
    float getMIDIKnob1();
    
    float curVol = 0.0;
private:
    
    //MIDI stuff - see example code in ofxMIDI
    float midiKnob1;
    float midiKnob2;
    float midiKnob3;
    float midiKnob4;
    float midiKnob5;
    float midiKnob6;
    float midiKnob7;
    float midiKnob8;
    
    
    ofxMidiIn midiIn;
    
    //sound input - see example code in audioinputexample
    ofSoundStream soundStream;
    vector <float> left;
    vector <float> right;
};

#endif /* InputManager_hpp */
