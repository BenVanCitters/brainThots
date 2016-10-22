//
//  AudioVisual.cpp
//  brainThots
//
//  Created by Ben Van Citters on 10/20/16.
//
//

#include "AudioVisual.h"

AudioVisual::AudioVisual(int sampleCount)
{
    this->sampleCount = sampleCount;
    samples = new float[sampleCount];
    
    mMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mMesh.setUsage(GL_DYNAMIC_DRAW);
    for(int i = 0; i < sampleCount; i++)
    {
        samples[i] = 0;
        mMesh.addVertex(ofVec2f(0,0));
    }
}

AudioVisual::~AudioVisual()
{
    delete[] samples;
}

void AudioVisual::setSamples(vector<float> vec)
{
    int i = 0;
    for (vector<float>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        samples[i++] = (*it);
    }
}

void AudioVisual::update(float dt)
{
    float sectionLen = 2000.f/sampleCount;
    for(int i = 0; i < sampleCount; i++)
    {
        ofVec3f v(i*sectionLen, samples[i]*500, 0);
        mMesh.setVertex(i, v);
    }
   
}

void AudioVisual::draw()
{
    ofPushMatrix();
    ofPushStyle();
    
    ofVec3f t(0,currentScreenSz.y/2.f,0);
    ofTranslate(t);
    ofSetColor(255, 255, 255);
    ofSetLineWidth(5);
    mMesh.draw();
    
    ofPopStyle();
    ofPopMatrix();
}