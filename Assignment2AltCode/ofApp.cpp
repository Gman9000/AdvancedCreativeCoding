#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sizeModifier = 0.00015f;
	isIncreasingSize = true;
	maxCircleSize = 30.0f;
	currentCircleSize = 15.0f;
	minCircleSize = 5.0f;
	
	maxColor = 255;
	currentRColor = 51;
	currentGColor = 150;
	currentBColor = 250;
	minColor = 0;
	movementX = 1;
	movementY = 500;
	window_width = 1900;
	window_height = 1000;
	isIncreasingMovementX = true;
	isIncreasingMovementY = true;

	movementModifier = 3;


	ofSetWindowShape(window_width, window_height);
	//different frame rates makes the artwork really interesting. i'm really digging the 30fps perspective
	//ofSetFrameRate(60);
	//ofSetFrameRate(15);
	ofSetFrameRate(30);
	ofSetBackgroundColor(0, 0, 0); //pure black
}

//--------------------------------------------------------------
void ofApp::update(){
	//increase/decrease each component color separately to show a better range of colors for our pulsating circles
	if (isIncreasingRColor) {
		currentRColor++;
		ofSetColor(currentRColor, currentGColor, currentBColor);
	}
	else {
		currentRColor--;
		ofSetColor(currentRColor, currentGColor, currentBColor);
	}

	if (isIncreasingGColor) {
		currentGColor++;
		ofSetColor(currentRColor, currentGColor, currentBColor);
	}
	else {
		currentGColor--;
		ofSetColor(currentRColor, currentGColor, currentBColor);
	}

	if (isIncreasingBColor) {
		currentBColor++;
		ofSetColor(currentRColor, currentGColor, currentBColor);
	}
	else {
		currentBColor--;
		ofSetColor(currentRColor, currentGColor, currentBColor);
	}


	//toggles between incrementing and decrementing the color components when they hit certain minimums/maximums 
	if (currentRColor >= maxColor) {
		isIncreasingRColor = false;
	}
	else if (currentRColor <= minColor) {
		isIncreasingRColor = true;
	}

	if (currentGColor >= maxColor) {
		isIncreasingGColor = false;
	}
	else if (currentGColor <= minColor) {
		isIncreasingGColor = true;
	}

	if (currentBColor >= maxColor) {
		isIncreasingBColor = false;
	}
	else if (currentBColor <= minColor) {
		isIncreasingBColor = true;
	}

	//toggles between increasing and decreasing circle size
	if(currentCircleSize >= maxCircleSize) {
		isIncreasingSize = false;
	}
	else if (currentCircleSize <= minCircleSize) {
		isIncreasingSize = true;
	}

	//toggles between moving left and right
	if (movementX >= window_width) {
		isIncreasingMovementX = false;
	}
	if (movementX <= 0) {
		isIncreasingMovementX = true;
	}
	//toggles between moving up and down
	if (movementY >= window_height) {
		isIncreasingMovementY = false;
	}
	if (movementY <= 0) {
		isIncreasingMovementY = true;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//draw the circles for each row and each column
	for (int x = -window_width; x < window_width+50; x += 50)
	{
		for (int y = -window_height; y < window_height+50; y += 50)
		{
			if (isIncreasingSize) {
				currentCircleSize += sizeModifier;
				ofCircle(x + 25 + movementX, y + 25+movementY, currentCircleSize);
			}
			else {
				currentCircleSize -= sizeModifier;
				ofCircle(x + 25 + movementX, y + 25 + movementY, currentCircleSize);
			}

		}
	}
	if (isIncreasingMovementX) {
		movementX+= movementModifier;
	}
	else {
		movementX-= movementModifier;
	}

	if (isIncreasingMovementY) {
		movementY += movementModifier;
	}
	else {
		movementY -= movementModifier;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
