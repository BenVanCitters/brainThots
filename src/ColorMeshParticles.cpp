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
    int particleCount = 100;
    float radSpacing = TWO_PI/particleCount;
    for(int i = 0; i < particleCount; i++)
    {
        ColorMeshParticle p;
        p.vel = ofVec3f();
        p.pos = ofVec3f(cosf(radSpacing*i),sinf(radSpacing*i),0);
        p.maxSpeed = ofRandom(55)+60;
        particles.push_back(p);
    }
}


void ColorMeshParticles::draw()
{
    ofSetHexColor(0x0cb0b6);
    ofFill();
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofBeginShape();
    for(int i = 0; i < particles.size(); i++)
    {
//        ofDrawEllipse(particles[i].pos.x, particles[i].pos.y, 5, 5);
        ofVertex( particles[i].pos);
    }
    ofEndShape();
}

void ColorMeshParticles::update()
{
    float maxDist = ofDist(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    float repulseAmt = .000001;
    for(int i = 0; i < particles.size(); i++)
    {
        ColorMeshParticle* thisPart = &particles[i];
        
        for(int j = 0; j < particles.size(); j++)
        {
            if(j!= i)
            {
                ColorMeshParticle* part = &particles[j];
                ofVec3f nextDir = thisPart->pos - part->pos;
                float nextDist = nextDir.length();
                nextDir = nextDir.normalize();
                ofVec3f nextForce = nextDir * .001-nextDist/100000;// / (nextDist/repulseAmt);
                thisPart->vel += nextForce;
            }
        }
//        int nextIndex = (i+1)%particles.size();
//        ColorMeshParticle* nextPart = &particles[nextIndex];
//        ofVec3f nextDir = thisPart->pos - nextPart->pos;
//        float nextDist = nextDir.length();
//        nextDir = nextDir.normalize();
//        ofVec3f nextForce = nextDir / (nextDist/repulseAmt);
//        
//        int prevIndex = (i-1+particles.size())%particles.size();
//        ColorMeshParticle* prevPart = &particles[prevIndex];
//        ofVec3f prevDir = thisPart->pos - prevPart->pos;
//        float prevDist = prevDir.length();
//        prevDir = prevDir.normalize();
//        ofVec3f prevForce = prevDir / (prevDist/repulseAmt);
        
        ofVec3f targDir = targetVector-thisPart->pos;
        float targDist = targDir.length();
        float newDist = targDist/maxDist;
        targDir = targDir.normalize();
        
        ofVec3f targForce = targDir* thisPart->maxSpeed * sqrt( newDist);
//        thisPart->pos.interpolate(targetVector,.2); //targDir/(targDist/50);
        
        thisPart->vel += targForce;// + nextForce + prevForce;
    }
    
    for(int i = 0; i < particles.size(); i++)
    {
        ColorMeshParticle* thisPart = &particles[i];
        thisPart->pos = thisPart->pos + thisPart->vel;
    }

}