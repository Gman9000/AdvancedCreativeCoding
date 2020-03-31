#include "ofApp.h"
ofImage screenshottedImage;
float northAngle = 0;
float southAngle = 0;
float eastAngle = 0;
float westAngle = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofNoFill();
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	gui.add(lineColor.set("Line Color", ofColor(255, 0, 0), ofColor(0), ofColor(255)));
	gui.add(lineThickness.set("Line Thickness", 1, 1, 20));
	gui.add(backGroundColor.set("Background Color", ofColor(0, 0, 0), ofColor(0), ofColor(255)));
	gui.add(timeToChangeCircles.set("Toggle Circles", false));
	gui.add(variation1.set("Variation 1", true));
	gui.add(variation2.set("Variation 2", false));
	gui.add(variation3.set("Variation 3", false));
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
	//angle stuff
	startAngleModifier = 0.015;
	startNorthAngle = ofDegToRad(90.0f);
	startSouthAngle = ofDegToRad(270.0f);
	startEastAngle = 0;
	startWestAngle = ofDegToRad(180.0);
	angleVar = 0.1;
}

//--------------------------------------------------------------
void ofApp::update(){
	startNorthAngle += startAngleModifier;
	startSouthAngle += startAngleModifier;
	startEastAngle +=  startAngleModifier;
	startWestAngle +=  startAngleModifier;
	northAngle = startNorthAngle;
	southAngle = startSouthAngle;	
	eastAngle = startEastAngle;
	westAngle = startWestAngle;

	if (variation1) {
		variation2.set("Variation 2", false);
		variation3.set("Variation 3", false);
	}
	else if (variation2) {
		variation1.set("Variation 1", false);
		variation3.set("Variation 3", false);
	}
	else if (variation3) {
		variation2.set("Variation 2", false);
		variation1.set("Variation 1", false);
	}

	
	if ((timeToChangeCircles) ||(window_width != ofGetWidth()) || (window_height != ofGetHeight())) {
		circles.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		for (int i = 0; i < 100; i++) {
			//int randomRadius = ofRandom(minRadius, maxRadius);
			int randomX = ofRandom(radius, window_width - radius);
			int randomY = ofRandom(radius, window_height - radius);
			circles.push_back(new Circle(randomX, randomY, radius, resolution, window_width, window_height));
		}
		timeToChangeCircles.set("Toggle Circles", false);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(backGroundColor);
	//ofBackground(ofColor::blue);

	for (vector<Circle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
		(*itr)->drawCircle(backGroundColor);
		for (vector<Circle*>::iterator itr2 = circles.begin(); itr2 != circles.end(); ++itr2) {
			if (itr != itr2) {
				if (distanceBetweenTwoPoints((*itr)->getX(), (*itr)->getY(), (*itr2)->getX(), (*itr2)->getY()) <= (2 * radius)) {
					//ofBackground(ofColor::white);
					if (variation1) {
						radius = 30;
						(*itr)->drawSurroundingCircles(lineColor);
					}
					if (variation2) {
						radius = 30;
						sinNorthY = ofMap(sin(northAngle), -1, 1, (*itr)->getY() - radius, (*itr)->getY() + radius);
						cosNorthX = ofMap(cos(northAngle), -1, 1, (*itr)->getX() - radius, (*itr)->getX() + radius);
						sinSouthY = ofMap(sin(southAngle), -1, 1, (*itr)->getY() - radius, (*itr)->getY() + radius);
						cosSouthX = ofMap(cos(southAngle), -1, 1, (*itr)->getX() - radius, (*itr)->getX() + radius);
						sinEastY = ofMap(sin(eastAngle), -1, 1, (*itr)->getY() - radius, (*itr)->getY() + radius);
						cosEastX = ofMap(cos(eastAngle), -1, 1, (*itr)->getX() - radius, (*itr)->getX() + radius);
						sinWestY = ofMap(sin(westAngle), -1, 1, (*itr)->getY() - radius, (*itr)->getY() + radius);
						cosWestX = ofMap(cos(westAngle), -1, 1, (*itr)->getX() - radius, (*itr)->getX() + radius);
						(*itr)->drawOrbitingCircle(lineColor, cosNorthX, sinNorthY, cosSouthX, sinSouthY, cosEastX, sinEastY, cosWestX, sinWestY);
					}
					if (variation3) {
						radius = 100;
						ofSetColor(lineColor);
						ofVec3f arrowTailPoint = ofVec3f((*itr)->getX(), (*itr)->getY(), 0);
						ofVec3f arrowHeadPoint = ofVec3f((*itr2)->getX(), (*itr2)->getY(), 0);
						ofDrawArrow(arrowTailPoint, arrowHeadPoint,5.0f);
					}
				}
			}
		}
		if (variation2) {
			northAngle += angleVar;
			southAngle += angleVar;
			eastAngle += angleVar;
			westAngle += angleVar;
		}
	}
	if (isDrawingGui) {
		gui.draw();
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
