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
        if(msg.control == 1)
        {
            midiKnob1 = msg.value;    
        }
        
        cout << " control: " << msg.control << endl;
        cout << " val: " << msg.value << endl;
    }
}


float InputManager::getMIDIKnob1()
{
    return 4*midiKnob1/128.f;
}


void InputManager::setupAudioInput()
{
    int bufferSize = 256;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    soundStream.setup( 0, 2, 44100, bufferSize, 4);
}

// incoming audio stream
//--------------------------------------------------------------
void InputManager::audioIn(float * input, int bufferSize, int nChannels)
{
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
}
