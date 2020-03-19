#include "ofApp.h"
ofImage screenshottedImage;

//--------------------------------------------------------------
void ofApp::setup(){
	ofNoFill();
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	gui.add(lineColor.set("Line Color", ofColor(255, 0, 0), ofColor(0), ofColor(255)));
	gui.add(lineThickness.set("Line Thickness", 1, 1, 20));
	gui.add(backGroundColor.set("Background Color", ofColor(0, 0, 0), ofColor(0), ofColor(255)));
	gui.add(screenShot.set("Screenshot"));

	//screen size
	window_width = 1000;
	window_height = 1000;
	ofSetWindowShape(window_width, window_height);

	for (int i = 0; i < 100; i++) {
		//int randomRadius = ofRandom(minRadius, maxRadius);
		int randomX = ofRandom(radius, window_width - radius);
		int randomY = ofRandom(radius, window_height - radius);
		circles.push_back(new Circle(randomX, randomY, radius, resolution,window_width,window_height));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if ((window_width != ofGetWidth()) || (window_height != ofGetHeight())) {
		circles.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		for (int i = 0; i < 100; i++) {
			//int randomRadius = ofRandom(minRadius, maxRadius);
			int randomX = ofRandom(radius, window_width - radius);
			int randomY = ofRandom(radius, window_height - radius);
			circles.push_back(new Circle(randomX, randomY, radius, resolution, window_width, window_height));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(backGroundColor);
	//ofBackground(ofColor::blue);
	if (isDrawingGui) {
		gui.draw();
	}
	for (vector<Circle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
		(*itr)->drawCircle(backGroundColor);
		for (vector<Circle*>::iterator itr2 = circles.begin(); itr2 != circles.end(); ++itr2) {
			if (itr != itr2) {
				if (distanceBetweenTwoPoints((*itr)->getX(), (*itr)->getY(), (*itr2)->getX(), (*itr2)->getY()) <= (2* radius) ) {
					//ofBackground(ofColor::white);
					(*itr)->drawSurroundingCircles(lineColor);
				}
			}
		}
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


int ofApp::distanceBetweenTwoPoints(int x, int y, int a, int b) {
	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
