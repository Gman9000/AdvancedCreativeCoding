#pragma once
//#include <iostream>
#include <list> 
#include "ofMain.h"
#include "ofxGui.h"
#include <iterator>
//#include "circle.h"





class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	ofxPanel gui;
	ofParameter<bool> triggerFill;
	ofParameter<int> lineWidth;
	ofParameter<float> maxCircleSize;
	ofParameter<float> minCircleSize;
	ofParameter<int> xSpacing;
	ofParameter<int> ySpacing;
	ofParameter<int> redComponent;
	ofParameter<int> greenComponent;
	ofParameter<int> blueComponent;
	ofParameter<int> alphaComponent;
	ofParameter<int> circleResolution;
	ofParameter<int> movementModifierX;
	ofParameter<int> movementModifierY;
	ofParameter<int> rotationModifier;
	ofParameter<float> increasingSizeModifier;
	ofParameter<float> decreasingSizeModifier;
	//ofParameter<bool> isIncreasingMovementX;
	//ofParameter<bool> isIncreasingMovementY;
	ofParameter<bool> triggerTheColors;
	ofParameter<bool> triggerTheRotation;
	ofParameter<bool> triggerMultiColorGradient;
	ofParameter<bool> triggerSingleColorGradient;
	ofParameter<bool> triggerGradientShifter;
	ofParameter<int> gradientShifter;
	ofParameter<bool> triggerGradientBrightness;
	ofParameter<int> gradientBrightness;
	ofParameter<ofColor> singleGradientcolorChoice;
	ofParameter<ofColor> backgroundColor;
	ofParameter<string> screenShot;
	ofColor color;
	//vector<circle*> circles;

	bool isPaused;

	ofSoundPlayer myPlayer;
	// MUSIC BY https://www.fesliyanstudios.com/royalty-free-music/downloads-c/lofi-hip-hop-music/37
	string musicList[10] = { "Bobbin","Lazy_Day","Feels_Good", "Out_And_About", "Done_With_Work", "Vibes", "Homework", "I_Got_This", "Chill_Gaming", "On_My_Own" };
	//string musicList[1] = { "Bobbin.mp3" };
	int musicCounter;
	//string musicItr = *musicList.begin();
	bool isIncreasingGradientShift;
	bool isIncreasingGradientBrightness;
	int maxGradientBrightnessShift;
	int minGradientBrightnessShift;
	int hueValue;
	int saturationValue;

	bool isDrawingGui;


	//float maxCircleSize;
	float currentCircleSize;
	//float minCircleSize;
	bool isIncreasingSize;
	//float sizeModifier;

	int movementX;
	int movementY;
	int window_width;
	int window_height;
	bool isIncreasingMovementX;
	bool isIncreasingMovementY;
	//int movementModifier;

	//unsigned long actualTime;
	//unsigned int sucessTimeDelta;

	int maxColor;
	int minColor;
	//bool isIncreasingColor;
	bool isIncreasingRColor;
	bool isIncreasingGColor;
	bool isIncreasingBColor;

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
