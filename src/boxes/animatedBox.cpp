#include "animatedBox.h"

//------------------------------------------------------------------
animatedBox::animatedBox(){
	
	float width = ofGetWidth() * .12;
	
	box.set( width*1.25 ); //
	
	cout << "animatedBox constructuor" << endl;

}
//------------------------------------------------------------------
animatedBox::~animatedBox(){
	
cout << "animatedBox destructuor" << endl;
	
}
//------------------------------------------------------------------
animatedBox::animatedBox(float width){
	
	//float width = ofGetWidth() * .12;
	
	box.set( 1 ); // width*1.25
	cout << "animatedBox destructuor with parameters" << endl;
}

//------------------------------------------------------------------
void animatedBox::update(){
	
	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);
	float spinZ = cos(ofGetElapsedTimef()*.075f);
	
	box.rotate(spinX, 1.0, 0.0, 0.0);
	box.rotate(spinY, 0, 1.0, 0.0);
	
	box.move(0.0, 0.0, spinZ);
	
}

//------------------------------------------------------------------
void animatedBox::setPosition(ofVec3f _pos){

	box.setPosition(_pos);
}

//------------------------------------------------------------------
void animatedBox::draw(){

	box.draw();

}

