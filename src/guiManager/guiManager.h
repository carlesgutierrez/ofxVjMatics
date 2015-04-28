//
//  guiManager.h
//
//
//  Created by Carles
//
//

#pragma once

//#include "eventObjectScenario.h"

#include "ofxUI.h"
#include "ofxOsc.h"
#include "ofxControlOSC.h"
#include "ofxJSON.h"
#include "soundManager.h"
#include "ofxXmlSettings.h"
#include "eventInteraction.h"

class guiManager {
	
	// variables & methods for singleton
private:
    static bool	instanceFlag;
    static guiManager *single;
	
public:
	static guiManager* getInstance();
	// end singleton
	
public:
	void setup();
	void update();
	void draw();

	//osc
	void oscReceivingUpdate();
	void addGuiToPhoneOscSetup(string ipPhone);

	ofxOscReceiver receiverOSC; //Wierd order (receiverOSC before controlOsc) is necesary to do not provoque AsynchronousBreak()
	
	ofxControlOSC controlOsc;
	ofxJSONElement myJsonOSCSettings;


    //ofApp events
	void keyReleased(ofKeyEventArgs &args);
	void keyPressed(ofKeyEventArgs &args);
	void mouseDragged(ofMouseEventArgs &args);
    void mouseMoved(ofMouseEventArgs &args);
    void mousePressed(ofMouseEventArgs &args);
    void mouseReleased(ofMouseEventArgs &args);
	
	//get your external IP ... TOdo > Get internal ip.
	string getPublicIPAddress();
	string getIpToLoadGui();
	
    /* GUI stuff */
	void createUtilsGUI();
	
	bool createBailongosGUI();
	ofxUICanvas *guiBailongos;
	
	bool createSoundGUI();
	ofxUICanvas *guiSound;
	
	bool createParticlesGUI();
	ofxUICanvas *guiParticles;
	
	bool createOSCGUI();
	ofxUICanvas *guiOSC;

	
	ofVec2f posGui;
	
	void guiParticlesEvent(ofxUIEventArgs &e);
	void guiBailongosEvent(ofxUIEventArgs &e);
	void guiSoundEvent(ofxUIEventArgs &e);
	void guiOSCEvent(ofxUIEventArgs &e); // TODO this is not allowing to use Text Intup? raro raro
	
	ofColor backgroundColor;
	
	//control bailongos
	bool bBailongos;
	float myControlXvalue, myControlYvalue, myControlZ1value, myControlZ2value;
	
	//control sound
	bool bSound;
	int beatDetectedValue, lastBeatDetectedValue;
	
	//control particles
	bool bParticles;
	float numParticles;
};