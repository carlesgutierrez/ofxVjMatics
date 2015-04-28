#pragma once

#include "ofMain.h"
#include "demoParticle.h"
#include "guiManager.h"
#include "eventInteraction.h"

class particleManager{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

	//ofApp events
	void keyReleased(ofKeyEventArgs &args);
	void keyPressed(ofKeyEventArgs &args);
	void mouseDragged(ofMouseEventArgs &args);
	void mouseMoved(ofMouseEventArgs &args);
	void mousePressed(ofMouseEventArgs &args);
	void mouseReleased(ofMouseEventArgs &args);
	
	void listenerMovingGUI(eventInteraction & args);
	bool bmouseDisabled;
	
		particleMode currentMode;
		string currentModeStr = "";

		vector <demoParticle> p;
		int numParticles;
		vector <ofVec2f> attractPoints;
		vector <ofVec2f> attractPointsWithMovement;
	
		int numAttractPoints = 1;
		int particlesX = ofGetWidth()-ofGetWidth()*0.35;
		int particlesY = ofGetHeight()-ofGetHeight()*0.35;
	
};
