//
//  InputMask.hpp
//  brainThots
//
//  Created by Ben Van Citters on 10/16/16.
//
//

#ifndef InputMask_h
#define InputMask_h

#include <stdio.h>
#include "LerpedFloat.h"
#include "InputManager.h"
//class to handle tasks associated with grabbing and updating input
class InputMask
{
public:
    InputMask(InputManager* input);
    virtual void update(float dt);
    
protected:
    InputManager* im;
};

class ShaderInputMask : public InputMask
{
    public:
    ShaderInputMask(InputManager* input);
    LerpedFloat blurAmount;
    LerpedFloat shaderVar1;
    LerpedFloat shaderVar2;
    void update(float dt);
};

class Brain3DInputMask : public InputMask
{
public:
    Brain3DInputMask(InputManager* input);
    LerpedFloat brain3DScale;
    LerpedFloat brain3DRotationSpeed;
    void update(float dt);
};

class RBGInputMask : public InputMask
{
public:
    RBGInputMask(InputManager* input);
    LerpedFloat amplitude;
    LerpedFloat lineLength;
    LerpedFloat lineThickness;
    void update(float dt);
};

class FollowerMask : public InputMask
{
public:
    FollowerMask(InputManager* input);
    LerpedFloat speed;
    LerpedFloat size;
    LerpedFloat particleSize;
    void update(float dt);
};

class LightingMask : public InputMask
{
public:
    LightingMask(InputManager* input);
    LerpedFloat speed;
    LerpedFloat ambientLight;
    void update(float dt);
};
#endif /* InputMask_h */
