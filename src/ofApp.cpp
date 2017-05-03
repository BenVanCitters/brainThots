#include "ofApp.h"

ofApp::ofApp():
inputMarshaller(&inputManager),audioVisual(256), lightingRig(ofVec2f(ofGetScreenWidth(),ofGetScreenHeight()))
{
//    super();
}

//--------------------------------------------------------------
void ofApp::setup()
{
    updateScreenSize(ofGetScreenWidth(),ofGetScreenHeight());
    
    ofHideCursor();
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0, 0, 0);
    
    inputManager.setup();
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
    
    string tintProgram = getStringFromFilePath(data + "shaders/tint.glsl");
    tintShader.setupShaderFromSource(GL_VERTEX_SHADER, vertShader);
    tintShader.setupShaderFromSource(GL_FRAGMENT_SHADER, tintProgram);
    tintShader.linkProgram();
    
}

void ofApp::setupFBO()
{
    //allocate and clear the framebuffer
    blurBuffer.allocate(cachedScrSz.x, cachedScrSz.y, GL_RGBA);
    blurBuffer.begin();
    ofClear(0, 0, 0, 255);
    blurBuffer.end();
    
    //allocate and clear the framebuffer
    fbo.allocate(cachedScrSz.x, cachedScrSz.y, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
}


//--------------------------------------------------------------
void ofApp::update()
{
    float dt = ofGetLastFrameTime();
    
    inputMarshaller.update(dt);
    
    inputManager.pollOSCInput();
    float eegStreams[16];
    inputManager.getEEGStreams(eegStreams);

    chromaController.update(dt,&inputMarshaller.chromaMask);
    
    audioVisual.setSamples(inputManager.getAudioStream());
    audioVisual.update(dt,&inputMarshaller.audioMask);
    audioVisual.currentColor = chromaController.currentColor;
    
    pillar.update(dt, &inputMarshaller.pillar3DMask);
    pillar.lerpSpeed = inputMarshaller.followerMask.speed.get();
    pillar.fade = inputManager.getMIDIKnob4();
    pillar.currentColor = chromaController.currentColor;
    
    
    particles.fade = inputManager.getMIDIKnob6();
//    particles.setTargetVector(pillar.getCurrentPosition());
    particles.color = chromaController.currentColor;
    particles.update(dt);
    particles.strokeWeight = inputMarshaller.followerMask.particleSize.get();
    
    lightingRig.fade =inputManager.getMIDIKnob5();
    lightingRig.update(dt, &inputMarshaller.lightingMask);
    
    //blur first/horizontal-pass stuff
    shaderTime = ofGetElapsedTimef()*3;
    blurBuffer.begin();
    hPassShader.begin();
    hPassShader.setUniformTexture("tex0", fbo.getTexture() , 1 );
    hPassShader.setUniform2f("uResolution", cachedScrSz);
    hPassShader.setUniform1f("blurAmountShaderVar", inputMarshaller.shaderMask.blurAmount.get());
    hPassShader.setUniform1f("time", shaderTime);
    hPassShader.setUniform1f("factor1", inputMarshaller.shaderMask.shaderVar1.get());
    hPassShader.setUniform1f("factor2", inputMarshaller.shaderMask.shaderVar2.get());
    hPassShader.setUniform1f("factor3", inputMarshaller.shaderMask.shaderVar3.get());
    hPassShader.setUniform1f("factor4", inputMarshaller.shaderMask.shaderVar4.get());
    
    float knob2 =inputManager.getMIDIKnob2();
    hPassShader.setUniform1f("blackout", knob2);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0,0);
    
    glTexCoord2f(1, 0);
    glVertex3f(cachedScrSz.x, 0, 0);
    
    glTexCoord2f(1, 1);
    glVertex3f(cachedScrSz.x, cachedScrSz.y,0);
    
    glTexCoord2f(0, 1);
    glVertex3f(0, cachedScrSz.y, 0);
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
    vPassShader.setUniform2f("uResolution", cachedScrSz);
    vPassShader.setUniform1f("blurAmountShaderVar", inputMarshaller.shaderMask.blurAmount.get());
    vPassShader.setUniform1f("time", shaderTime);
    vPassShader.setUniform1f("factor1", inputMarshaller.shaderMask.shaderVar1.get());
    vPassShader.setUniform1f("factor2", inputMarshaller.shaderMask.shaderVar2.get());
    vPassShader.setUniform1f("factor3", inputMarshaller.shaderMask.shaderVar3.get());
    vPassShader.setUniform1f("factor4", inputMarshaller.shaderMask.shaderVar4.get());
    float knob2 =inputManager.getMIDIKnob2();
    vPassShader.setUniform1f("blackout", knob2);

    //this action - rendering the second blur pass - would be faster with a quad in vram
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0,0);
    
    glTexCoord2f(1, 0);
    glVertex3f(cachedScrSz.x, 0, 0);
    
    glTexCoord2f(1, 1);
    glVertex3f(cachedScrSz.x, cachedScrSz.y,0);
    
    glTexCoord2f(0, 1);
    glVertex3f(0, cachedScrSz.y, 0);
    glEnd();
    vPassShader.end();
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    
    
    audioVisual.draw();
    
    lightingRig.enable();
    
    pillar.draw(inputManager.curVol);
    
    lightingRig.disable();
    
    particles.draw();
    
    glDisable(GL_DEPTH_TEST);
    
    fbo.end();
    tintShader.begin();
    tintShader.setUniformTexture("tex0", fbo.getTexture() , 1 );
    tintShader.setUniform2f("uResolution", cachedScrSz);
    
    tintShader.setUniform4f("tintColor", ofVec4f(chromaController.currentColor.r,
                                                 chromaController.currentColor.g,
                                                 chromaController.currentColor.b,256)/256.f);
    fbo.draw(0,0);
    tintShader.end();
    
    
    if(inputManager.showDebug)
    {
        ofFill();
        ofSetColor(chromaController.currentColor);
        ofDrawRectangle(0, 0, 100, 100);
        
        ofSetColor(255, 255, 255 );
        ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    }
}

void ofApp::updateScreenSize(int w, int h)
{
    cachedScrSz = ofVec2f(w,h);
    lightingRig.setWindowSize(cachedScrSz);
    pillar.currentScreenSize = cachedScrSz;
    particles.currentScreenSz = cachedScrSz;
    audioVisual.currentScreenSz = cachedScrSz;

    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
    blurBuffer.begin();
    ofClear(0, 0, 0, 255);
    blurBuffer.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    inputManager.keyPressed(key);
    
    switch(key)
    {
        case 'f':
            ofToggleFullscreen();
            fbo.begin();
            ofClear(0, 0, 0, 255);
            fbo.end();
            blurBuffer.begin();
            ofClear(0, 0, 0, 255);
            blurBuffer.end();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ inputManager.keyReleased(key); }

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ inputManager.mouseMoved(x,y); }

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){ inputManager.mouseDragged(x,y,button); }

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){ inputManager.mousePressed(x,y,button); }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ inputManager.mouseReleased(x,y,button); }

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){ inputManager.mouseEntered(x,y); }

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){ inputManager.mouseExited(x,y); }

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    updateScreenSize(w,h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}





