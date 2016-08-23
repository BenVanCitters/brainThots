#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxMidi.h"
#define PORT 7400

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
        void setupMIDI();
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
        void newMidiMessage(ofxMidiMessage& eventArgs);
    
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    
    int current_msg_string;

    
    int mouseX, mouseY;
    string mouseButtonState;
    
    ofImage receivedImage;
    
    int musicNum;

    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
};
