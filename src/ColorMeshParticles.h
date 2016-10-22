//
//  ColorMeshParticles.h
//  brainThots
//
//  Created by Ben Van Citters on 8/24/16.
//
//

#ifndef ColorMeshParticles_h
#define ColorMeshParticles_h

#include <stdio.h>
#include "ofMain.h"

struct ColorMeshParticle
{
    ofVec3f pos;
    ofVec3f vel;
    float maxSpeed;
};

class ColorMeshParticles
{
public:
    ColorMeshParticles();
    void update(float dt);
    void draw();
    inline void setTargetVector(ofVec3f targ){targetVector = targ;}
    
    ofColor color;
    ofVec2f currentScreenSz;

    float strokeWeight = 0;
private:
    float lastWeight;
    vector<ColorMeshParticle> particles;
    ofVec3f targetVector;
};

#endif /* ColorMeshParticles_h */
