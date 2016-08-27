#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0, 0, 0);
    setupMIDI();
    setupAudioInput();
    setupLights();
    
    setupFBO();
    setupShaders();
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    //mocking shit
    nextUpdateSeconds = 0;;
    updateDeltaSeconds = .5;
}

#define STRINGIFY(A) #A
void ofApp::setupShaders()
{
    tmp.load("/Users/admin/Downloads/IMAG3202.jpg");
    string vertShader = STRINGIFY(void main()
    {
        gl_TexCoord[0] = gl_MultiTexCoord0;
        vec4 eyeCoord  = gl_ModelViewMatrix * gl_Vertex;
        gl_Position    = gl_ProjectionMatrix * eyeCoord;
    });
    
    string HQBlurHorizontalProgram = STRINGIFY(
                                     // Precision
                                     //precision highp float;
                                     
                                     // Uniforms
                                     uniform sampler2DRect tex0;
                                     uniform vec2 uResolution;
                                     
                                     uniform float blurAmountShaderVar;
                                     uniform vec2 sampleOffset;
                                     
                                     float weights[21];
                                     
                                     void main()
    {
        float weightCount = 10.0;
        weights[0] = 0.0091679276560113852;
        weights[1] = 0.014053461291849008;
        weights[2] = 0.020595286319257878;
        weights[3] = 0.028855245532226279;
        weights[4] = 0.038650411513543079;
        weights[5] = 0.049494378859311142;
        weights[6] = 0.060594058578763078;
        weights[7] = 0.070921288047096992;
        weights[8] = 0.079358891804948081;
        weights[9] = 0.084895951965930902;
        weights[10] = 0.086826196862124602;
        weights[11] = 0.084895951965930902;
        weights[12] = 0.079358891804948081;
        weights[13] = 0.070921288047096992;
        weights[14] = 0.060594058578763092;
        weights[15] = 0.049494378859311121;
        weights[16] = 0.0386504115135431;
        weights[17] = 0.028855245532226279;
        weights[18] = 0.020595286319257885;
        weights[19] = 0.014053461291849008;
        weights[20] = 0.00916792765601138;
        
        vec2 sampleOffset = vec2(blurAmountShaderVar,blurAmountShaderVar);
        sampleOffset *= .1; //~~ /= weightCount;
        
        vec2 position = uResolution*gl_TexCoord[0].st;
        vec4 sum = vec4( 0.0, 0.0, 0.0 , 0.0);
        vec2 baseOffset = -weightCount * sampleOffset;
        
        vec2 offset = vec2( 0.0, 0.0 );
        for( int s = 0; s < 21; ++s )
        {
            vec2 texcord = position.st + vec2(baseOffset.x + offset.x, 0.0);
            sum += texture2DRect( tex0, texcord ) * weights[s];
            offset.x += sampleOffset.x;
        }
        
        gl_FragColor = sum;// vec4(vTexCoord.x,vTexCoord.y,0.0,1.0);//vec4(gl_TexCoord[0].x,gl_TexCoord[0].y,0.0,1.0);//texture2DRect( tex0, uResolution*gl_TexCoord[0].st );//
    }
                                     );
    hPassShader.setupShaderFromSource(GL_VERTEX_SHADER, vertShader);
    hPassShader.setupShaderFromSource(GL_FRAGMENT_SHADER, HQBlurHorizontalProgram);
    
        hPassShader.linkProgram();
//    hPassShader.load("", "shaders/HQBlurHorizontal.fsh", "");
//    hPassShader.load("shaders/basicVert.vert", "shaders/HQBlurHorizontal.fsh", "");

    
//    vPassShader.load("", "shaders/HQBlurVertical.fsh", "");
//    vPassShader.load("shaders/basicVert.vert", "shaders/HQBlurVertical.fsh", "");
    
    string HQBlurVerticalProgram = STRINGIFY(
                                             // Uniforms
                                             uniform sampler2DRect tex0;
                                             uniform vec2 uResolution;
                                             
                                             uniform float blurAmountShaderVar;
                                             uniform vec2 sampleOffset;
                                             
                                             float weights[21];
                                             
                                             void main()
    {
        float weightCount = 10.0;
        weights[0] = 0.0091679276560113852;
        weights[1] = 0.014053461291849008;
        weights[2] = 0.020595286319257878;
        weights[3] = 0.028855245532226279;
        weights[4] = 0.038650411513543079;
        weights[5] = 0.049494378859311142;
        weights[6] = 0.060594058578763078;
        weights[7] = 0.070921288047096992;
        weights[8] = 0.079358891804948081;
        weights[9] = 0.084895951965930902;
        weights[10] = 0.086826196862124602;
        weights[11] = 0.084895951965930902;
        weights[12] = 0.079358891804948081;
        weights[13] = 0.070921288047096992;
        weights[14] = 0.060594058578763092;
        weights[15] = 0.049494378859311121;
        weights[16] = 0.0386504115135431;
        weights[17] = 0.028855245532226279;
        weights[18] = 0.020595286319257885;
        weights[19] = 0.014053461291849008;
        weights[20] = 0.00916792765601138;
        
        vec2 sampleOffset = vec2(blurAmountShaderVar,blurAmountShaderVar);
        sampleOffset *= .1; //~~ /= weightCount;
        
        vec2 position = uResolution*gl_TexCoord[0].st;
        vec4 sum = vec4( 0.0, 0.0, 0.0 , 0.0);
        vec2 baseOffset = -weightCount * sampleOffset;
        
        vec2 offset = vec2( 0.0, 0.0 );
        for( int s = 0; s < 21; ++s )
        {
            vec2 texcord = position.st + vec2(0.0, baseOffset.y + offset.y);
            sum += texture2DRect( tex0, texcord ) * weights[s];
            offset.y += sampleOffset.y;
        }
        
        gl_FragColor = sum;//sum;//vec4(1.0,0.0,0.0,1.0);//vec4(vTexCoord.x,vTexCoord.y,0.0,1.0);//texture2D( texture[0], vTexCoord );//
    }

    );
    vPassShader.setupShaderFromSource(GL_VERTEX_SHADER, vertShader);
    vPassShader.setupShaderFromSource(GL_FRAGMENT_SHADER, HQBlurVerticalProgram);
    vPassShader.linkProgram();
}

void ofApp::setupFBO()
{
    int drawWidth = ofGetScreenWidth();
    int drawHeight = ofGetScreenHeight();
    
    
    //allocate and clear the framebuffer
    blurBuffer.allocate(drawWidth, drawHeight, GL_RGBA);
    blurBuffer.begin();
    ofClear(0, 0, 0, 0);
    blurBuffer.end();
    
    
    //allocate and clear the framebuffer
    fbo.allocate(drawWidth, drawHeight, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();
    
}

void ofApp::setupLights()
{
    directionalLight.setDiffuseColor(ofColor(128.f, 128.f, 128.f));
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    
    // set the direction of the light
    // set it pointing from left to right -> //
    directionalLight.setOrientation( ofVec3f(0, 0, 900) );

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
    particles.color = cf.currentColor;
    particles.update();
    
    
    //blur first/horizontal-pass stuff
    blurBuffer.begin();
    hPassShader.begin();
    hPassShader.setUniformTexture("tex0", fbo.getTexture() , 1 );
    hPassShader.setUniform2f("uResolution", ofVec2f(ofGetScreenWidth(), ofGetScreenHeight() ));
    hPassShader.setUniform1f("blurAmountShaderVar", 15);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0,0);
    
    glTexCoord2f(1, 0);
    glVertex3f(ofGetScreenWidth(), 0, 0);
    
    glTexCoord2f(1, 1);
    glVertex3f(ofGetScreenWidth(), ofGetScreenHeight(),0);
    
    glTexCoord2f(0, 1);
    glVertex3f(0, ofGetScreenHeight(), 0);
    glEnd();
    
    hPassShader.end();
    blurBuffer.end();
    //end blur
}

//--------------------------------------------------------------
void ofApp::draw()
{
    fbo.begin();
    vPassShader.begin();
    vPassShader.setUniformTexture("tex0", blurBuffer.getTexture() , 1 );
    vPassShader.setUniform2f("uResolution", ofVec2f(ofGetScreenWidth(), ofGetScreenHeight() ));
    vPassShader.setUniform1f("blurAmountShaderVar", 15);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0,0);
    
    glTexCoord2f(1, 0);
    glVertex3f(ofGetScreenWidth(), 0, 0);
    
    glTexCoord2f(1, 1);
    glVertex3f(ofGetScreenWidth(), ofGetScreenHeight(),0);
    
    glTexCoord2f(0, 1);
    glVertex3f(0, ofGetScreenHeight(), 0);
    glEnd();
    vPassShader.end();
    
    
//        ofEnableLighting();
//        directionalLight.enable();
    
    ofDrawBitmapString(ofToString(musicNum),500,200);
    cf.draw();
    particles.draw();
    
    ofDisableLighting();
    
    fbo.end();
    fbo.draw(0,0);
}


//--------------------------------------------------------------
void ofApp::pollMockOSC()
{
    contNum = ofRandom(8.f);
    if(ofGetElapsedTimef() > nextUpdateSeconds)
    {
        musicNum = (int)ofRandom(8.f);
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
    switch(key)
    {
        case 'f':
            ofToggleFullscreen();
            fbo.begin();
            ofClear(0, 0, 0, 0);
            fbo.end();
            break;
        default:
            break;
    }
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

