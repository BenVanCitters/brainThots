//
//  Brain3D.cpp
//  brainThots
//
//  Created by Ben Van Citters on 9/25/16.
//
//

#include "Brain3D.h"

aiMatrix4x4 recusrMult(aiNode* node)
{
    if(node->mParent != NULL)
    {
        return recusrMult(node->mParent) * node->mTransformation;
    }
    return node->mTransformation;
}

Brain3D::Brain3D():rawBrainGraphic(16)
{
    model.loadModel("models/decimatex2.dae", false);
    model.setScaleNormalization(false);
    model.setScale(1.f,1.f,1.f);
//    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    
    //load the eeg node positions...
    const aiScene * t = model.getAssimpScene();
    aiNode* eegParent = t->mRootNode->FindNode("EEGNodes");
    for(int i = 0; i < 16; i++)
    {
        stringstream s;
        s << "eeg" << i;
        string t = s.str();
        aiNode* tNode = eegParent->FindNode( t.c_str() );
        
        
        aiMatrix4x4 trans = tNode->mTransformation;//recusrMult(tNode);//
        
//        while(tNode->mParent != NULL)
//        {
//            tNode = tNode->mParent;
//            trans *= tNode->mTransformation;
//        }
        rawBrainGraphic.setTransform( i, trans );
    }
}



void Brain3D::draw()
{
    ofMesh mesh = model.getCurrentAnimatedMesh(0);
//    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotate(-ofGetMouseX(), 0, 1, 0);
//            ofTranslate(model.getPosition().x, model.getPosition().y, 0);
//            ofRotate(-ofGetMouseX(), 0, 1, 0);
//            ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
//            ofTranslate(150*i, 150*j, 0);
//            ofScale(ofPoint(.3,.3,.3));
            
            rawBrainGraphic.draw();
            model.drawFaces();
            ofPopMatrix();
        }
    }
}

void Brain3D::addSamples(float* samples)
{
    rawBrainGraphic.addSamples(samples);
    rawBrainGraphic.update();
}

void Brain3D::update()
{
    
    model.update();

}