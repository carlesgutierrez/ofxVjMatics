#include "particleManager.h"

//--------------------------------------------------------------
void particleManager::setup(){
	//ofSetVerticalSync(true);
	//TODO Error by Creating this boxes
	
	
	numParticles = 250;
	
	//try {
	//	p.assign(num, demoParticle());
	//	cout << "demoParticle created" << endl;
	//}
	//catch(std::bad_alloc&) {
	//	cout << "ERROR Memoria insuficiente" << endl;
	//}
	for(int i=0 ; i < numParticles ; i++){
		p.push_back(demoParticle());
	}
	
	currentMode = PARTICLE_MODE_NEAREST_POINTS;

	//currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
	
	//Interaction events // in this case from Gui event
	//ofAddListener(eventInteraction::onInteraction ,this, &particleManager::listenerMovingGUI);
	
	bmouseDisabled = false;
	
	resetParticles();
}

//--------------------------------------------------------------
void particleManager::resetParticles(){

	//these are the attraction points used in the forth demo 
	attractPoints.clear();
	for(int i = 0; i < 1; i++){//numAttractPoints = 1
		attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofGetHeight()-3, ofGetHeight()-10) ); // TODO Check this Attractors how to play with them better. For now just once is active
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}
	
	//Forum extra movement
	random_one_neu = ofRandom(ofGetWidth());
	random_two_neu = ofRandom(ofGetHeight());
	random_one = random_one_neu;
	random_two = random_two_neu;
}

//--------------------------------------------------------------
void particleManager::update(){
	
	//Random attractor order for particles
	ofPoint neuAttractor = getRandomAttractorParticles();
	
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update(neuAttractor);
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
	

}

//--------------------------------------------------------------
ofPoint particleManager::getRandomAttractorParticles(){
	
	//Forum Try
	int frame_num = ofGetFrameNum();
	int elapsedTime = ofGetElapsedTimef();
	
	
	if(elapsedTime == 5){
		
		random_one_neu = (int)ofRandom(ofGetWidth());
		random_two_neu = guiManager::getInstance()->myParticlesYvalue*ofGetHeight();
		
		//cout << "elapsedTime= " << elapsedTime << " random_one_neu = " << random_one_neu << " random_two_neu = " << random_two_neu << endl;
		ofResetElapsedTimeCounter();
		
		random_one = random_one_neu;
		random_two = random_two_neu;
		
	} else{
		random_one_neu = random_one;
		random_two_neu = random_two;
		//ofPoint attractPt(random_one_neu, random_two_neu);
		//cout << "elapsedTime= " << elapsedTime << " random_one_neu = " << random_one_neu << " random_two_neu = " << random_two_neu << endl;
	}
	
	return ofPoint(random_one_neu, random_two_neu);
}

//--------------------------------------------------------------
void particleManager::draw(){
	
	int numParticlesGUI = guiManager::getInstance()->numParticles*numParticles;
	int numParticlesDIV3 = (int)(numParticles/3);


	for(unsigned int i = 0; i < numParticlesGUI; i++){
		if (i < numParticlesDIV3){
			ofSetColor(ofColor::red);
		}
		else if(i < numParticlesDIV3*2){
			//ofSetColor(ofColor::forestGreen);
			ofSetColor(ofColor::darkBlue);
		}else{
			ofSetColor(ofColor::yellow);
		}
		p[i].draw();
	}
	
	
	
	if(guiManager::getInstance()->guiBailongos->isVisible()){
		ofSetColor(190);
		if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
			for(unsigned int i = 0; i < attractPoints.size(); i++){
				ofNoFill();
				ofCircle(attractPointsWithMovement[i], 10);
				ofFill();
				ofCircle(attractPointsWithMovement[i], 4);
			}
		}
	}

}

//--------------------------------------------------------------
void particleManager::keyPressed(ofKeyEventArgs &args){
	
	if( args.key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 		
	}
	if( args.key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
	}
	if( args.key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force"; 						
	}
	if( args.key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
		resetParticles();
	}	
		
	if( args.key == ' ' ){
		resetParticles();
	}
}

//--------------------------------------------------------------
void particleManager::keyReleased(ofKeyEventArgs &args){

}

//--------------------------------------------------------------
void particleManager::mouseMoved(ofMouseEventArgs &args){
	if(bmouseDisabled){
	}
}

//--------------------------------------------------------------
void particleManager::mouseDragged(ofMouseEventArgs &args){

	//if(bmouseDisabled){
	if(!(guiManager::getInstance()->bGuiTouched)){
		for(int i = 0; i < attractPoints.size(); i++){
			attractPoints[i].x = args.x;
			attractPoints[i].y = args.y;
		}
	}
}

//--------------------------------------------------------------
void particleManager::mousePressed(ofMouseEventArgs &args){
	if(bmouseDisabled){
	}
}

//--------------------------------------------------------------
void particleManager::mouseReleased(ofMouseEventArgs &args){
	if(bmouseDisabled){
	}
}

/*

//------------------------------
//Activat / Deactivate Camera mouse events
void particleManager::listenerMovingGUI(eventInteraction & args){
	
	if(args.bGuiMouseInteraction){
		bmouseDisabled = true;
		cout << "set bmouseDisabled true = " << bmouseDisabled << endl;
	}
	else{
		bmouseDisabled = false;
		cout << "set bmouseDisabled false = " << bmouseDisabled<< endl;
	}
}
*/