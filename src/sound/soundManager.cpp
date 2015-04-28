#include "soundManager.h"


//----------------------------------------------
// SINGLETON initalizations
bool soundManager::instanceFlag = false;
soundManager* soundManager::single = NULL;


soundManager* soundManager::getInstance(){
	if(! instanceFlag)
	{
		single = new soundManager();
		instanceFlag = true;
		return single;
	}else{
		return single;
	}
}

//--------------------------------------------------------------
void soundManager::setup(){
	beatDetector.enableBeatDetect() ;
	beatDetector.setBeatValue( 160 ) ;
}

//--------------------------------------------------------------
void soundManager::audioReceived(float* input, int bufferSize, int nChannels)
{
	beatDetector.update( input ) ;
}

//--------------------------------------------------------------
void soundManager::update(){
	

	
}

//--------------------------------------------------------------
void soundManager::draw(){

}
