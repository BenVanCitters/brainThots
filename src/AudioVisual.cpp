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
    
    mMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mMesh.setUsage(GL_DYNAMIC_DRAW);
    for(int i = 0; i < sampleCount; i++)
    {
        samples[i] = 0;
        mMesh.addVertex(ofVec2f(0,0));
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

void AudioVisual::update(float dt, WaveFormMask* inputMask)
{
    float amp = inputMask->amplitude.get();
    float lineWeight = inputMask->lineWeight.get();
    ofVec2f offset(0,lineWeight);
    float shapeLerp = inputMask->shapeLerp.get();
    float radius = currentScreenSz.y/4;
    float sectionLen = currentScreenSz.x/(sampleCount-1);
    ofVec2f mid(currentScreenSz.x/2,0);
    for(int i = 0; i < sampleCount; i++)
    {
        ofVec3f v(-i*sectionLen, samples[i]*amp, 0);
        ofVec3f l1 = v-offset;
        ofVec3f l2 = v+offset;

        float pct = (i)*1.f/(sampleCount-1);
        float currentRadian = pct*TWO_PI-PI/2.0;
        ofVec3f circlePos(cosf(currentRadian),sinf(currentRadian));
        ofVec3f c1 = (radius+samples[i]*amp-lineWeight)*circlePos + mid;
        ofVec3f c2 = (radius+samples[i]*amp+lineWeight)*circlePos + mid;

        ofVec3f b1 = shapeLerp*c1 + (shapeLerp-1)*l1;
        ofVec3f b2 = shapeLerp*c2 + (shapeLerp-1)*l2;

        mMesh.setVertex(2*i, b1);
        mMesh.setVertex(2*i+1, b2);
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