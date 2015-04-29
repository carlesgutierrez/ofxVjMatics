#include "animatedBox.h"

//------------------------------------------------------------------
animatedBox::animatedBox(){
	
	float width = ofGetWidth() * .12;
	
	box.set( width*1.5); //
	
	cout << "animatedBox constructuor" << endl;

}
//------------------------------------------------------------------
animatedBox::~animatedBox(){
	
cout << "animatedBox destructuor" << endl;
	
}
//------------------------------------------------------------------
animatedBox::animatedBox(float _width){
	
	//float width = ofGetWidth() * .12;
	
	box.set( _width ); //
	cout << "animatedBox destructuor with parameters" << endl;
}

//------------------------------------------------------------------
void animatedBox::update(ofVec2f _auxTween){
	
	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);
	float spinZ = cos(ofGetElapsedTimef()*.09f);
	
	box.rotate(spinX, 1.0, 0.0, 0.0);
	box.rotate(spinY, 0, 1.0, 0.0);
	
	if(guiManager::getInstance()->bAnimatedBoxes){
		box.move(0.0, 0.0, _auxTween.x);
	}
	//else{
	//	box.move(0.0, 0.0, spinZ);
	//}
}

//------------------------------------------------------------------
void animatedBox::setPosition(ofVec3f _pos){

	box.setPosition(_pos);
}

//------------------------------------------------------------------
void animatedBox::draw(){

	box.draw();

}

