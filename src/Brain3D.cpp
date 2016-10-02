//
//  Brain3D.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/25/16.
//
//

#include "Brain3D.h"


Brain3D::Brain3D()
{
    model.loadModel("models/decimatex2.dae", false);
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
}

void Brain3D::draw()
{
    ofMesh mesh = model.getCurrentAnimatedMesh(0);
    
    for(int i = 0; i < 5; i++)
    {
        
    for(int j = 0; j < 5; j++)
        {
    ofPushMatrix();
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(-ofGetMouseX(), 0, 1, 0);
    ofTranslate(-model.getPosition().x + 150*i, -model.getPosition().y + 150*j, 0);
            ofScale(ofPoint(.3,.3,.3));
    model.drawFaces();
    ofPopMatrix();
        }
}

}


void Brain3D::update()
{
    model.update();

}