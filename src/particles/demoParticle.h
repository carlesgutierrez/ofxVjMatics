#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

class demoParticle{

	public:
		demoParticle();
		~demoParticle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <ofVec2f> * attract );

		void reset();
		void update();
		void draw();		
		
		ofVec2f pos;
		ofVec2f vel;
		ofVec2f frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		particleMode mode;
		
		vector <ofVec2f> * attractPoints;
	
	
	// forum try: http://forum.openframeworks.cc/t/automatically-moving-particles/19273/1
	
	int random_one_neu;
	int random_one;
	int random_two_neu;
	int random_two;
};