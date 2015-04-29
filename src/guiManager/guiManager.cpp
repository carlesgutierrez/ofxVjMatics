//
//  guiManager.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "guiManager.h"

#define GUI_CANVAS_WIDTH (50+OFX_UI_GLOBAL_CANVAS_WIDTH/2)
//----------------------------------------------
// SINGLETON initalizations
bool guiManager::instanceFlag = false;
guiManager* guiManager::single = NULL;


guiManager* guiManager::getInstance(){
    if(! instanceFlag)
    {
        single = new guiManager();
        instanceFlag = true;
        return single;
    }else{
        return single;
    }
}

//--------------------------------------------------------------
void guiManager::setup(){
	
    ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
	
	guiBailongos = NULL;

	receiverOSC.setup(12345);
	cout << "OSC setup" << endl;

	createUtilsGUI();
	createBailongosGUI();
	createParticlesGUI();
	createBoxesGUI();
	
	//set invisible at first
	guiBailongos->toggleVisible();
	guiSound->toggleVisible();
	guiOSC->toggleVisible();
	guiParticles->toggleVisible();
	guiBoxes->toggleVisible();
	
	bOnActionGui = false;
	
	mouseX = mouseY = 0;
	bGuiTouched = false;
	
}

//--------------------------------------------------------------
void guiManager::createUtilsGUI(){
	//In order taking care who ask positions from who
	createOSCGUI();
	createSoundGUI();

}


//--------------------------------------------------------------
void guiManager::update(){
	//OSC GUI interaction... TODO check this
	oscReceivingUpdate();
	
	if(
		guiParticles->isHit(mouseX, mouseY) ||
		guiOSC->isHit(mouseX, mouseY)		||
		guiBailongos->isHit(mouseX, mouseY) ||
		guiSound->isHit(mouseX, mouseY)		||
		guiBoxes->isHit(mouseX, mouseY)
	   )
	{
		bGuiTouched = true;
	}else{
		bGuiTouched = false;
	}
	
	
	//TODO auto update the beat to the GUI SOUND
	/*
	beatDetectedValue = soundManager::getInstance()->beatDetector.getBeatValue();
	
	cout << "beatDetectedValue = " << beatDetectedValue << endl;
	
	if(beatDetectedValue != lastBeatDetectedValue){
		//How to change UI value from outside
		
		 ofxUIWidget * widget2 = guiSound->getWidget("beatDetected");
		 if( widget2->getKind() == OFX_UI_WIDGET_SLIDER_H){
			 ofxUISlider *slider = (ofxUISlider *) widget2;
			 slider->setValue(beatDetectedValue);
		 }
		
		lastBeatDetectedValue = beatDetectedValue;
	}
	 */
}

//--------------------------------------------------------------
void guiManager::draw(){

}
//--------------------------------------------------------------
//TODO internal: ifconfig | perl -ne 'print "$1\n" if /inet addr:([\d.]+)/'
//--------------------------------------------------------------
string guiManager::getPublicIPAddress() {
	string myPublicIP = "";
	FILE* pubIP = popen("curl -s checkip.dyndns.org|sed -e 's/.*Current IP Address: //' -e 's/<.*$//'", "r");  //modes w and r
	char ip[128];
	if (fgets(ip, 128, pubIP) != NULL) {
		//strip the endline character from the end of the string.
		int len = strlen(ip);
		if( ip[len-1] == '\n' ) ip[len-1] = 0;
		myPublicIP.append(ip);
		
		printf("\n PUBLIC IP: '%s' \n", myPublicIP.c_str());
	}
	pclose(pubIP);
	
	return myPublicIP;
}

//--------------------------------------------------------------
bool guiManager::createOSCGUI(){
	posGui = ofVec2f(0, 0);
	guiOSC = new ofxUICanvas(posGui.x, posGui.y, GUI_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
	guiOSC->addLabel("OSC");
	guiOSC->addButton("loadGUItoPhone", false);
	guiOSC->addSpacer();
	//guiOSC->addTextInput("IpToLoadGui", "192.168.1.49");
	guiOSC->addLabel("IpToLoadGui", getIpToLoadGui());
	
	guiOSC->autoSizeToFitWidgets();
	ofAddListener(guiOSC->newGUIEvent,this,&guiManager::guiOSCEvent);
	
	guiOSC->loadSettings("GUI/myLastOSCValues");
}

//--------------------------------------------------------------
bool guiManager::createSoundGUI(){
	posGui = ofVec2f(0, 0);
	guiSound = new ofxUICanvas(posGui.x, posGui.y+guiOSC->getRect()->getHeight(), GUI_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
	guiSound->addLabel("Sound");
	guiSound->addToggle("bSoundActive", false);
	guiSound->addSpacer();
	guiSound->addSlider("beatDetected", 0, 300, 0.0);
	
	guiSound->autoSizeToFitWidgets();
	ofAddListener(guiSound->newGUIEvent,this,&guiManager::guiSoundEvent);
	
	guiSound->loadSettings("GUI/myLastSoundValues");
}

//--------------------------------------------------------------
bool guiManager::createParticlesGUI(){
	posGui = ofVec2f(GUI_CANVAS_WIDTH, 0);
	guiParticles = new ofxUICanvas(posGui.x, posGui.y, GUI_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
	guiParticles->addLabel("Particles");
	guiParticles->addToggle("bParticles", false);
	guiParticles->addSpacer();
	guiParticles->addSlider("numParticles", 0, 1, 0.0);
	guiParticles->addSlider("myParticlesYvalue", -1, 1, 0.0);

	guiParticles->autoSizeToFitWidgets();
	ofAddListener(guiParticles->newGUIEvent,this,&guiManager::guiParticlesEvent);
	
	guiParticles->loadSettings("GUI/myLastParticlesValues");
}

//--------------------------------------------------------------
bool guiManager::createBoxesGUI(){
	posGui = ofVec2f(GUI_CANVAS_WIDTH*2, 0);
	guiBoxes = new ofxUICanvas(posGui.x, posGui.y, GUI_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
	guiBoxes->addLabel("Boxes");
	guiBoxes->addToggle("bBoxes", false);
	guiBoxes->addSlider("numBoxes", 0, 10, 0.0);
	guiBoxes->addToggle("bAnimatedBoxes", false);
	guiBoxes->addSlider("controlXBoxes", -1, 1, 0.0);
	guiBoxes->addSlider("controlYBoxes", -1, 1, 0.0);
	guiBoxes->addSlider("controlZBoxes", -1, 1, 0.0);
	guiBoxes->addSpacer();
	guiBoxes->addToggle("bWireBoxes", false);
	guiBoxes->addSlider("colorHBoxes", 0, 255, 0.0);
	guiBoxes->addSlider("colorSBoxes", 0, 255, 200.0);
	guiBoxes->addSlider("colorVBoxes", 0, 255, 200.0);
	guiBoxes->autoSizeToFitWidgets();
	ofAddListener(guiBoxes->newGUIEvent,this,&guiManager::guiBoxesEvent);
	
	guiBoxes->loadSettings("GUI/myLastBoxesValues");
}

//--------------------------------------------------------------
bool guiManager::createBailongosGUI(){
	
	cout << "Going to create a new Gui" << endl;
	posGui = ofVec2f(GUI_CANVAS_WIDTH*3, 0);
	guiBailongos = new ofxUICanvas(posGui.x, posGui.y, GUI_CANVAS_WIDTH, GUI_CANVAS_WIDTH);

	guiBailongos->addLabel("Bailongos");
	guiBailongos->addToggle("Visible_Bailongos", false);
	guiBailongos->addSpacer();
			
	guiBailongos->addSlider("controX", -1, 1, 0.0);
	guiBailongos->addSlider("controY", -1, 1, 0.0);
	guiBailongos->addSlider("controZ1", 0, 1, 0.0);
	guiBailongos->addSlider("controZ2", 0, 1, 0.0);
	
	guiBailongos->addSpacer();
	
	guiBailongos->addSlider("numObjects", 0, 1, 0.0);
	guiBailongos->addSlider("rangeSeparation", 0, 1, 0.0);
	
	guiBailongos->addSpacer();
	
	//guiBailongos->addLabel("Modify Ip in the reciever");
	//guiBailongos->addLabel("with the following IP");
	//guiBailongos->addLabel(getPublicIPAddress());
	//guiBailongos->addSpacer();

	guiBailongos->autoSizeToFitWidgets();
	ofAddListener(guiBailongos->newGUIEvent,this,&guiManager::guiBailongosEvent);
	
	guiBailongos->loadSettings("GUI/myLastBailongosValues");
	
	cout << "Gui Done" << endl;
}

//--------------------------------------------------------------
void guiManager::keyPressed(ofKeyEventArgs &args){

}

//--------------------------------------------------------------
void guiManager::keyReleased(ofKeyEventArgs &args){
    
    switch(args.key)
    {
		case 'g':
			guiParticles->toggleVisible();
			guiBailongos->toggleVisible();
			guiSound->toggleVisible();
			guiOSC->toggleVisible();
			guiBoxes->toggleVisible();

			//if(guiBailongos->isVisible()) ofShowCursor();
			///else ofHideCursor();
			
			break;
		case 's':

			guiBailongos->saveSettings("GUI/myLastBailongosValues");
			guiSound->saveSettings("GUI/myLastSoundValues");
			guiOSC->saveSettings("GUI/myLastOSCValues");
			guiParticles->saveSettings("GUI/myLastParticlesValues");
			guiBoxes->saveSettings("GUI/myLastBoxesValues");
			cout << "saving all gui params to different Xml" << endl;
			break;
    }
	
	
	//
	if(args.key == 'P'){ //phone GUI added
		
		string messagexml;
		string ipAddress;
		ipAddress =  getIpToLoadGui();
		
		addGuiToPhoneOscSetup(ipAddress);
		
	}

	
}

//--------------------------------------------------------
string guiManager::getIpToLoadGui(){
	
	std::string file = "OSC/mySettings.json";
	string ipgettted = "192.168.1.47"; //default value
	// Now parse the JSON
	bool parsingSuccessful = myJsonOSCSettings.open(file);
	
	if(parsingSuccessful){
		// <-- change to your phone's IP
		ipgettted =myJsonOSCSettings["ipadress2loadGUI"].asString();
		cout << "The IP to load the GUI is: " <<  ipgettted << endl;
	}
	
	return ipgettted;
}


//--------------------------------------------------------
void guiManager::mouseDragged(ofMouseEventArgs &args){

	mouseX = args.x;
	mouseY = args.y;
	
}

//--------------------------------------------------------
void guiManager::mouseMoved(ofMouseEventArgs &args){
	mouseX = args.x;
	mouseY = args.y;
}

//--------------------------------------------------------
void guiManager::mousePressed(ofMouseEventArgs &args){

	mouseX = args.x;
	mouseY = args.y;
	
	//eventInteraction newInteractionEvent;
	//newInteractionEvent.bGuiMouseInteraction = true;
	//ofNotifyEvent(eventInteraction::onInteraction, newInteractionEvent);


}

//--------------------------------------------------------
void guiManager::mouseReleased(ofMouseEventArgs &args){

	
	//eventInteraction newInteractionEvent;
	//newInteractionEvent.bGuiMouseInteraction = false;
	//ofNotifyEvent(eventInteraction::onInteraction, newInteractionEvent);

}

//--------------------------------------------------------
void guiManager::guiOSCEvent(ofxUIEventArgs &e){
/*
	if(e.getName() == "bSoundActive")
	{
		ofxUIToggle *toggle = e.getToggle();
		bSound = toggle->getValue();
		cout << "bSound = " << bSound << endl;
	}
*/
}

//--------------------------------------------------------
void guiManager::guiBoxesEvent(ofxUIEventArgs &e){
	
	if(e.getName() == "bBoxes")
	{
		ofxUIToggle *toggle = e.getToggle();
		bBoxes = toggle->getValue();
		cout << "bBoxes = " << bBoxes << endl;
	}
	else if(e.getName() == "bAnimatedBoxes")
	{
		ofxUIToggle *toggle = e.getToggle();
		bAnimatedBoxes = toggle->getValue();
		cout << "bAnimatedBoxes = " << bAnimatedBoxes << endl;
	}
	else if(e.getName() == "bWireBoxes")
	{
		ofxUIToggle *toggle = e.getToggle();
		bWireBoxes = toggle->getValue();
		cout << "bWireBoxes = " << bWireBoxes << endl;
	}
	else if(e.getName() == "numBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		numBoxes = slider->getScaledValue();
		cout << "numBoxes = " << numBoxes << endl;
	}
	else if(e.getName() == "colorHBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		colorHBoxes = slider->getScaledValue();
		cout << "colorHBoxes = " << colorHBoxes << endl;
	}
	else if(e.getName() == "colorSBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		colorSBoxes = slider->getScaledValue();
		cout << "colorSBoxes = " << colorSBoxes << endl;
	}
	else if(e.getName() == "colorVBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		colorVBoxes = slider->getScaledValue();
		cout << "colorVBoxes = " << colorVBoxes << endl;
	}
	else if(e.getName() == "controlXBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		controlXBoxes = slider->getScaledValue();
		cout << "controlXBoxes = " << controlXBoxes << endl;
	}
	else if(e.getName() == "controlYBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		controlYBoxes = slider->getScaledValue();
		cout << "controlYBoxes = " << controlYBoxes << endl;
	}
	else if(e.getName() == "controlZBoxes")
	{
		ofxUISlider *slider = e.getSlider();
		controlZBoxes = slider->getScaledValue();
		cout << "controlZBoxes = " << controlZBoxes << endl;
	}
	
}

//--------------------------------------------------------
void guiManager::guiParticlesEvent(ofxUIEventArgs &e){

	if(e.getName() == "bParticles")
	{
		ofxUIToggle *toggle = e.getToggle();
		bParticles = toggle->getValue();
		cout << "bParticles = " << bParticles << endl;
	}
	else if(e.getName() == "numParticles")
	{
		ofxUISlider *slider = e.getSlider();
		numParticles = slider->getScaledValue();
		cout << "numParticles = " << numParticles << endl;
	}
	else if(e.getName() == "myParticlesYvalue")
	{
		ofxUISlider *slider = e.getSlider();
		myParticlesYvalue = slider->getScaledValue();
		cout << "myParticlesYvalue = " << myParticlesYvalue << endl;
	}
	
	
}

//--------------------------------------------------------
void guiManager::guiSoundEvent(ofxUIEventArgs &e){
	if(e.getName() == "beatDetected")
	{
		ofxUISlider *slider = e.getSlider();
		beatDetectedValue = (int)slider->getScaledValue();
		cout << "beatDetected = " << beatDetectedValue << endl;
	}
	if(e.getName() == "bSoundActive")
	{
		ofxUIToggle *toggle = e.getToggle();
		bSound = toggle->getValue();
		cout << "bSound = " << bSound << endl;
	}

}

//--------------------------------------------------------
void guiManager::guiBailongosEvent(ofxUIEventArgs &e){
    //string name = e.widget->getName();
	
	if(e.getName() == "Visible_Bailongos")
	{
		ofxUIToggle *toggle = e.getToggle();
		bBailongos = toggle->getValue();
		cout << "bBailongos = " << bBailongos << endl;
	}
	else if(e.getName() == "controX")
	{
		ofxUISlider *slider = e.getSlider();
		myControlXvalue = slider->getScaledValue();
		cout << "myControlXvalue = " << myControlXvalue << endl;
	}
	else if(e.getName() == "controY")
	{
		ofxUISlider *slider = e.getSlider();
		myControlYvalue = slider->getScaledValue();
		cout << "myControlYvalue = " << myControlYvalue << endl;
	}
	else if	(e.getName() == "controZ1")
	{
		ofxUISlider *slider = e.getSlider();
		myControlZ1value = slider->getScaledValue();
		cout << "myControlZ1value = " << myControlZ1value << endl;
	}
	else if	(e.getName() == "controZ2")
	{
		ofxUISlider *slider = e.getSlider();
		myControlZ2value = slider->getScaledValue();
		cout << "myControlZ2value = " << myControlZ2value << endl;
	}
	
	//How to change UI value from outside
	/*
	ofxUIWidget * widget2 = guiBailongos->getWidget("controY");
	if( widget2->getKind() == OFX_UI_WIDGET_SLIDER_H){
		ofxUISlider *slider = (ofxUISlider *) widget2;
		slider->setValue(myControlXvalue);
		cout << "OFX_UI_WIDGET_SLIDER_H" << endl;
	}*/
	
	//else if(e.getName() == "FULLSCREEN")
	//{
	//	ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
	//	ofSetFullscreen(toggle->getValue());
	//}
}


//--------------------------------------------------------------
void guiManager::addGuiToPhoneOscSetup(string ipPhone){
	
	// create an interface
	
	controlOsc.setup("MyApoloControlOSC_15Abril", PORTRAIT);
	Page* page = controlOsc.addPage("page1");
	
	
	ofxControlOSCSlider *slider1 = page->addSlider("BCtrX", 0.5, 0.1, 0.4, 0.1);
	slider1->setAddress("/BCtrX");
	slider1->setMin(-1);
	slider1->setMax(1);

	ofxControlOSCSlider *slider2 = page->addSlider("BCtrY", 0.5, 0.2, 0.4, 0.1);
	slider2->setAddress("/BCtrY");
	slider2->setMin(-1);
	slider2->setMax(1);

	ofxControlOSCSlider *slider3 = page->addSlider("BAngZ1", 0.5, 0.3, 0.4, 0.1);
	slider3->setAddress("/BAngZ1");
	slider3->setMin(0);
	slider3->setMax(1);

	ofxControlOSCSlider *slider4 = page->addSlider("BAngZ2", 0.5, 0.4, 0.4, 0.1);
	slider4->setAddress("/BAngZ2");
	slider4->setMin(0);
	slider4->setMax(1);

	
	page->addToggle("Bailongos", 0.05, 0.1, 0.2, 0.1);
	page->addToggle("Particles", 0.05, 0.2, 0.2, 0.1);
	
	//page->addMultiButton("myMultiButton", 0.05, 0.6, 0.25, 0.25, 1, 5); // TODO is not accepting this matrix
	
	string json = controlOsc.getJson();
	
	cout << json << endl;
	
	// The string json contains the interface. There are two ways to
	// get it onto your device. The manual way is to save it to a file
	// and upload it to a webserver, from which you can retrieve it
	// inside the ControlOSC application.
	// Save it using controlOsc.save(PATH_TO_YOUR_FILE) or output
	// the json string manually using controlOsc.getJson()
	
	
	// The second way is to push the json directly to your phone over OSC.
	// Make sure your android device is connected to the same network as your
	// computer before running, and make sure ControlOSC is open.
	// Set myPhoneIpAddress to the network address of your device.
	// This feature is unstable however, as it causes ControlOSC
	// to crash sometimes depending on the features added. So if it doesn't
	// work, you should use the above manual way
	
	string ipAddress = ipPhone;    // <-- change to your phone's IP
	ofxOscSender osc;
	ofxOscMessage m;
	m.setAddress("/pushInterface");
	m.addStringArg(json);
	osc.setup(ipAddress, 8080);     // port must always be 8080
	osc.sendMessage(m);
	
}


//--------------------------------------------------------------
void guiManager::oscReceivingUpdate(){
	
	// check for waiting messages
	while(receiverOSC.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiverOSC.getNextMessage(&m);
		
		cout << "m.getAddress() =  " << m.getAddress() << endl;
		
		// check for mouse button message
		if(m.getAddress() == "/page1/myButton"){
			// the single argument is a string
			if(m.getArgAsInt32(0) < 0){
				//bDoRamdomPos = (bool)0; // -1 a  1
			}else {
				//bDoRamdomPos = (bool)1; // -1 a  1
			}
		}
		
		if(m.getAddress() == "/bailongo_controlX"){
			// the single argument is a string
			float auxFloatValue = m.getArgAsFloat(0);
			cout << "get osc value received " << auxFloatValue << endl;
			
			//How to change UI value from outside
			 ofxUIWidget * widget2 = guiBailongos->getWidget("controX");
			 if( widget2->getKind() == OFX_UI_WIDGET_SLIDER_H){
				 ofxUISlider *slider = (ofxUISlider *) widget2;
				 slider->setValue(auxFloatValue);
			 }else{
				 myControlXvalue = auxFloatValue;
			 }
		}else if(m.getAddress() == "/bailongo_controlY"){
				// the single argument is a string
				float auxFloatValue = m.getArgAsFloat(0);
				cout << "get osc value received " << auxFloatValue << endl;
				
				//How to change UI value from outside
			 ofxUIWidget * widget2 = guiBailongos->getWidget("controY");
			 if( widget2->getKind() == OFX_UI_WIDGET_SLIDER_H){
				 ofxUISlider *slider = (ofxUISlider *) widget2;
				 slider->setValue(auxFloatValue);
			 }
			 else{
				myControlYvalue = auxFloatValue;
			 }
			
		}
		else if(m.getAddress() == "/bailongo_controlZ1"){
			// the single argument is a string
			float auxFloatValue = m.getArgAsFloat(0);
			cout << "get osc value received " << auxFloatValue << endl;
			
			//How to change UI value from outside
			ofxUIWidget * widget2 = guiBailongos->getWidget("controZ1");
			if( widget2->getKind() == OFX_UI_WIDGET_SLIDER_H){
				ofxUISlider *slider = (ofxUISlider *) widget2;
				slider->setValue(auxFloatValue);
			}
			else{
				myControlZ1value = auxFloatValue;
			}
		}
	}
}
