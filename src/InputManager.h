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
    float getFactor1();
private:
    
    float factor1;
    ofxMidiIn midiIn; 
};

#endif /* InputManager_hpp */
