#pragma once
#include "C:\Users\granv\Documents\of\libs\openFrameworks\app\ofBaseApp.h"
#include "ofMain.h"

class Shape:
	public ofBaseApp
{
public:
	Shape();
	~Shape();


	void draw();
	void pinchNPull();
	void changeColor();
	int colorSwitcher;

	bool isPinching;
	ofColor color;

	// i have these for future endeavors when i wanna manipulate these rotation values via key presses and stuff
	int minRotationValue;
	int maxRotationValue;

	int maxX;
	int maxY;
	int startingX;
	int startingY;
	int width;
	int height;

private:
	int rotationValue;
};

