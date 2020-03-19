#pragma once
#include "ofMain.h"

class Circle
{
private:
	int x;
	int y;
	float radius;
	int circleResolution;
	int window_width;
	int window_height;
	//i'm hardcoding certain circle properties properties because i don't want to have this controlled by the gui
	int minMovementSpeedX;
	int maxMovementSpeedX;
	int minMovementSpeedY;
	int maxMovementSpeedY;
	//edgeDetection properties
	bool isGoingRight;
	bool isGoingUp;

public:
	Circle();
	Circle(int xPos, int yPos, float circleRadius, int circleRes, int win_widt, int win_height);
	void drawCircle(ofColor color);
	void setCircleResolution(int circleRes);
	int getX();
	void setX(int newX);
	int getY();
	void setY(int newY);
	void setIsGoingRight(bool newBool);
	void setIsGoingUp(bool newBool);
	void drawSurroundingCircles(ofColor color);

};

