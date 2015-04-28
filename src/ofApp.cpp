#include "ofApp.h"


#include "ofxPublishScreen.h"

ofxPublishScreen::FboPublisher myPublishScreen;

//--------------------------------------------------------------
void ofApp::setup(){
   
	ofSetFrameRate(30);
    ofBackground(0, 255, 0);

	
	//Load oll examples
	myRandomVideosPlayers.setup();
	myAnimatedBoxes.setup();
	myParticles.setup();
	
	
	guiManager::getInstance()->setup();
	
#ifdef USE_SYPHON
	mainOutputSyphonServer.setName("OF_syphon"); // 1syphon
#endif
	
	
#ifdef USE_MTL_MAPPING
	_mapping = new ofxMtlMapping2D();
	_mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
#endif
	
	
#ifdef USE_PUBLISHSCREEN
	myPublishScreen.setup(20000, ofGetWidth(), ofGetHeight());
#endif
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
    #ifdef USE_MTL_MAPPING
	_mapping->update();
	#endif
	
	if(guiManager::getInstance()->bBailongos)myRandomVideosPlayers.update(modeLocation,0,spaceVideos, false);
	
	if(guiManager::getInstance()->bParticles)myParticles.update();
	
	myAnimatedBoxes.update();
	
	
	switch (myModeVisual) {
		case videosInLineArea:
			myRandomVideosPlayers.update(modeLocation,0,spaceVideos, false);
			break;
		case ribbonsArea:
			//waiting to edit this mode
			break;
		case particlesArea:
			myParticles.update();
			break;
		default:
			cout << "No myModeVisual right selected" << endl;
	}
	
#ifdef USE_PUBLISHSCREEN
	myPublishScreen.begin();
	drawVisuals();
	myPublishScreen.end();
#endif
	
	guiManager::getInstance()->update(); // udpate receiving OSC data frmom mobiles
	
	
}

//--------------------------------------------------------------
void ofApp::drawVisuals(){
	
	
	myAnimatedBoxes.draw();
	
	if(guiManager::getInstance()->bBailongos)myRandomVideosPlayers.draw();
	if(guiManager::getInstance()->bParticles)myParticles.draw();
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetWindowTitle("ApoloMatics - FrameRate = "+ ofToString(ofGetFrameRate(), 2));
	
	// ----
	#ifdef USE_MTL_MAPPING
	_mapping->bind();
	#endif


#ifdef USE_PUBLISHSCREEN
	ofSetColor(ofColor::white);
	myPublishScreen.draw();
#else
	drawVisuals();
#endif

	
	#ifdef USE_MTL_MAPPING
	_mapping->unbind();
    
    //-------- mapping of the towers/shapes
    _mapping->draw();
	#endif
	

	#ifdef USE_SYPHON
	mainOutputSyphonServer.publishScreen();
	#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	if(key == '8'){
		myModeVisual = videosInLineArea;
	}
	else if(key == '9'){
		myModeVisual = particlesArea;
	}
	else if(key == '0'){
		myModeVisual = ribbonsArea;
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//myRandomVideosPlayers.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//myRandomVideosPlayers.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	//myRandomVideosPlayers.mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels)
{
	//soundManager::getInstance()->audioReceived( input , bufferSize, nChannels ) ;
}


				  
