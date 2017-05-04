//
//  TriangleMotion.cpp
//  brainThots
//
//  Created by Ben Van Citters on 5/3/17.
//
//

#include "TriangleMotion.h"

void TriangleMotion::update(float dt, TriangleMask& mask)
{
    localTime += dt;
    
    extrusionRotation += (extrusionAmt/20.f)*dt;
    
    size = mask.size.get();
    zRotSpeed = mask.zRotSpeed.get();
    extrusionOffset = mask.extrusionOffset.get();
    extrusionAmt = mask.extrusionAmt.get();
    count = (int)mask.count.get();
    
    zRotation += zRotSpeed*dt;
}

void TriangleMotion::draw()
{
    int partitionCount = count;
    ofVec3f modifiers(sin(2+localTime*.2),sin(1+localTime*.13),sin(7+localTime*.07));
    
    float maxSize = 1000*size;
    ofPushMatrix();
    
    ofRotateZ(zRotation);
    
    //the only reason to crate these shapes dynamically is so they can be changed...
    for(int i = 0; i < partitionCount; i++)
    {
        float pct = i*1.f/partitionCount;
        
        ofMesh m;
        m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        float outerRadius = maxSize*(1-pct);
        float innerRadius = maxSize*(1-(i+1.f)/partitionCount);
        for(int j = 0; j <= 3; j++)
        {
            float radian = j*TWO_PI/3.f;
            ofVec3f pos(cos(radian),sin(radian),0);
            
            m.addVertex(outerRadius*pos);
            m.addVertex(innerRadius*pos);
        }
        
        
        
        float osc = pct*8*sin(5+extrusionRotation*10);
        ofPushMatrix();
        ofRotateX(modifiers.x*extrusionOffset*(pct+osc));
        ofRotateY(modifiers.y*extrusionOffset*(pct+osc));
        ofRotateZ(modifiers.z*extrusionOffset*(pct+osc));
        m.draw();
        ofPopMatrix();
    }
    
    ofPopMatrix();
}