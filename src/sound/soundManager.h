#pragma once

#include "ofMain.h"
#include "ofxBeatDetector.h"
#include "guiManager.h"

class soundManager{

	// variables & methods for singleton
private:
	static bool	instanceFlag;
	static soundManager *single;
	
public:
	static soundManager* getInstance();
	// end singleton
	
	public:
		void setup();
		void update();
		void draw();
	
		void audioReceived(float* input, int bufferSize, int nChannels);
	
		ofxBeatDetector      beatDetector ;
	
};
