#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Circle.h"


/*
My first instruction: A surface filled with circles of the same size moving at a relatively slow speed. 
Show the intersections of any circles that come into contact with each other but do not show the intersecting circles themselves.
*/
class ofApp : public ofBaseApp{

	public:
		//gui stuff
		ofxPanel gui;
		ofParameter<ofColor> lineColor;
		ofParameter<int> lineThickness;
		ofParameter<ofColor> backGroundColor;
		ofParameter<bool> timeToChangeCircles;
		ofParameter<bool> variation1;
		ofParameter<bool> variation2;
		ofParameter<bool> variation3;
		ofParameter<string> screenShot;
		bool isDrawingGui;

		// circle stuff
		vector<Circle*> circles;
		
		//i'm hardcoding certain circle properties properties because i don't want to have this controlled by the gui
		int radius = 30;
		int resolution = 40;

		// window stuff
		int window_width;
		int window_height;

		// collision detection stuff
		int distanceBetweenTwoPoints(int x, int y, int a, int b);

		//angle stuff
		float startAngleModifier;
		float startNorthAngle;
		float startSouthAngle;
		float startEastAngle;
		float startWestAngle;
		float angleVar;
		float sinNorthY;
		float cosNorthX;
		float sinSouthY;
		float cosSouthX;
		float sinEastY;
		float cosEastX;
		float sinWestY;
		float cosWestX;
		

		void setup();
		void update();
		void draw();

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
