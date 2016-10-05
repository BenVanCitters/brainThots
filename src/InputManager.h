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
    void setupOSC();
    void audioIn(float * input, int bufferSize, int nChannels);
    void pollOSCInput();
    void pollMockOSC();

    float getMIDIKnob1();
    float getMIDIKnob2();
    
    float getBrainNote();
    
    float curVol = 0.0;
    
    
    //input marshalling from ofApp
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    
private:
    
    //MIDI stuff - see example code in ofxMIDI
    ofxMidiIn midiIn;
    
    float midiKnob1;
    float midiKnob2;
    float midiKnob3;
    float midiKnob4;
    float midiKnob5;
    float midiKnob6;
    float midiKnob7;
    float midiKnob8;
    
    //osc stuff
    ofxOscReceiver receiver;
    float nextUpdateSeconds;
    float updateDeltaSeconds;
    float brainNote;
    float contNum;
    
    bool usingMockOSC = false;
    
    
    //sound input - see example code in audioinputexample
    ofSoundStream soundStream;
    vector <float> left;
    vector <float> right;
    
};

#endif /* InputManager_hpp */
