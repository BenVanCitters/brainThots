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
    for (vector<vector<float>>::iterator it = brainBuffers.begin() ; it != brainBuffers.end(); ++it)
    {
        cout << "\nvec: ";
        for(int i = 0; i < it->size(); i++)
        {
            cout << it->at(i) << ",";
        }
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