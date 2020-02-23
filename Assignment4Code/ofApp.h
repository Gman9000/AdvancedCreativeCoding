#pragma once

#include "ofMain.h"
#include "/Users/granv/Documents/of/of_v0.11.0_vs2017_release/apps/myApps/Assignment4Alt/Shape.h"

class ofApp : public ofBaseApp{

	public:
		Shape bigEllipse;
		vector<Shape> shapesForImage1;
		vector<Shape> shapesForImage2;


		void setup();
		void update();
		void draw();
		ofImage ellipseImage;
		ofImage eyesImage;
		ofImage sneakerImage;
		ofImage leftHornOfSneaker;
		ofImage rightHornOfSneaker;


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
