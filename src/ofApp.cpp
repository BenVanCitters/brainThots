#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    setupMIDI();
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
}


//--------------------------------------------------------------
void ofApp::setupMIDI()
{
    midiIn.openPort("LPD8");

    midiIn.ignoreTypes(false, false, false);
    
    midiIn.addListener(this);
    
//    midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        musicNum = m.getArgAsInt32(0);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString(ofToString(musicNum),500,200);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::newMidiMessage(ofxMidiMessage& msg)
{
    // make a copy of the latest message
    midiMessage = msg;
}
