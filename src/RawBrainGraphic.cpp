//
//  RawBrainGraphic.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/14/16.
//
//

#include "RawBrainGraphic.h"



RawBrainGraphic::RawBrainGraphic(int count)
{
    for(int i = 0; i < count; i++)
    {
        brainBuffers.push_back(vector<float>());
    }
    
    ofVboMesh tMesh;
    tMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    tMesh.setUsage(GL_DYNAMIC_DRAW);
    for(int j = 0; j < maxFloatLen; j++)
    {
        tMesh.addVertex(ofVec2f(0,0));
    }
    
    for(int i = 0; i < LINE_COUNT; i++)
    {
        mMesh[i] = ofVboMesh(tMesh);
    }
}

void RawBrainGraphic::update()
{
    float lineLen = 500;
    
    int j = 0;
    for (vector<vector<float>>::iterator it = brainBuffers.begin() ; it != brainBuffers.end(); ++it)
    {
        float sectionLen = lineLen/it->size();
        for(int i = 0; i < it->size(); i++)
        {
            ofVec3f v(it->at(i), -i*sectionLen, 0);
            mMesh[j].setVertex(i, v);
        }
        j++;
    }
//    printVecs();
}

void RawBrainGraphic::printVecs()
{
    int k = 0;
    for (vector<vector<float>>::iterator it = brainBuffers.begin() ; it != brainBuffers.end(); ++it)
    {
        cout << "\nvec" << k << ": ";
        for(int i = 0; i < it->size(); i++)
        {
            cout << it->at(i) << ",";
        }
        k++;
    }
}

void RawBrainGraphic::draw()
{
    for(int i = 0; i < LINE_COUNT; i++)
    {
        ofPushMatrix();
        ofMultMatrix(mTransformations[i]);
        ofSetColor(255,255,255,255);
        mMesh[i].draw();
        ofPopMatrix();
    }
}

void RawBrainGraphic::addSample(int index, float newSample)
{
//    brainBuffers[index].push_back(newSample);
    brainBuffers[index].insert(brainBuffers[index].begin(), newSample);
    while(brainBuffers[index].size() > maxFloatLen)
    {
        brainBuffers[index].pop_back();
    }
//    brainBuffers.at(index)[currentIndex] = newSample;
//    brainBuffers[index][currentIndex] = newSample;
//    currentIndex++;
}

void RawBrainGraphic::addSamples(float* newSample)
{
    for(int i = 0; i < 16; i++)
    {
        brainBuffers[i].insert(brainBuffers[i].begin(), newSample[i]);
        while(brainBuffers[i].size() > maxFloatLen)
        {
            brainBuffers[i].pop_back();
        }
    }
    //    brainBuffers.at(index)[currentIndex] = newSample;
    //    brainBuffers[index][currentIndex] = newSample;
    //    currentIndex++;
}

void  RawBrainGraphic::setTransform(int index, aiMatrix4x4 t)
{
//    mTransformations[index] = ofMatrix4x4(t.a1,t.a2,t.a3,t.a4,
//                                          t.b1,t.b2,t.b3,t.b4,
//                                          t.c1,t.c2,t.c3,t.c4,
//                                          t.d1,t.d2,t.d3,t.d4);
    mTransformations[index] = ofMatrix4x4(t.a1,t.b1,t.c1,t.d1,
                                          t.a2,t.b2,t.c2,t.d2,
                                          t.a3,t.b3,t.c3,t.d3,
                                          t.a4,t.b4,t.c4,t.d4);
}