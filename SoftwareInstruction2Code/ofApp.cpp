#include "ofApp.h"
ofImage screenshottedImage;

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetBackgroundAuto(false);
	//screen size
	window_width = 1000;
	window_height = 1000;
	ofSetWindowShape(window_width, window_height);
	
	//gui stuff
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	gui.add(lineColor.set("Line Color", ofColor(0, 0, 255), ofColor(0), ofColor(255)));
	//gui.add(lineThickness.set("Line Thickness", 1, 1, 20));
	gui.add(numberOfPoints.set("number of points", 600, 100, 1000));
	gui.add(backGroundColor.set("Background Color", ofColor(0, 0, 0), ofColor(0), ofColor(255)));
	gui.add(timeToChangePoints.set("Toggle Points", false));
	gui.add(variation1.set("Variation 1", true));
	gui.add(variation2.set("Variation 2", false));
	gui.add(variation3.set("Variation 3", false));
	gui.add(screenShot.set("Screenshot"));

	//point stuff
	origin = ofVec2f(window_width, window_height);
	for (int i = 0; i < numberOfPoints; i++) {
		int randomX = ofRandom(0, window_width);
		int randomY = ofRandom(0, window_height);
		points.push_back(new ofVec2f(randomX, randomY));
	}
	currentNumberOfPoints = numberOfPoints;
}

//--------------------------------------------------------------
void ofApp::update(){
	if ((window_width != ofGetWidth()) || (window_height != ofGetHeight()) || (currentNumberOfPoints != numberOfPoints)) {
		points.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		currentNumberOfPoints = numberOfPoints;
		for (int i = 0; i < numberOfPoints; i++) {
			int randomX = ofRandom(0, window_width);
			int randomY = ofRandom(0, window_height);
			points.push_back(new ofVec2f(randomX, randomY));
		}
	}
	if (timeToChangePoints) {
		timeToChangePoints.set("Toggle Points", false);
		points.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		for (int i = 0; i < numberOfPoints; i++) {
			int randomX = ofRandom(0, window_width);
			int randomY = ofRandom(0, window_height);
			points.push_back(new ofVec2f(randomX, randomY));
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(backGroundColor);
	
	if (isDrawingGui) {
		gui.draw();
	}
	ofSetColor(lineColor);
	for (vector<ofVec2f*>::iterator itr = points.begin(); itr != points.end(); ++itr) {
		//ofSetLineWidth(lineThickness);
		ofDrawLine((**itr), origin);
	}
	if (variation1) {
		variation2.set("Variation 2", false);
		variation3.set("Variation 3", false);
	}
	else if (variation2) {
		variation1.set("Variation 1", false);
		variation3.set("Variation 3", false);
		ofSetCircleResolution(3);
		ofSetColor(backGroundColor);
		ofDrawCircle(origin, 200);
	}
	else if (variation3) {
		variation1.set("Variation 1", false);
		variation2.set("Variation 2", false);
		ofSetCircleResolution(4);
		ofSetColor(backGroundColor);
		ofDrawCircle(origin, 200);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'x') {
		isDrawingGui = !isDrawingGui;
	}
	else if (key == 's') {
		screenshottedImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshottedImage.save(screenShot.toString() + ".png");
		screenShot.set("Screenshot Saved!");
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	origin = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
