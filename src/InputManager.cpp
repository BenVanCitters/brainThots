//
//  InputManager.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#include "InputManager.h"

void InputManager::setupMIDI()
{
    midiIn.openPort("LPD8");
    
    midiIn.ignoreTypes(false, false, false);
    
    midiIn.addListener(this);
    
    //    midiIn.setVerbose(true);

}

// incoming midi
//--------------------------------------------------------------
void InputManager::newMidiMessage(ofxMidiMessage& msg)
{
//    stringstream text;

    
    //buttons in pad mode
    if(msg.pitch >= 36 && msg.pitch <=43)
    {
        cout << " pitch: " << msg.pitch << endl;
    }
    //knobs in pad mode
    if(msg.control >= 1 && msg.control <= 8)
    {
        factor1 = msg.value;
        cout << " control: " << msg.control << endl;
        cout << " val: " << msg.value << endl;
    }
}


float InputManager::getFactor1()
{
    return 4*factor1/128.f;
}