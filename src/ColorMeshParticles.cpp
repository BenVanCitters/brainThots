//
//  ColorMeshParticles.cpp
//  brainThots
//
//  Created by Ben Van Citters on 8/24/16.
//
//

#include "ColorMeshParticles.h"

ColorMeshParticles::ColorMeshParticles()
{
    for(int i = 0; i < 100; i++)
    {
        ColorMeshParticle p;
        p.vel = ofVec3f();
        p.pos = ofVec3f();
        p.maxSpeed = 3;
        particles.push_back(p);
    }
}


void ColorMeshParticles::draw()
{
    
}

void ColorMeshParticles::update()
{
    
}