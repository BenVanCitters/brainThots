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
    int particleCount = 20;
    float radSpacing = TWO_PI/particleCount;
    ofVec3f mid(500,500);//ofGetWindowWidth()/2.f,ofGetWindowHeight()/2.f);
    for(int i = 0; i < particleCount; i++)
    {
        ColorMeshParticle p;
        p.vel = ofVec3f();
        p.pos = ofVec3f(cosf(radSpacing*i),sinf(radSpacing*i),ofRandom(40)-20);
        p.pos *= 60;
        p.pos += mid;
        p.maxSpeed = ofRandom(3);
        particles.push_back(p);
    }
}


void ColorMeshParticles::draw()
{
    ofSetColor(color);
    ofFill();
//    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
//    ofBeginShape();
    for(int i = 0; i < particles.size(); i++)
    {
        ofVec3f end = particles[i].pos - particles[i].vel;
        ofSetLineWidth(5);
        ofDrawLine(particles[i].pos,end);
//        ofDrawEllipse(particles[i].pos.x, particles[i].pos.y, 5, 5);
//        ofVertex( particles[i].pos);
    }
//    ofEndShape();
}

void ColorMeshParticles::update()
{
    float maxDist = ofDist(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    float repulseAmt = .000001;
    for(int i = 0; i < particles.size(); i++)
    {
        ColorMeshParticle* thisPart = &particles[i];
        ofVec3f partSum;
        for(int j = 0; j < particles.size(); j++)
        {
            if(j!= i)
            {
                ColorMeshParticle* part = &particles[j];
                ofVec3f nextDir = thisPart->pos - part->pos;
                float nextDist = nextDir.length();
                nextDir = nextDir.normalize();
                float multAmt = 5/(powf(nextDist, 2));
                ofVec3f nextForce = nextDir *  multAmt;// (-x+2)^(1/3);// / (nextDist/repulseAmt);
                partSum += nextForce;
            }
        }
        
        thisPart->vel *= .96;
        thisPart->vel += partSum;
        
        ofVec3f targDir = targetVector-thisPart->pos;
        float targDist = targDir.length();
        float newDist = targDist/maxDist;
        targDir = targDir.normalize();
        float scl = 4.f;
        float forceScalar =scl-(1.f/((1/scl)+newDist)); //sqrt(.01*newDist); //pow(MAX(0,(-10+newDist)/10.f),1.f/3.f);
//        float forceScalar = 200/(targDist*targDist);
        ofVec3f targForce = targDir * thisPart->maxSpeed * forceScalar;
//        thisPart->pos.interpolate(targetVector,.2); //targDir/(targDist/50);
        
        thisPart->vel += targForce;// + nextForce + prevForce;
    }
    
    for(int i = 0; i < particles.size(); i++)
    {
        ColorMeshParticle* thisPart = &particles[i];
        thisPart->pos = thisPart->pos + thisPart->vel;
    }
}