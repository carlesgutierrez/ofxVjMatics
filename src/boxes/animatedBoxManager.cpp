#include "animatedBoxManager.h"


//--------------------------------------------------------------
animatedBoxManager::animatedBoxManager(){

	clamp = false;
	easingType = ofxTween::easeInOut;
	easestring = "ease in/out";
	
	last_elapsedTimeMillis = last_elapsedTimeMillis = 0;

}

//--------------------------------------------------------------
animatedBoxManager::~animatedBoxManager(){
	//TODO> Check if this is ok..
	// We need to deallocate our buffer
/*
	for(int i=0; i < animatedBoxes.size(); i++){
		delete[] animatedBoxes[i];
		animatedBoxes[i] = NULL;
	}
*/
}


//--------------------------------------------------------------
void animatedBoxManager::setup(){
	
	int numBoxes = 5;
	
	//animatedBoxes.reserve(num);

	
	animatedBox box3dApolo;
	
	cout << "animatedBoxes.size() = " << animatedBoxes.size() << endl;
	
	for(int i = 0; i < numBoxes; i++){
		
		animatedBoxes.push_back(box3dApolo);
		ofVec3f newPosition = ofVec3f(i*box3dApolo.box.getWidth()+100,ofGetHeight()*0.25,0); //TODO hack less 
		animatedBoxes[i].setPosition(newPosition);
		cout << "animatedBoxes.vectMov.z" << animatedBoxes[i].vectMov.z << endl;
	}
	
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
}

//--------------------------------------------------------------
ofVec2f animatedBoxManager::tweenAnimationValue(){
	//tweens animations
	int elapsedTime = ofGetElapsedTimef();
	elapsedTimeMillis = ofGetElapsedTimeMillis();
	
	//tweens animations
	posAnimation.x = ofxTween::map(elapsedTimeMillis - last_elapsedTimeMillis, 0, 5000, 0, 1, clamp, easeCubic, easingType);
	posAnimation.y = guiManager::getInstance()->controlYBoxes*ofGetWidth();
	
	if(elapsedTime == 5){
		last_elapsedTimeMillis = elapsedTimeMillis;
	}
	
	return ofVec2f(posAnimation);
}

//--------------------------------------------------------------
void animatedBoxManager::update(){
	
	ofVec2f auxTween = tweenAnimationValue();

	//
	for(int i = 0; i < animatedBoxes.size(); i++){
		animatedBoxes[i].update(auxTween);
	}
	

}

//--------------------------------------------------------------
void animatedBoxManager::draw(){
	
	if(guiManager::getInstance()->bBoxes){
	
		//POSITION
		ofPushMatrix();
		ofVec2f newTranslatePos = ofVec2f(guiManager::getInstance()->controlXBoxes*ofGetWidth(), guiManager::getInstance()->controlYBoxes*ofGetHeight());
		ofTranslate(newTranslatePos);
		
		for(unsigned int i = 0; i < animatedBoxes.size(); i++){
			ofSetColor(ofColor::fromHsb(
						guiManager::getInstance()->colorHBoxes,
						guiManager::getInstance()->colorSBoxes,
						guiManager::getInstance()->colorVBoxes));
			

			
			animatedBoxes[i].draw();
			
			//ofSetColor(ofColor::white);
			//animatedBoxes[i].box.drawAxes(animatedBoxes[i].box.getWidth()+30);
			//ofSetColor(ofColor::red);
			//animatedBoxes[i].box.drawNormals(20, true);
			
			if(guiManager::getInstance()->bWireBoxes){
				ofSetColor(ofColor::black);
				animatedBoxes[i].box.drawWireframe();
			}
			
		}
		
		ofTranslate(newTranslatePos*-1);
		ofPopMatrix();
	}
	
}

//--------------------------------------------------------------
void animatedBoxManager::keyPressed(ofKeyEventArgs &args){

	if( args.key == ' ' ){
		
	}
}

//--------------------------------------------------------------
void animatedBoxManager::keyReleased(ofKeyEventArgs &args){

}

//--------------------------------------------------------------
void animatedBoxManager::mouseMoved(ofMouseEventArgs &args){

}

//--------------------------------------------------------------
void animatedBoxManager::mouseDragged(ofMouseEventArgs &args){

}

//--------------------------------------------------------------
void animatedBoxManager::mousePressed(ofMouseEventArgs &args){

}

//--------------------------------------------------------------
void animatedBoxManager::mouseReleased(ofMouseEventArgs &args){

}