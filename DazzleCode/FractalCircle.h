#pragma once

#include "ofMain.h"
class FractalCircle
{
private:
	int x;
	int y;
	float radius;
	float originalRadius;
	int circleResolution;
public:
	float getOriginalRadius();
	void setRadius(float newRadius);
	FractalCircle();	
	FractalCircle(int xPos, int yPos, float circleRadius, int circleRes);
	void drawCircle(ofColor color);
	void drawCircleY(float yPos,ofColor color);
	void drawCircleX(float xPos, ofColor color);
	void drawCircleXY(float xPos, float yPos, ofColor color);
	void setCircleResolution(int circleRes);

};

