#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "InputManager.h"
#include "ColorFollower.h"
#include "ColorMeshParticles.h"
#include "RawBrainGraphic.h"

#define PORT 7400

class ofApp : public ofBaseApp{

	public:
		void setup();
        void setupAudioInput();
        void setupFBO();
        void setupLights();
        void setupShaders();
        void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void pollOSCInput();
    
        void pollMockOSC();
        //listener functions
        void newMidiMessage(ofxMidiMessage& eventArgs);
        void audioIn(float * input, int bufferSize, int nChannels);
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    
    int current_msg_string;

    
    int mouseX, mouseY;
    string mouseButtonState;
    
    
    float nextUpdateSeconds;
    float updateDeltaSeconds;
    
    float musicNum;
    float contNum;
    //sound input - see example code in audioinputexample
    ofSoundStream soundStream;
    float curVol = 0.0;
    float shaderTime;
    //MIDI stuff - see example code in ofxMIDI
 
    ColorFollower cf;

    ColorMeshParticles particles;
    InputManager im;
    
    ofLight directionalLight;
    ofFbo blurBuffer;
    ofFbo fbo;
    ofShader hPassShader;
    ofShader vPassShader;
    
    ofImage tmp;
    
    RawBrainGraphic rbg;
    
    vector <float> left;
    vector <float> right;
};
