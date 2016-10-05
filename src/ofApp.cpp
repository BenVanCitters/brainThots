#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0, 0, 0);
    im.setupMIDI();
    im.setupOSC();
    im.setupAudioInput();
    setupLights();
    
    setupFBO();
    setupShaders();
}

string getStringFromFilePath(string filepath)
{
    std::ifstream fileStream(filepath);
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    return stringStream.str();
}

#define STRINGIFY(A) #A
void ofApp::setupShaders()
{
    string data = ofFilePath::join(ofFilePath::getCurrentExeDir(), "../../../data/");
    string vertShader = getStringFromFilePath(data + "shaders/defaultVert.glsl");
    
    string HQBlurHorizontalProgram = getStringFromFilePath(data + "shaders/horizontalPass.glsl");
    
    hPassShader.setupShaderFromSource(GL_VERTEX_SHADER, vertShader);
    hPassShader.setupShaderFromSource(GL_FRAGMENT_SHADER, HQBlurHorizontalProgram);
    hPassShader.linkProgram();
    
    string HQBlurVerticalProgram = getStringFromFilePath(data + "shaders/verticalPass.glsl");

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
    directionalLight.setPosition(0, 0, -1000);
    directionalLight.setDiffuseColor(ofColor(128.f, 128.f, 128.f));
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    
    // set the direction of the light
    // set it pointing from left to right -> //
    directionalLight.setOrientation( ofVec3f(100, 1000, -900) );
}


//--------------------------------------------------------------
void ofApp::update()
{
    brain3d.update();
    shaderTime = ofGetElapsedTimef()*3;
    rbg.update();
    im.pollOSCInput();
    
    cf.setCurrentIndex(im.getBrainNote());
    cf.update();
    particles.setTargetVector(cf.getCurrentPosition());
    particles.color = cf.currentColor;
    particles.update();
    
    
    //blur first/horizontal-pass stuff
    blurBuffer.begin();
    hPassShader.begin();
    hPassShader.setUniformTexture("tex0", fbo.getTexture() , 1 );
    hPassShader.setUniform2f("uResolution", ofVec2f(ofGetScreenWidth(), ofGetScreenHeight() ));
    hPassShader.setUniform1f("blurAmountShaderVar", 25);
    hPassShader.setUniform1f("time", shaderTime);
    float ghg =im.getMIDIKnob1();
    hPassShader.setUniform1f("factor1", 5);
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
//    ofRect(<#float x1#>, <#float y1#>, <#float w#>, <#float h#>)
    fbo.begin();
    vPassShader.begin();
    vPassShader.setUniformTexture("tex0", blurBuffer.getTexture() , 1 );
    vPassShader.setUniform2f("uResolution", ofVec2f(ofGetScreenWidth(), ofGetScreenHeight() ));
    vPassShader.setUniform1f("blurAmountShaderVar", 25);
    vPassShader.setUniform1f("time", shaderTime);
    float ghg =im.getMIDIKnob1();
    vPassShader.setUniform1f("factor1", ghg);
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
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    ofEnableLighting();
    directionalLight.enable();
    
    cf.draw(im.curVol);
    
    brain3d.draw();
    
    directionalLight.disable();
    ofDisableLighting();
    
    particles.draw();
    glDisable(GL_DEPTH_TEST);
    fbo.end();
    fbo.draw(0,0);
    rbg.draw();

    ofSetColor(255, 255, 255 );
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    im.keyPressed(key);
    
    switch(key)
    {
        case 'f':
            ofToggleFullscreen();
            fbo.begin();
            ofClear(0, 0, 0, 0);
            fbo.end();
            blurBuffer.begin();
            ofClear(0, 0, 0, 0);
            blurBuffer.end();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ im.keyReleased(key); }

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ im.mouseMoved(x,y); }

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ im.mouseDragged(x,y,button); }

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ im.mousePressed(x,y,button); }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ im.mouseReleased(x,y,button); }

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ im.mouseEntered(x,y); }

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ im.mouseExited(x,y); }

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}





