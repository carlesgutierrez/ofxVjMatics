//
//  eventInteraction
//  apoloMatics
//
//  Created by carles 2015
//
//


#pragma once

#include "ofMain.h"

class eventInteraction : public ofEventArgs {
public:
	
	eventInteraction();
	
	bool	bGuiMouseInteraction;
	bool	bInteractionRandomButton;
	
    static ofEvent <eventInteraction> onInteraction;
};
