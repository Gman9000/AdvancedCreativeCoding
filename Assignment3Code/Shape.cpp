#include "Shape.h"

Shape::Shape()
{
	isPinching = true;
	color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	colorSwitcher = 0;
	maxY = 300;
	maxX = 300;
	startingX = 50;
	startingY = 50;
	width = 50;
	height = 50;

	// this is art based on the top left corner of the screen
	/*minRotationValue = 10;
	maxRotationValue = 15;*/

	minRotationValue = 50;
	maxRotationValue = 150;
	rotationValue = ofRandom(minRotationValue,maxRotationValue);
}

Shape::~Shape()
{
}

void Shape::pinchNPull()
{
	if ((startingX >= maxX) || (startingY >= maxY)) {
		isPinching = true;
	}
	else if ((startingX <= 0) || (startingY <= 0)) {
		isPinching = false;
	}
	if (isPinching) {
		--startingX;
		--startingY;
	}
	else {
		++startingX;
		++startingY;
	}
}

void Shape::changeColor()
{
	++colorSwitcher;
	switch (colorSwitcher)
	{
	case 1: // code to be executed if n = 1;
		//all black
		color = ofColor(0);
		break;
	case 2: // code to be executed if n = 2;
		//all blue based values
		color = ofColor(0, 0, ofRandom(255));
		break;
	case 3: // code to be executed if n = 3;
		//all green based values
		color = ofColor(0, ofRandom(255), 0);
		break;
	case 4: // code to be executed if n = 4;
		//all green-blue based values
		color = ofColor(0, ofRandom(255), ofRandom(255));
		break;
	case 5: // code to be executed if n = 5;
		//all red  based values
		color = ofColor(ofRandom(255), 0, 0);
		break;
	case 6: // code to be executed if n = 6;
		// all red-blue based values
		color = ofColor(ofRandom(255), 0, ofRandom(255));
		break;
	case 7: // code to be executed if n = 7;
		//all red-green based values
		color = ofColor(ofRandom(255), ofRandom(255), 0);
		break;
	case 8: // code to be executed if n = 8;
		//all values
		color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
		break;
	default: // code to be executed if n doesn't match any cases
		// this turns the alpha to 0
		color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255),0);
		colorSwitcher = 0;
	}
	
}

void Shape::draw() {
	ofSetColor(color);
	ofSetRectMode(OF_RECTMODE_CENTER);

	// this is art based on the top left corner of the screen
	/*
	ofRotateZ(ofGetElapsedTimef() * rotationValue);
	ofDrawRectangle(startingX, startingY, width, height);
	*/

	ofPushMatrix();
	ofTranslate(1000, 500);
	ofRotateZ(ofGetElapsedTimef() * rotationValue);
	ofDrawRectangle(startingX, startingY, width, height);
	ofPopMatrix();	
	
	pinchNPull();
}


