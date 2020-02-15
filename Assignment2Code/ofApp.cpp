#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//sucessTimeDelta = 500; //0.5 seconds

	sizeModifier = 0.001f;
	isIncreasingSize = true;
	maxCircleSize = 30.0f;
	currentCircleSize = 15.0f;
	minCircleSize = 5.0f;
	
	//isIncreasingColor = true;
	maxColor = 255;
	//currentColor = 100;
	currentRColor = 51;
	currentGColor = 150;
	currentBColor = 250;
	minColor = 0;


	ofSetWindowShape(1900, 1000);
	//different frame rates makes the artwork really interesting. i'm really digging the 15fps perspective
	//ofSetFrameRate(60);
	//ofSetFrameRate(30);
	ofSetFrameRate(15);
	ofSetBackgroundColor(0, 0, 0); //pure black
	//ofSetBackgroundColor(176, 196, 222); // steel blue
}

//--------------------------------------------------------------
void ofApp::update(){
	/*this was for grayscale. in the future i can have a boolean changeable via mouseclick that allows you to swap between the commented
	color code and the uncommented color code but i want only eye interaction for this assignment*/

	/*if (isIncreasingColor) {
		currentColor++;
		ofSetColor(currentColor);
	}
	else {
		currentColor--;
		ofSetColor(currentColor);
	}*/


	/*if (currentColor >= maxColor) {
		isIncreasingColor = false;
	}
	else if (currentColor <= minColor) {
		isIncreasingColor = true;
	}*/

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

	if(currentCircleSize >= maxCircleSize) {
		isIncreasingSize = false;
	}
	else if (currentCircleSize <= minCircleSize) {
		isIncreasingSize = true;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//draw the circles for each row and each column
	for (int x = 0; x < 1900; x += 50)
	{
		for (int y = 0; y < 1000; y += 50)
		{
			if (isIncreasingSize) {
				currentCircleSize += sizeModifier;
				ofCircle(x + 25, y + 25, currentCircleSize);
			}
			else {
				currentCircleSize -= sizeModifier;
				ofCircle(x + 25, y + 25, currentCircleSize);
			}

		}
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
