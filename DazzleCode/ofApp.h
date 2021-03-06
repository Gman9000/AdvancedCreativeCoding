#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "FractalCircle.h"
#include "ofxOsc.h"


class ofApp : public ofBaseApp{

	public:
		//osc stuff
		ofxOscSender sender;
		ofxOscReceiver receiver;
		float timeSent, timeReceived;

		// relates to volume of the song
		float energy;
		float tempo;
		bool searchedForASong;
		bool receivedData;
		int beatPerFrameValue;

		float valence;
		int frameNumberSinceSearch;

		//SPOTIFY API VARIABLES
		string urlBase;
		string urlSearch;
		void setup();
		void update();
		void draw();

		//ofShader shader;

		ofxPanel gui;
		ofParameter<float> musicVolume;
		ofParameter<int> lineThickness;
		ofParameter<int> circleResolution;
		ofParameter<float> circleRadius;
		ofParameter<float> fractalThreshold;
		ofParameter<bool> triggerMusicVisualization;
		//ofParameter<int> musicVisualizationChilltensity;
		ofParameter<int> pulseIntensity;
		ofParameter<int> startingPulseSizeOffset;
		ofParameter<int> bands;
		ofParameter<bool> triggerXMotion;
		ofParameter<bool> triggerYMotion;
		ofParameter<bool> triggerMultiColorGradient;
		//ofParameter<bool> triggerGradientShifter;
		ofParameter<int> gradientShifter;
		ofParameter<ofColor> backGroundColor;
		ofParameter<ofColor> singleFractalColor;
		ofParameter<string> screenShot;
		ofParameter<string> spotifySearch;
		ofColor color;
		float hue;
		float hueModifier;

		ofSoundPlayer myPlayer;
		bool isMusicPaused;
		bool hasPausedVisualizations;
		bool toggleVisuals;
		// MUSIC BY https://www.fesliyanstudios.com/royalty-free-music/downloads-c/lofi-hip-hop-music/37
		string musicList[10] = { "Lazy_Day","Feels_Good", "Out_And_About", "Done_With_Work","Bobbin","Vibes", "Homework", "I_Got_This", "Chill_Gaming", "On_My_Own" };
		//string musicList[1] = { "Bobbin" };
		int musicCounter;

		bool isIncreasingGradientShift;
		int maxGradientShift;
		int minGradientShift;
		int hueValue;
		bool isIncreasingCircleResolution;
		int maxCircleResolution;
		int minCircleResolution;
		
		bool isDrawingGui;
		float currentFractalThreshold;
		float currentCircleRadius;
		int currentCircleResolution;
		void generateFractalCircle(int xPos, int yPos, int circleRadius);
		float startAngle = 0;
		float angleVar = 0.1;
		int window_width;
		int window_height;

		vector<FractalCircle*> circles;

		//MUSIC VISUALIZATION STUFF
		float * fftSmooth;
		//int bands;
		float previousTempCalculation;
		float calculationThreshold;

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
