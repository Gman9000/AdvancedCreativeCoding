#include "ofApp.h"
#include <iterator>

ofImage screenshottedImage;
float angle = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	// Testing redirects and https.
	// This server will echo back everything that you send to it.
	//This is to get one specific song
	urlBase = "https://api.spotify.com/v1/search";
	urlSearch = "?q=Elixia&type=track";
	
	// Create a client.
	ofxHTTP::Client client;

	// Create a request.
	ofxHTTP::GetRequest request(urlBase + urlSearch);

	// Create a context.
	ofxHTTP::Context context;

	// Set custom session settings.
	//
	// See the class documentation for many additional settings.
	ofxHTTP::ClientSessionSettings sessionSettings;
	// Set a 60 second keep-alive timeout (default is 8 seconds).
	sessionSettings.setKeepAliveTimeout(Poco::Timespan::SECONDS * 60);

	// Save the session settings with the context.
	context.setClientSessionSettings(sessionSettings);

	try
	{
		// Execute the request within the given context.
		auto response = client.execute(context, request);

		// Check the response.
		if (response->getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
		{
			// A successful response.
			ofLogNotice("ofApp::setup") << "Response success, expecting " << response->estimatedContentLength() << " bytes.";

			// Buffer the response, or otherwise consume the stream.
			ofBuffer buffer(response->stream());

			ofLogNotice("ofApp::setup") << "Content Begin";

			std::cout << buffer << std::endl;

			ofLogNotice("ofApp::setup") << "Content End";
		}
		else
		{
			ofLogError("ofApp::setup") << response->getStatus() << " " << response->getReason();
		}
	}
	catch (const Poco::Exception& exc)
	{
		ofLogError("ofApp::setup") << exc.displayText();
		//YO IT ALWAYS BE CATCHING THIS ERROR SON
		// ERROR: [ error ] ofApp::setup: I/O error: No port can be determined for request.
	}
	catch (const std::exception& exc)
	{
		ofLogError("ofApp::setup") << exc.what();
	}
	
	//MAKE A CALL
	//GET THE SONG
	//PLAY THE SONG



	/*ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 2);
	shader.load("shadersGL3/shader");
	*/

	ofNoFill();
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	//gui.setup("enter->toggler music");
	gui.add(musicVolume.set("Music Volume", 1.0f, 0.0f, 1.0f));
	gui.add(lineThickness.set("Line Thickness", 1, 1, 20));
	gui.add(circleResolution.set("Circle Resolution", 4, 3, 30));
	gui.add(circleRadius.set("Circle Radius", 1000, 100, 1000));
	gui.add(fractalThreshold.set("Fractal Threshold", 0.002, 0.002, 300));
	gui.add(triggerMusicVisualization.set("Trigger Visualz!", false));
	//gui.add(circleResolution.set("Circle Resolution", 4, 3, 30));
	gui.add(musicVisualizationChilltensity.set("visualz Chilltensity", 10, 1, 10));
	gui.add(bands.set("band number", 64, 4, 128)); 
	gui.add(triggerXMotion.set("Trigger X Motion!", false));
	gui.add(triggerYMotion.set("Trigger Y Motion!", false));
	gui.add(triggerMultiColorGradient.set("Trigger Multi Gradient!", false));
	//gui.add(triggerGradientShifter.set("Trigger Gradient Shifter!", false));
	gui.add(gradientShifter.set("Gradient Shifter", 1, 0, 255));
	gui.add(singleFractalColor.set("Single Fractal Color", ofColor(255, 0, 0), ofColor(0), ofColor(255)));
	gui.add(backGroundColor.set("Background Color", ofColor(0, 0, 0), ofColor(0), ofColor(255)));
	gui.add(screenShot.set("Screenshot"));

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
	
	//MUSIC HANDLING
	isMusicPaused = false;
	hasPausedVisualizations = false;
	musicCounter = 0;
	myPlayer.load(musicList[musicCounter] + ".mp3");
	fftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++) {
		fftSmooth[i] = 0;
	}
	//we are just messing with shapes so we don't need a high band
	//bands = 64; //EDITING THIS IN GUI BEFORE MAKING IT PERMANENT
	myPlayer.play();
	//myPlayer.setVolume(0);
	toggleVisuals = false;

	//hackandslash
	previousTempCalculation = 0.0f;
	calculationThreshold = 1.0f;

}

//--------------------------------------------------------------
void ofApp::update(){
	//music handling 
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
	}

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
				if (triggerMusicVisualization) {
					
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
				}
				else {
					(*itr)->setRadius((*itr)->getOriginalRadius());
					if (triggerMultiColorGradient) {
						(*itr)->drawCircleX(x, color);
					}
					else {
						(*itr)->drawCircleX(x, singleFractalColor);
					}
				}
				angle += angleVar;
			}
		}
		else if (!triggerXMotion && triggerYMotion) {
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
				float y = ofMap(sin(angle), -1, 1, 0, float(ofGetWindowHeight()));
				if (triggerMusicVisualization) {
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
				}
				else {
					(*itr)->setRadius((*itr)->getOriginalRadius());
					if (triggerMultiColorGradient) {
						(*itr)->drawCircleY(y, color);
					}
					else {
						(*itr)->drawCircleY(y, singleFractalColor);
					}

				}
				angle += angleVar;
			}

		}
		else if (triggerXMotion && triggerYMotion)
		{
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
				float y = ofMap(sin(angle), -1, 1, 0, float(ofGetWindowHeight()));
				float x = ofMap(cos(angle), -1, 1, 0, float(ofGetWindowWidth()));
				if (triggerMusicVisualization) {
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
				}
				else {
					(*itr)->setRadius((*itr)->getOriginalRadius());
					if (triggerMultiColorGradient) {
						(*itr)->drawCircleXY(x, y, color);
					}
					else {
						(*itr)->drawCircleXY(x, y, singleFractalColor);
					}
				}
				angle += angleVar;
			}
		}
		else
		{
			for (vector<FractalCircle*>::iterator itr = circles.begin(); itr != circles.end(); ++itr) {
				if (triggerMusicVisualization) {
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
				}
				else {
					(*itr)->setRadius((*itr)->getOriginalRadius());
					if (triggerMultiColorGradient) {
						(*itr)->drawCircle(color);
					}
					else {
						(*itr)->drawCircle(singleFractalColor);
					}
				}
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
	else if (key == 's') {
		screenshottedImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshottedImage.save(screenShot.toString() + ".png");
		screenShot.set("Screenshot Saved!");
	}
	else if (key == OF_KEY_RETURN) {
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
