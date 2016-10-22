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

void getTransformsForRBGs()
{
//    //load the eeg node positions...
//    const aiScene * t = model.getAssimpScene();
//    aiNode* eegParent = t->mRootNode->FindNode("EEGNodes");
//    for(int i = 0; i < 16; i++)
//    {
//        stringstream s;
//        s << "eeg" << i;
//        string t = s.str();
//        aiNode* tNode = eegParent->FindNode( t.c_str() );
//        
//        
//        aiMatrix4x4 trans = tNode->mTransformation;//recusrMult(tNode);//
//        
//        //        while(tNode->mParent != NULL)
//        //        {
//        //            tNode = tNode->mParent;
//        //            trans *= tNode->mTransformation;
//        //        }
//        rawBrainGraphic.setTransform( i, trans );
//    }
}

Brain3D::Brain3D()
{
    model.loadModel("models/decimatex2.dae", false);
    model.setScaleNormalization(false);
    model.setScale(1.f,1.f,1.f);
    model.enableColors();
//    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    
//    getTransformsForRBGs();
}

void Brain3D::setScale(float s)
{
    model.setScale(s,s,s);
}

void Brain3D::draw()
{
//    ofMesh me = model.getMesh(0);
////    me.mesh
//    ofMaterial m = model.getMaterialForMesh(0);
//    m.setDiffuseColor(ofFloatColor(ofRandom(255),ofRandom(255),ofRandom(255)));
//    ofMesh mesh = model.getCurrentAnimatedMesh(0);
//    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            ofPushMatrix();
            ofTranslate(currentScreenSz.x/2, currentScreenSz.y/2);
//            ofRotate(-ofGetMouseX(), 0, 1, 0);
//            ofTranslate(model.getPosition().x, model.getPosition().y, 0);
//            ofRotate(-ofGetMouseX(), 0, 1, 0);
//            ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
//            ofTranslate(150*i, 150*j, 0);
//            ofScale(ofPoint(.3,.3,.3));
            ofPushMatrix();
            ofPopMatrix();
            ofRotate(currentRotation, curRot.x, curRot.y, curRot.z);
            ofScale(ofPoint(3,3,3));
            model.drawFaces();
            ofPopMatrix();
        }
    }
}

void Brain3D::addSamples(float* samples)
{
//    rawBrainGraphic.addSamples(samples);
//    rawBrainGraphic.update();
}

void Brain3D::update(float dt, Brain3DInputMask* bim)
{
//    model.update();
    float rotSpd =bim->brain3DRotationSpeed.get();
    brainTime += dt* rotSpd;
    currentRotation = brainTime ;
    setScale(bim->brain3DScale.get());
    
    float lerpTime = ofGetElapsedTimef();
    float lerp = bim->brain3DRotationAxis.get();
    curRot = lerp*ofVec3f(sin(lerpTime*.12+2),
                          sin(lerpTime*.03-2),
                          -sin(lerpTime*0.01)) + (1-lerp)*ofVec3f(0,1,0);
}