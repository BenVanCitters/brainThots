//
//  ChromaController.h
//  brainThots
//
//  Created by Ben Van Citters on 5/2/17.
//
//

#ifndef ChromaController_h
#define ChromaController_h

#include <stdio.h>
#include "ofMain.h"
#include "InputMask.h"

class ChromaController
{

    double currentTime;
public:
    void update(float dt, ChromaMask* inputMask);
    ofColor currentColor;
};
#endif /* ChromaController_h */
