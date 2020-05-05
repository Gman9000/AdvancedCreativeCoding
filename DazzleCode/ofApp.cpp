#include "ofApp.h"
#include <iterator>

ofImage screenshottedImage;
float angle = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	// recievers only need ports
	// senders need ip and ports
	receiver.setup(8080);
	sender.setup("127.0.0.1", 8082);
	ofSetFrameRate(30);
	searchedForASong = false;
	receivedData = false;

	ofNoFill();
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	//gui.setup("enter->toggler music");
	gui.add(musicVolume.set("Music Volume", 1.0f, 0.0f, 1.0f));
	//gui.add(lineThickness.set("Line Thickness", 1, 1, 20));
	gui.add(circleResolution.set("Circle Resolution", 4, 3, 30));
	gui.add(circleRadius.set("Circle Radius", 1000, 100, 1000));
	gui.add(fractalThreshold.set("Fractal Threshold", 0.002, 0.002, 300));
	gui.add(triggerMusicVisualization.set("Trigger Visualz!", false));
	gui.add(pulseIntensity.set("Pulse Intensity", 1, 1, 10));
	gui.add(startingPulseSizeOffset.set("Starting Pulse Size Offset", 5, 0, 50));
	//gui.add(circleResolution.set("Circle Resolution", 4, 3, 30));
	//gui.add(musicVisualizationChilltensity.set("visualz Chilltensity", 10, 1, 10));
	gui.add(bands.set("band number", 64, 4, 128)); 
	gui.add(triggerXMotion.set("Trigger X Motion!", false));
	gui.add(triggerYMotion.set("Trigger Y Motion!", false));
	gui.add(triggerMultiColorGradient.set("Trigger Multi Gradient!", false));
	//gui.add(triggerGradientShifter.set("Trigger Gradient Shifter!", false));
	gui.add(gradientShifter.set("Gradient Shifter", 1, 0, 255));
	gui.add(singleFractalColor.set("Single Fractal Color", ofColor(255, 0, 0), ofColor(0), ofColor(255)));
	gui.add(backGroundColor.set("Background Color", ofColor(0, 0, 0), ofColor(0), ofColor(255)));
	gui.add(screenShot.set("Screenshot"));
	gui.add(spotifySearch.set("SongTitleSearch"));


	hue = 0;
	hueModifier = 0.1f;
	color = singleFractalColor;
	currentFractalThreshold = fractalThreshold;
	currentCircleRadius = circleRadius;
	isIncreasingCircleResolution = true;
	minCircleResolution = 3;
	maxCircleResolution = 30;
	
	
	//screen size
	window_width = 1000;
	//window_width = ofGetWindowWidth();
	window_height = 1000;
	//window_height = ofGetWindowHeight();
	ofSetWindowShape(window_width, window_height);
	generateFractalCircle(window_width / 2, window_height / 2, circleRadius);
	
	//for in triggerGradientShift Mode
	isIncreasingGradientShift = true;
	maxGradientShift = 255;
	minGradientShift = 0;
	
	/* //MUSIC HANDLING
	//make this true for now so that i can play spotify music
	//isMusicPaused = false;
	isMusicPaused = true;
	hasPausedVisualizations = false;
	musicCounter = 0;
	myPlayer.load(musicList[musicCounter] + ".mp3");
	fftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++) {
		fftSmooth[i] = 0;
	}
	//we are just messing with shapes so we don't need a high band
	//bands = 64; //EDITING THIS IN GUI BEFORE MAKING IT PERMANENT
	//commenting this out for now
	//myPlayer.play();
	//myPlayer.setVolume(0);
	toggleVisuals = false;
	

	//hackandslash
	previousTempCalculation = 0.0f;
	calculationThreshold = 1.0f;*/

}

//--------------------------------------------------------------
void ofApp::update(){

	while (receiver.hasWaitingMessages()) {
		ofxOscMessage rMsg;
		receiver.getNextMessage(rMsg);
		if (rMsg.getAddress() == "/energy") {
			energy = rMsg.getArgAsFloat(0);
			//OSC handling energy level to circle resolution combo
			circleResolution = ofMap(energy, 0.0f, 1.0f, 30, 3);
			//ofLog(OF_LOG_NOTICE, "the energy of the song is " + ofToString(energy));
		}
		else if (rMsg.getAddress() == "/tempo") {
			tempo = roundf(rMsg.getArgAsFloat(0));
			float bpm = tempo / 60.0f;
			float setFrameRate = 1.0f / 30.0f;
			float intermediaryStep = (bpm * setFrameRate);

			//ofLog(OF_LOG_NOTICE, "the bpm is " + ofToString(bpm));
			//ofLog(OF_LOG_NOTICE, "the setFrameRate is " + ofToString(setFrameRate));
			//ofLog(OF_LOG_NOTICE, "the intermediaryStep is " + ofToString(intermediaryStep));
			beatPerFrameValue = roundf(1.0f/intermediaryStep);
			//ofLog(OF_LOG_NOTICE, "the beatPerFrameValue is " + ofToString(beatPerFrameValue));
			// 1/ (tempo/60seconds * 1 second/30 frames (my framerate) ) is the formula
			//and we gotta round it nicely
			//tempo = rMsg.getArgAsFloat(0);
			//ofLog(OF_LOG_NOTICE, "the tempo of the song is " + ofToString(tempo));
			receivedData = true;
		}
		else if (rMsg.getAddress() == "/valence") {
			valence = rMsg.getArgAsFloat(0);
			//ofLog(OF_LOG_NOTICE, "the tempo of the song is " + ofToString(tempo));
			//OSC handling valence level to circle thickness combo
			lineThickness = ofMap(valence, 0.0f, 1.0f, 1, 5);
		}
		
	}
	for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
		if (searchedForASong && receivedData && triggerMusicVisualization) {
			if ((ofGetFrameNum() - frameNumberSinceSearch) % beatPerFrameValue == 0) {
				(*itr)->setRadius((*itr)->getOriginalRadius() + startingPulseSizeOffset);
			}
			else {
				(*itr)->setRadius((*itr)->getCurrentRadius() - pulseIntensity);
			}
		}
		else {
			(*itr)->setRadius((*itr)->getOriginalRadius());
		}
	}
	//osc handling tempo somehow
	//circleRadius = 100;
	//ofLog(OF_LOG_NOTICE, "the beatPerFrameValue is " + ofToString(beatPerFrameValue));
	/*if (searchedForASong && receivedData) {
		if ((ofGetFrameNum() - frameNumberSinceSearch) % beatPerFrameValue == 0) {

			circleRadius = 1000;
		}
		circleRadius = MIN(1000, circleRadius - 5);
	}*/
	//do stuff with the tempo variable

	/* //music handling 
	myPlayer.setVolume(musicVolume);
	ofSoundUpdate();
	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] = 0.3f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}
	if (!myPlayer.isPlaying() && !isMusicPaused) {
		++musicCounter;
		int lengthOfArray = sizeof(musicList) / sizeof(*musicList); //THIS ACTUALLY WORKED WHICH IS JUST WOW
		if (musicCounter >= lengthOfArray) {
			musicCounter = 0;
		}
		myPlayer.load(musicList[musicCounter] + ".mp3");
		myPlayer.play();
	}*/

	startAngle += 0.015;
	angle = startAngle;
	ofSetLineWidth(lineThickness);
	if (triggerMultiColorGradient) {
		hue += hueModifier;
		if (hue >= 255) {
			hue = 0;
		}
		color.setHue(hue);

		if (isIncreasingGradientShift)
		{
			++gradientShifter;
		}
		else {
			--gradientShifter;
		}

		//toggles between increasing and decreasing gradient shifts
		if (gradientShifter >= maxGradientShift) {
			isIncreasingGradientShift = false;
		}
		else if (gradientShifter <= minGradientShift) {
			isIncreasingGradientShift = true;
		}
	}


	if ((currentFractalThreshold != fractalThreshold) || (currentCircleRadius != circleRadius) || (currentCircleResolution != circleResolution) || (window_width != ofGetWidth()) || (window_height != ofGetHeight()) )  {
		circles.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		currentFractalThreshold = fractalThreshold;
		currentCircleRadius = circleRadius;
		currentCircleResolution = circleResolution;
		generateFractalCircle(window_width / 2, window_height / 2, circleRadius);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(backGroundColor);
		if (triggerXMotion && !triggerYMotion)
		{
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
				float x = ofMap(cos(angle), -1, 1, 0, float(ofGetWindowWidth()));

				/*if (triggerMusicVisualization) {
					
					for (int i = 0; i < bands; i++) {
						float tempCalculation = (*itr)->getOriginalRadius() + abs((fftSmooth[i] * (*itr)->getOriginalRadius()) / musicVisualizationChilltensity);
						if (abs(tempCalculation - previousTempCalculation) > calculationThreshold) {
							(*itr)->setRadius(tempCalculation); //MUSIC VISUALIZAITON VIA RADIUS SHIFTINGS
							if (triggerMultiColorGradient) {
								(*itr)->drawCircleX(x, color);
							}
							else {
								(*itr)->drawCircleX(x, singleFractalColor);
							}
						}
						previousTempCalculation = tempCalculation;
					}
				}*/
				//else {
				//(*itr)->setRadius((*itr)->getOriginalRadius());
				if (triggerMultiColorGradient) {
					(*itr)->drawCircleX(x, color);
				}
				else {
					(*itr)->drawCircleX(x, singleFractalColor);
				}
				//}
				angle += angleVar;
			}
		}
		else if (!triggerXMotion && triggerYMotion) {
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
				float y = ofMap(sin(angle), -1, 1, 0, float(ofGetWindowHeight()));
				/*if (triggerMusicVisualization) {
					for (int i = 0; i < bands; i++) { 
						float tempCalculation = (*itr)->getOriginalRadius() + abs( (fftSmooth[i] * (*itr)->getOriginalRadius()) / musicVisualizationChilltensity);
						if (abs(tempCalculation - previousTempCalculation) > calculationThreshold) {
							(*itr)->setRadius(tempCalculation); //MUSIC VISUALIZAITON VIA RADIUS SHIFTINGS
							if (triggerMultiColorGradient) {
								(*itr)->drawCircleY(y, color);
							}
							else {
								(*itr)->drawCircleY(y, singleFractalColor);
							}
						}
						previousTempCalculation = tempCalculation;
					}
				}*/
				//else {
				//(*itr)->setRadius((*itr)->getOriginalRadius());
				if (triggerMultiColorGradient) {
					(*itr)->drawCircleY(y, color);
				}
				else {
					(*itr)->drawCircleY(y, singleFractalColor);
				}

				//}
				angle += angleVar;
			}

		}
		else if (triggerXMotion && triggerYMotion)
		{
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
				float y = ofMap(sin(angle), -1, 1, 0, float(ofGetWindowHeight()));
				float x = ofMap(cos(angle), -1, 1, 0, float(ofGetWindowWidth()));
				/*if (triggerMusicVisualization) {
					for (int i = 0; i < bands; i++) {
						float tempCalculation = (*itr)->getOriginalRadius() + abs((fftSmooth[i] * (*itr)->getOriginalRadius()) / musicVisualizationChilltensity);
						if (abs(tempCalculation - previousTempCalculation) > calculationThreshold) {
							(*itr)->setRadius(tempCalculation); //MUSIC VISUALIZAITON VIA RADIUS SHIFTINGS
							if (triggerMultiColorGradient) {
								(*itr)->drawCircleXY(x, y, color);
							}
							else {
								(*itr)->drawCircleXY(x, y, singleFractalColor);
							}
						}
						previousTempCalculation = tempCalculation;
					}
				}*/
				//else {
				//(*itr)->setRadius((*itr)->getOriginalRadius());
				if (triggerMultiColorGradient) {
					(*itr)->drawCircleXY(x, y, color);
				}
				else {
					(*itr)->drawCircleXY(x, y, singleFractalColor);
				}
				//}
				angle += angleVar;
			}
		}
		else
		{
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {

				/*if (triggerMusicVisualization) {
					for (int i = 0; i < bands; i++) {
						float tempCalculation = (*itr)->getOriginalRadius() + abs((fftSmooth[i] * (*itr)->getOriginalRadius()) / musicVisualizationChilltensity);
						if (abs(tempCalculation - previousTempCalculation) > calculationThreshold) {
							(*itr)->setRadius(tempCalculation); //MUSIC VISUALIZAITON VIA RADIUS SHIFTINGS
							if (triggerMultiColorGradient) {
								(*itr)->drawCircle(color);
							}
							else {
								(*itr)->drawCircle(singleFractalColor);
							}
						}
						previousTempCalculation = tempCalculation;
					}
				}*/
				//else {
				//(*itr)->setRadius((*itr)->getOriginalRadius());
				if (triggerMultiColorGradient) {
					(*itr)->drawCircle(color);
				}
				else {
					(*itr)->drawCircle(singleFractalColor);
				}
				//}
			}
		}

	if (isDrawingGui) {
		gui.draw();
	}
}

void ofApp::generateFractalCircle(int xPos, int yPos, int radius) {
	if (radius >= fractalThreshold) {
		//leftSide
		generateFractalCircle(xPos - (radius / 2), yPos, radius / 2);
		//generateFractalCircle(xPos, yPos, radius / 2);
		//rightSide
		generateFractalCircle(xPos + (radius / 2), yPos, radius / 2);
	}
	//circles.push_back(new FractalCircle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 300, 12));
	//circles.push_back(new FractalCircle(xPos, yPos, radius, currentCircleResolution, shader));
	circles.push_back(new FractalCircle(xPos, yPos, radius, currentCircleResolution));

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'x') {
		isDrawingGui = !isDrawingGui;
	}
	else if (key == OF_KEY_RETURN) {
		ofxOscMessage message;
		message.setAddress("/userSearch");
		message.addStringArg(spotifySearch.toString());
		sender.sendMessage(message);
		frameNumberSinceSearch = ofGetFrameNum();
		searchedForASong = true;
		receivedData = false;
		//ofLog(OF_LOG_NOTICE, ofToString(frameNumberSinceSearch));

	}
	else if (key == OF_KEY_PAGE_UP) {
		screenshottedImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshottedImage.save(screenShot.toString() + ".png");
		screenShot.set("Screenshot Saved!");
	}
	else if (key == OF_KEY_DEL) {
		if (!isMusicPaused) {
			isMusicPaused = true;
			if (triggerMusicVisualization) {
				hasPausedVisualizations = true;
				triggerMusicVisualization.set("Trigger Visualz!", false);
			}
			myPlayer.setPaused(true);
		}
		else {
			isMusicPaused = false;
			if (hasPausedVisualizations) {
				triggerMusicVisualization.set("Trigger Visualz!", true);
				hasPausedVisualizations = false;
			}
			myPlayer.setPaused(false);
			//myPlayer.play();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
