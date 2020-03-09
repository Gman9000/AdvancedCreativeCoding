#include "FractalCircle.h"

FractalCircle::FractalCircle() 
{
	x = 0;
	y = 0;
	radius = 300.0f;
	originalRadius = 300.0f;
	circleResolution = 3;
}


FractalCircle::FractalCircle(int xPos, int yPos, float circleRadius, int circleRes){
	x = xPos;
	y = yPos;
	radius = circleRadius;
	originalRadius = circleRadius;
	circleResolution = circleRes;
}

float FractalCircle::getOriginalRadius() {
	return originalRadius;
}
void FractalCircle::setRadius(float newRadius) {
	radius = newRadius;
}
void FractalCircle::drawCircle(ofColor color)
{
	ofSetCircleResolution(circleResolution);
	ofSetColor(color);
	ofDrawCircle(x, y, radius);
}
void FractalCircle::drawCircleY(float yPos, ofColor color) {
	ofSetCircleResolution(circleResolution);
	ofSetColor(color);
	ofDrawCircle(x, yPos, radius);
}
void FractalCircle::drawCircleX(float xPos, ofColor color) {
	ofSetCircleResolution(circleResolution);
	ofSetColor(color);
	ofDrawCircle(xPos, y, radius);
}
void FractalCircle::drawCircleXY(float xPos, float yPos, ofColor color) {
	ofSetCircleResolution(circleResolution);
	ofSetColor(color);
	ofDrawCircle(xPos, yPos, radius);
}

void FractalCircle::setCircleResolution(int circleRes)
{
	circleResolution = circleRes;
}



