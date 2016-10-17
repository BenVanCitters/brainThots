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

    void setup();
    void setupMIDI();
    void setupAudioInput();
    void setupOSC();
    void audioIn(float * input, int bufferSize, int nChannels);
    void pollOSCInput();
    void pollMockOSC();

    float getMIDIKnob1();
    float getMIDIKnob2();
    float getMIDIKnob3();
    float getMIDIKnob4();
    float getMIDIKnob5();
    float getMIDIKnob6();
    
    float getMIDIFader1();
    float getMIDIFader2();
    float getMIDIFader3();
    float getMIDIFader4();
    float getMIDIFader5();
    float getMIDIFader6();
    
    float getBrainNote();
    
    float curVol = 0.0;
    
    bool showDebug;
    
    //input marshalling from ofApp
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    
    void getEEGStreams(float* streams);
    
private:
    
    //MIDI stuff - see example code in ofxMIDI
    ofxMidiIn midiIn;

    
    float midiKnob1;
    float midiKnob2;
    float midiKnob3;
    float midiKnob4;
    float midiKnob5;
    float midiKnob6;
    
    float midiFader1;
    float midiFader2;
    float midiFader3;
    float midiFader4;
    float midiFader5;
    float midiFader6;
    //osc stuff
    ofxOscReceiver receiver;
    float nextUpdateSeconds;
    float updateDeltaSeconds;
    float brainNote;
    float contNum;
    
    float eegStreams[16];
    
    bool usingMockOSC = false;
    
    
    //sound input - see example code in audioinputexample
    ofSoundStream soundStream;
    vector <float> left;
    vector <float> right;
    
};

#endif /* InputManager_hpp */
