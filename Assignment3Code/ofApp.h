#pragma once

#include "ofMain.h"
#include "/Users/granv/Documents/of/of_v0.11.0_vs2017_release/apps/myApps/Assignment3/Shape.h"

class ofApp : public ofBaseApp{

	public:
		vector<Shape> shapes;

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
