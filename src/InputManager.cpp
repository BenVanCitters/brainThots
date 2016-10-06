//
//  InputManager.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#include "InputManager.h"

#define PORT 7400

void InputManager::setupOSC()
{
    receiver.setup(PORT);
    cout << "listening for osc messages on port " << PORT << "\n";
    //mocking shit
    nextUpdateSeconds = 0;
    updateDeltaSeconds = .5;
}


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
        else if(msg.control == 2)
        {
            midiKnob2 = msg.value;
        }
        
        cout << " control: " << msg.control << endl;
        cout << " val: " << msg.value << endl;
    }
}


float InputManager::getMIDIKnob1()
{
    return 10*midiKnob1/128.f;
}

float InputManager::getMIDIKnob2()
{
    return 10*midiKnob2/128.f;
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
//--------------------------------------------------------------
void InputManager::pollMockOSC()
{
    contNum = ofRandom(8.f);
    if(ofGetElapsedTimef() > nextUpdateSeconds)
    {
        brainNote = (int)ofRandom(8.f);
        nextUpdateSeconds += updateDeltaSeconds;
    }
}

float InputManager::getBrainNote()
{
    return brainNote;
}

//--------------------------------------------------------------
void InputManager::pollOSCInput()
{
    if(usingMockOSC)
    {
        pollMockOSC();
        return;
    }
    
    while(receiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        string addr =m.getAddress();
        
        const char* continuousStr = "/continuous";
        const char* notechangeStr = "/notechange";
        const char* rawDataStr = "/rawData";
        const char* addrCStr = addr.c_str();
        if(0 ==  strcmp(addrCStr, continuousStr))
        {
            contNum = m.getArgAsFloat(0);
        }
        else if(0 == strcmp(addrCStr, notechangeStr))
        {
            brainNote = m.getArgAsFloat(0);
            cout << "time: " << ofGetElapsedTimef() << " brainNote: " << brainNote << endl;
            cout << "contNum: "  << contNum << endl;
        }
        else if(0 == strcmp(addrCStr, notechangeStr))
        {
            brainNote = m.getArgAsFloat(0);
            cout << "time: " << ofGetElapsedTimef() << " brainNote: " << brainNote << endl;
            cout << "contNum: "  << contNum << endl;
        }
        else if(0 == strcmp(addrCStr, rawDataStr))
        {
            //            brainBuffer.ad
            float val = m.getArgAsFloat(0);
            cout << "time: " << ofGetElapsedTimef() << " rawData: " << val << endl;
        }
        else
        {
            cout << "unknown: " << addrCStr << endl;
        }
    }
}

void InputManager::keyPressed(int key)
{
    switch(key)
    {
        case 'm':
            usingMockOSC = !usingMockOSC;
            break;
        case 'd':
            showDebug = !showDebug;
            break;
        default:
            break;
    }

}
//--------------------------------------------------------------
void InputManager::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void InputManager::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void InputManager::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void InputManager::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void InputManager::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void InputManager::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void InputManager::mouseExited(int x, int y){
    
}