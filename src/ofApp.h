#pragma once

#include "ofMain.h"

#include "ExternalsConfig.h"

#ifdef USE_MTL_MAPPING
#include "ofxMtlMapping2D.h"
#endif

#ifdef USE_SYPHON
#include "ofxSyphon.h"
#endif


#include "ofxRandomVideosPlayer.h"

#include "guiManager.h"

#include "eventInteraction.h"

#include "particleManager.h"
#include "animatedBoxManager.h"
#include "soundManager.h"

enum modeVisual {
	videosInLineArea = 0,
	particlesArea,
	ribbonsArea
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void drawVisuals();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	
	//Video VJ PLayer controlled with OSC receiver in 12345 port
	ofxRandomVideosPlayer myRandomVideosPlayers;
	particleManager myParticles;
	
	animatedBoxManager myAnimatedBoxes;
	

	//#endif
	
	//control vars videos
	int modeSelection = 0;
	int modeLocation = 1;
	int spaceVideos = 160;
	bool bDoRamdomPos = false;
	
	modeVisual myModeVisual = videosInLineArea;
	
	//sound control
	void audioReceived(float* input, int bufferSize, int nChannels);
	
	
	////////////////
	//Mapping
#ifdef USE_MTL_MAPPING
	ofxMtlMapping2D* _mapping;
#endif
	
	
	////////////////
	//Share all the OF windows screen directly to Resolume in this laptop
#ifdef USE_SYPHON
	//Syphon
	ofxSyphonServer mainOutputSyphonServer;
#endif

};
