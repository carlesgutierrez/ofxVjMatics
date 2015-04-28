#pragma once
#include "ofMain.h"


class animatedBox{

	public:
		animatedBox();//TODO this is doing crash at new declarations. I guess Shallow copy not implemted and issues arround but not shure..
		animatedBox(float w);
		~animatedBox();
	
		void update();
		void draw();		
		
		ofVec3f pos= ofVec3f(0,0,0);
		void setPosition(ofVec3f _pos);
		ofVec3f vectMov = ofVec3f(0,0,1);

		ofBoxPrimitive box;
};