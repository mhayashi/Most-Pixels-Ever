#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
	lastFrameTime = ofGetElapsedTimef();
	
    // initialize app
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
	client.setup("settings.xml", true);
    
    // set the random seed
	ofSeedRandom(1);
    
    // add a "randomly" placed ball
    Ball* ball = new Ball(ofRandom(0, client.getMWidth()), ofRandom(0, client.getMHeight()), client.getMWidth(), client.getMHeight());
    balls.push_back(ball);
    
	// start client
    client.start();
    
    
	ofxMPERegisterEvents(this);
	
	ofSetBackgroundAuto(false);    
}

//--------------------------------------------------------------
void testApp::update() {	
}

//--------------------------------------------------------------
void testApp::draw() {
}

//--------------------------------------------------------------
void testApp::mpeFrameEvent(ofxMPEEventArgs& event) {
	//ofClear(0, 0, 0, 0);
    client.placeScreen();
	
    cout << event.message << endl;
    vector<string> xy = ofSplitString(event.message, ",", true);
    
    if (!xy.empty()) {
        float x = ofToInt(xy[0]);
        float y = ofToInt(xy[1]);
        Ball* ball = new Ball(x, y, client.getMWidth(), client.getMHeight());
        balls.push_back(ball);
    }
    
    // move and draw all the balls
    for (int i = 0; i < balls.size(); i++) {
        balls[i]->calc();
        balls[i]->draw();
    }
		
	/*
     float now = ofGetElapsedTimef();
     cout << "fps would be " << 1./(now - lastFrameTime) << endl;
     lastFrameTime = now;
     */
}

//--------------------------------------------------------------
void testApp::mpeMessageEvent(ofxMPEEventArgs& event){
	//received a message from the server
}


void testApp::mpeResetEvent(ofxMPEEventArgs& event){
	//triggered if the server goes down, another client goes offline, or a reset was manually triggered in the server code
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    // never include a ":" when broadcasting your message
    x += client.getXoffset();
    y += client.getYoffset();
    client.broadcast(ofToString(x) + "," + ofToString(y));
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    cout << msg.message << endl;
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
