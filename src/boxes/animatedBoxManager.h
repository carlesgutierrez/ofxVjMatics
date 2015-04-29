#pragma once

#include "ofMain.h"
#include "animatedBox.h"
#include "guiManager.h"
#include "ofxTween.h"

class animatedBoxManager{
	
	public:
	
	animatedBoxManager();
	~animatedBoxManager();
	
	void setup();
	void update();
	void draw();

	void keyReleased(ofKeyEventArgs &args);
	void keyPressed(ofKeyEventArgs &args);
	void mouseDragged(ofMouseEventArgs &args);
	void mouseMoved(ofMouseEventArgs &args);
	void mousePressed(ofMouseEventArgs &args);
	void mouseReleased(ofMouseEventArgs &args);
	ofVec2f tweenAnimationValue();
	
	vector <animatedBox> animatedBoxes;
	
	
	//Twweeens
	ofVec2f posAnimation;
	ofxEasingCubic easeCubic;
	float clamp;
	ofxTween::ofxEasingType easingType;
	string easestring;
	int last_elapsedTimeMillis, elapsedTimeMillis;
	
};
