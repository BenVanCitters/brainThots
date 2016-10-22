//
//  InputManager.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#include "InputManager.h"

#define PORT 7400

void InputManager::setup()
{
    setupMIDI();
    setupOSC();
    setupAudioInput();
}

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
//    midiIn.openPort("MPD26");
    midiIn.openPort(0);
    midiIn.ignoreTypes(false, false, false);
    
    midiIn.addListener(this);
    
    //    midiIn.setVerbose(true);
}

void InputManager::addMIDIPADListener(MIDIPADListener* listener)
{
    for (vector<MIDIPADListener*>::iterator it = midiPadlisteners.begin(); it != midiPadlisteners.end(); ++it)
    {
        if((*it) == listener)
        {
            return;
        }
    }
    midiPadlisteners.push_back(listener);
}
void InputManager::removeMIDIPADListener(MIDIPADListener* listener)
{
    for (vector<MIDIPADListener*>::iterator it = midiPadlisteners.begin(); it != midiPadlisteners.end(); ++it)
    {
        if((*it) == listener)
        {
            midiPadlisteners.erase(it);
            return;
        }
    }
}

// incoming midi
//--------------------------------------------------------------
void InputManager::newMidiMessage(ofxMidiMessage& msg)
{
    //    cout << " MIDI msg: " << msg << endl;
    
    if(msg.status == MIDI_AFTERTOUCH)
    {
        
    }
    //pad down
    if(msg.status == MIDI_NOTE_ON)
    {
        //buttons in pad mode - pitch:PAD# - 36:1, 37:2... 51:16
        if(msg.pitch >= 36 && msg.pitch <=51)
        {
            for (vector<MIDIPADListener*>::iterator it = midiPadlisteners.begin(); it != midiPadlisteners.end(); ++it)
            {
                switch (msg.pitch) {
                    case 36:
                        (*it)->PAD1NoteOn(msg);
                        break;
                    case 37:
                        (*it)->PAD2NoteOn(msg);
                        break;
                    case 38:
                        (*it)->PAD3NoteOn(msg);
                        break;
                    case 39:
                        (*it)->PAD4NoteOn(msg);
                        break;
                    case 40:
                        (*it)->PAD5NoteOn(msg);
                        break;
                    case 41:
                        (*it)->PAD6NoteOn(msg);
                        break;
                    ///////etc
                    default:
                        break;
                }
            }
            cout << "pad/pitch on: " << msg.pitch << " vel: " << msg.velocity << endl;
        }
    }
    if(msg.status == MIDI_CONTROL_CHANGE)
    {
        //knobs in 'Live' preset
        //k5:control 11, k6: 12, k3:13, k4:14, k1:15, k2:16
        if(msg.control >= 11 && msg.control <= 16)
        {
            int knobNum = 0;
            if(msg.control == 15)
            {
                midiKnob1 = msg.value;
                knobNum = 1;
            }
            else if(msg.control == 16)
            {
                midiKnob2 = msg.value;
                knobNum = 2;
            }
            else if(msg.control == 13)
            {
                midiKnob3 = msg.value;
                knobNum = 3;
            }
            else if(msg.control == 14)
            {
                midiKnob4 = msg.value;
                knobNum = 4;
            }
            else if(msg.control == 11)
            {
                midiKnob5 = msg.value;
                knobNum = 5;
            }
            else if(msg.control == 12)
            {
                midiKnob6 = msg.value;
                knobNum = 6;
            }
            
            cout << "knob: " << knobNum << " val: " << msg.value << endl;
        }
        
        if(msg.control >= 1 && msg.control <= 6)
        {
            if(msg.control == 1)
            {
                midiFader1 = msg.value;
            }
            else if(msg.control == 2)
            {
                midiFader2 = msg.value;
            }
            else if(msg.control == 3)
            {
                midiFader3 = msg.value;
            }
            else if(msg.control == 4)
            {
                midiFader4 = msg.value;
            }
            else if(msg.control == 5)
            {
                midiFader5 = msg.value;
            }
            else if(msg.control == 6)
            {
                midiFader6 = msg.value;
            }
            cout << "fader: " << msg.control << " val: " << msg.value << endl;
        }
    }
}


float InputManager::getMIDIKnob1(){return midiKnob1/128.f;}
float InputManager::getMIDIKnob2(){return midiKnob2/128.f;}
float InputManager::getMIDIKnob3(){return midiKnob3/128.f;}
float InputManager::getMIDIKnob4(){return midiKnob4/128.f;}
float InputManager::getMIDIKnob5(){return midiKnob5/128.f;}
float InputManager::getMIDIKnob6(){return midiKnob6/128.f;}

float InputManager::getMIDIFader1(){return midiFader1/128.f;}
float InputManager::getMIDIFader2(){return midiFader2/128.f;}
float InputManager::getMIDIFader3(){return midiFader3/128.f;}
float InputManager::getMIDIFader4(){return midiFader4/128.f;}
float InputManager::getMIDIFader5(){return midiFader5/128.f;}
float InputManager::getMIDIFader6(){return midiFader6/128.f;}


void InputManager::getEEGStreams(float* streams)
{
    for(int i = 0; i < 16; i++)
    {
        streams[i] = eegStreams[i];
    }
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
    
    //what is actual range of eeg signals?
    for(int i = 0; i < 16; i++)
    {
        eegStreams[i] = ofRandom(10.f);
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
//            cout << "time: " << ofGetElapsedTimef() << " brainNote: " << brainNote << endl;
//            cout << "contNum: "  << contNum << endl;
        }
        else if(0 == strcmp(addrCStr, rawDataStr))
        {
            for(int i = 0; i < 16; i++)
            {
                eegStreams[i] =m.getArgAsFloat(i);
            }
            //print vals
//            cout << "time: " << ofGetElapsedTimef()<< " rawData: ";
//            for(int i = 0; i < 16; i++)
//            {
//                cout << eegStreams[i] << ", ";
//            }
//            cout << endl;
        }
        else
        {
//            cout << "unknown: " << addrCStr << endl;
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