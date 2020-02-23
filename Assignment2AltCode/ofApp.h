#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		float maxCircleSize;
		float currentCircleSize;
		float minCircleSize;
		bool isIncreasingSize;
		float sizeModifier;

		int movementX;
		int movementY;
		int window_width;
		int window_height;
		bool isIncreasingMovementX;
		bool isIncreasingMovementY;
		int movementModifier;

		//unsigned long actualTime;
		//unsigned int sucessTimeDelta;

		int maxColor;
		//int currentColor;
		int currentRColor;
		int currentGColor;
		int currentBColor;
		int minColor;
		//bool isIncreasingColor;
		bool isIncreasingRColor;
		bool isIncreasingGColor;
		bool isIncreasingBColor;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
