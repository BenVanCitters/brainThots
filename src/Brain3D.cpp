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
    model.loadModel("/Users/admin/Downloads/brainz/source-3/decimatex2.dae", false);
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
}

void Brain3D::draw()
{
    ofMesh mesh = model.getCurrentAnimatedMesh(0);
    ofPushMatrix();
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(-ofGetMouseX(), 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    model.drawFaces();
    ofPopMatrix();
    
}


void Brain3D::update()
{
    model.update();

}