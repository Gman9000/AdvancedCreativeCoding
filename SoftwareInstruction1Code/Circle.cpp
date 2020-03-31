#include "Circle.h"


Circle::Circle()
{
	x = 0;
	y = 0;
	radius = 300.0f;
	circleResolution = 3;
	window_width = 1000;
	window_height = 1000;
	minMovementSpeedX = 1;
	maxMovementSpeedX = 3;
	minMovementSpeedY = 1;
	maxMovementSpeedY = 3;
	isGoingRight = true;
	isGoingUp = false;
}
Circle::Circle(int xPos, int yPos, float circleRadius, int circleRes, int win_widt, int win_height) {
	x = xPos;
	y = yPos;
	radius = circleRadius;
	circleResolution = circleRes;
	window_width = win_widt;
	window_height = win_height;
	minMovementSpeedX = 1;
	maxMovementSpeedX = 3;
	minMovementSpeedY = 1;
	maxMovementSpeedY = 3;
	isGoingRight = true;
	isGoingUp = false;
}

void Circle::drawCircle(ofColor color) {
	if (x >= window_width - radius) {
		setIsGoingRight(false);
		//flip a coin and set the direction of the vertical accordingly
		if (round(ofRandom(0, 1))) {
			setIsGoingUp(true);
		}
		else {
			setIsGoingUp(false);
		}
	}
	else if (x <= radius) {
		setIsGoingRight(true);
		//flip a coin and set the direction of the vertical accordingly
		if (round(ofRandom(0, 1))) {
			setIsGoingUp(true);
		}
		else {
			setIsGoingUp(false);
		}
	}
	if (y >= window_height - radius) {
		setIsGoingUp(true);
		//flip a coin and set the direction of the horizontal accordingly
		if (round(ofRandom(0, 1))) {
			setIsGoingRight(true);
		}
		else {
			setIsGoingRight(false);
		}
	}
	else if (y <= radius) {
		setIsGoingUp(false);
		//flip a coin and set the direction of the horizontal accordingly
		if (round(ofRandom(0, 1))) {
			setIsGoingRight(true);
		}
		else {
			setIsGoingRight(false);
		}
	}
	
	if (isGoingRight) {
		setX(x + ofRandom(minMovementSpeedX, maxMovementSpeedX));
	}
	else {
		setX(x - ofRandom(minMovementSpeedX, maxMovementSpeedX));
	}
	if (isGoingUp) {
		setY(y - ofRandom(minMovementSpeedY, maxMovementSpeedY));
	}
	else {
		setY(y + ofRandom(minMovementSpeedY, maxMovementSpeedY));
	}
	
	
	ofSetCircleResolution(circleResolution);
	ofSetColor(color);
	ofDrawCircle(x, y, radius);
}
void Circle::drawSurroundingCircles(ofColor color) {
	//draw a circle temporarily for north/south/east/west
	ofSetColor(color);
	ofNoFill();
	//north
	ofDrawCircle(x, y-radius, radius/3);
	//south
	ofDrawCircle(x, y+radius, radius/3);
	//east
	ofDrawCircle(x+radius, y, radius/3);
	//west
	ofDrawCircle(x-radius, y, radius/3);
}

void Circle::drawOrbitingCircle(ofColor color, float cosNorthX, float sinNorthY, float cosSouthX, float sinSouthY, float cosEastX, float sinEastY, float cosWestX, float sinWestY) {
	ofSetColor(color);
	ofSetCircleResolution(3);
	ofFill();
	ofDrawCircle(cosNorthX, sinNorthY, radius / 3);
	ofDrawCircle(cosSouthX, sinSouthY, radius / 3);
	ofDrawCircle(cosEastX, sinEastY, radius / 3);
	ofDrawCircle(cosWestX, sinWestY, radius / 3);
}



void Circle::setCircleResolution(int circleRes)
{
	circleResolution = circleRes;
}

int Circle::getX() {
	return x;
}
void Circle::setX(int newX) {
	x = newX;
}
int Circle::getY() {
	return y;
}
void Circle::setY(int newY) {
	y = newY;
}
void Circle::setIsGoingRight(bool newBool) {
	isGoingRight = newBool;
}
void Circle::setIsGoingUp(bool newBool) {
	isGoingUp = newBool;
}
