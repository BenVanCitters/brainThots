#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "InputManager.h"
#include "ColorFollower.h"
#include "ColorMeshParticles.h"
#include "RawBrainGraphic.h"
#include "Brain3D.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
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
        
    ofTrueTypeFont font;
    
    int current_msg_string;

    
    int mouseX, mouseY;
    string mouseButtonState;
    

    float shaderTime;
 
    ColorFollower cf;

    ColorMeshParticles particles;
    InputManager im;
    
    ofLight directionalLight;
    ofFbo blurBuffer;
    ofFbo fbo;
    ofShader hPassShader;
    ofShader vPassShader;
        
    RawBrainGraphic rbg;
    Brain3D brain3d;
};
