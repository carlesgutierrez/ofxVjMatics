#pragma once

#include "ofMain.h"
#include "animatedBox.h"
#include "guiManager.h"

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
	
	vector <animatedBox> animatedBoxes;
	
};
