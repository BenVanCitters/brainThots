#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "InputManager.h"
#include "LightingRig.h"
#include "ColorFollower.h"
#include "ColorMeshParticles.h"
#include "Brain3D.h"
#include "InputMarshaller.h"
#include "RawBrainGraphic.h"

class ofApp : public ofBaseApp{

	public:
        ofApp();
		void setup();
        void setupFBO();
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
    
    void updateScreenSize(int w, int h);
    
    float shaderTime;
 
    ColorFollower colorFollower;
    ColorMeshParticles particles;
    InputManager inputManager;
    InputMarshaller inputMarshaller;
    LightingRig lightingRig;
    ofFbo blurBuffer;
    ofFbo fbo;
    ofShader hPassShader;
    ofShader vPassShader;
        
    Brain3D brain3d;
    
    RawBrainGraphic rawBrainGraphic;
    ofVec2f cachedScrSz;
};
