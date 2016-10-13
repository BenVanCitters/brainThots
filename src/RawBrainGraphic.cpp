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
}

void RawBrainGraphic::update()
{
    //cut down the size if they get too long
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
    for (vector<vector<float>>::iterator it = brainBuffers.begin() ; it != brainBuffers.end(); ++it)
    {
//        cout << ' ' << it;
        for(int i = 0; i < it->size(); i++)
        {
            
        }
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

void  RawBrainGraphic::setTransform(int index, aiMatrix4x4 transformation)
{
    mTransformations[index] = transformation;
}