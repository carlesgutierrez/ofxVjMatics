#include "animatedBoxManager.h"


//--------------------------------------------------------------
animatedBoxManager::animatedBoxManager(){


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
		ofVec3f newPosition = ofVec3f(i*box3dApolo.box.getWidth(),ofGetHeight()*0.25,0); //
		animatedBoxes[i].setPosition(newPosition);
		cout << "animatedBoxes.vectMov.z" << animatedBoxes[i].vectMov.z << endl;
	}
	
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
}


//--------------------------------------------------------------
void animatedBoxManager::update(){
	for(int i = 0; i < animatedBoxes.size(); i++){
		animatedBoxes[i].update();
	}
}

//--------------------------------------------------------------
void animatedBoxManager::draw(){
	
	
	for(unsigned int i = 0; i < animatedBoxes.size(); i++){
		ofSetColor(ofColor::lightPink);
		animatedBoxes[i].draw();
		
		ofSetColor(ofColor::white);
		animatedBoxes[i].box.drawAxes(animatedBoxes[i].box.getWidth()+30);
		ofSetColor(ofColor::red);
		animatedBoxes[i].box.drawNormals(20, true);
		ofSetColor(ofColor::black);
		animatedBoxes[i].box.drawWireframe();
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