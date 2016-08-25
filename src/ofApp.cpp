#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
//    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0, 0, 0);
    setupMIDI();
    setupAudioInput();
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    //mocking shit
    nextUpdateSeconds = 0;;
    updateDeltaSeconds = .5;
}


void ofApp::setupAudioInput()
{
    int bufferSize = 256;
    
//    left.assign(bufferSize, 0.0);
//    right.assign(bufferSize, 0.0);
//    volHistory.assign(400, 0.0);
//    
//    bufferCounter	= 0;
//    drawCounter		= 0;
//    smoothedVol     = 0.0;
//    scaledVol		= 0.0;
//    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
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
//    pollOSCInput();
    pollMockOSC();
    cf.setCurrentIndex(musicNum);
    cf.update();
    particles.setTargetVector(cf.getCurrentPosition());
    particles.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofDrawBitmapString(ofToString(musicNum),500,200);
    cf.draw();
    particles.draw();
}


//--------------------------------------------------------------
void ofApp::pollMockOSC()
{
    contNum = ofRandom(7.f);
    if(ofGetElapsedTimef() > nextUpdateSeconds)
    {
        musicNum = (int)ofRandom(7.f);
        nextUpdateSeconds += updateDeltaSeconds;
    }
    
}

//--------------------------------------------------------------
void ofApp::pollOSCInput()
{
    while(receiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        string addr =m.getAddress();
        
        const char* continuousStr = "/continuous";
        const char* notechangeStr = "/notechange";
        const char* addrCStr = addr.c_str();
        if(0 ==  strcmp(addrCStr, continuousStr))
        {
            contNum = m.getArgAsFloat(0);
        }
        else if(0 == strcmp(addrCStr, notechangeStr))
        {
            musicNum = m.getArgAsFloat(0);
            cout << "time: " << ofGetElapsedTimef() << " musicNum: " << musicNum << endl;
            cout << "contNum: "  << contNum << endl;
        }
        else
        {
            cout << "unknown: " << addrCStr << endl;
        }
    }
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

// incoming midi
//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg)
{
    // make a copy of the latest message
    midiMessage = msg;
}

// incoming audio stream
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
//    for (int i = 0; i < bufferSize; i++){
//        left[i]		= input[i*2]*0.5;
//        right[i]	= input[i*2+1]*0.5;
//        
//        curVol += left[i] * left[i];
//        curVol += right[i] * right[i];
//        numCounted+=2;
//    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
//    bufferCounter++;
    
}

