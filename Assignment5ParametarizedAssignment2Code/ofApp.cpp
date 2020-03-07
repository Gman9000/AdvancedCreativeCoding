#include "ofApp.h"
#include <iterator>

ofImage screenshottedImage;
//--------------------------------------------------------------
void ofApp::setup() {
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	gui.add(triggerFill.set("Trigger Fill", true));
	gui.add(lineWidth.set("line Width", 1, 1, 20));
	gui.add(maxCircleSize.set("max Circle size", 30.0f, 0.0f, 60.0f));
	gui.add(minCircleSize.set("min Circle Size", 5.0f, 0.0f, 15.0f));
	gui.add(xSpacing.set("x Spacing", 50, 50, 150));
	gui.add(ySpacing.set("y spacing", 50, 50, 150));
	gui.add(circleResolution.set("Circle Resolution", 5, 3, 12));
	gui.add(redComponent.set("Red Color Component", 50, 0, 255));
	gui.add(greenComponent.set("Green Color Component", 100, 0, 255));
	gui.add(blueComponent.set("Blue Color Component", 150, 0, 255));
	gui.add(alphaComponent.set("alpha Color Component", 250, 100, 255));
	gui.add(movementModifierX.set("X movement modifier", 3, 1, 10));
	gui.add(movementModifierY.set("Y movement modifier", 3, 1, 10));
	gui.add(rotationModifier.set("Rotation Speed", 20, 10, 30));
	gui.add(increasingSizeModifier.set("Increasing Size modifier", 0.00015f, 0.00010f, 0.00050f));
	gui.add(decreasingSizeModifier.set("Decreasing Size modifier", 0.00015f, 0.00010f, 0.00050f));
	//gui.add(increasingSizeModifier.set("Increasing Size modifier", 1.0f, 0.5f, 2.0f));
	//gui.add(decreasingSizeModifier.set("Decreasing Size modifier", 1.0f, 0.5f, 2.0f));
	gui.add(isIncreasingMovementX.set("Move Opposite CurrentX", true));
	gui.add(isIncreasingMovementY.set("Move Opposite CurrentY", true));
	gui.add(triggerTheColors.set("Trigger Colors!", false));
	gui.add(triggerTheRotation.set("Trigger Rotation!", true));
	gui.add(triggerMultiColorGradient.set("Trigger Multi Gradient!", false));
	gui.add(triggerGradientShifter.set("Trigger Gradient Shifter!", false));
	gui.add(gradientShifter.set("Gradient Shifter", 1, 0, 255));
	gui.add(triggerGradientBrightness.set("TriggerGradientBrightness!", false));
	gui.add(gradientBrightness.set("GradientBrightness", 254, 0, 255));
	gui.add(triggerSingleColorGradient.set("Trigger Single Gradient!", false));
	gui.add(singleGradientcolorChoice.set("Single Gradient Color", ofColor(255, 0, 0), ofColor(0), ofColor(255)));
	gui.add(backgroundColor.set("background Color", ofColor(0, 0, 0), ofColor(0), ofColor(255)));
	gui.add(screenShot.set("Screenshot"));
	isPaused = false;

	//Gradient Stuff
	isIncreasingGradientBrightness = true;
	hueValue = 0;
	saturationValue = 0;

	//for in triggerGradientShift Mode
	isIncreasingGradientShift = true;
	maxGradientBrightnessShift = 255;
	minGradientBrightnessShift = 0;

	//sizeModifier = 0.00015f;
	isIncreasingSize = true;
	//maxCircleSize = 30.0f;
	currentCircleSize = 15.0f;
	//minCircleSize = 5.0f;

	//for in trigger the colors mode
	maxColor = 255;
	minColor = 0;

	//starting positions for moving the art
	movementX = 1;
	movementY = 500;

	//screen size
	//window_width = 1900;
	window_width = ofGetWidth();
	//window_height = 1000;
	window_height = ofGetHeight();


	//movementModifier = 3;


	ofSetWindowShape(window_width, window_height);
	//different frame rates makes the artwork really interesting. i'm really digging the 30fps perspective
	//ofSetFrameRate(60);
	//ofSetFrameRate(15);
	ofSetFrameRate(30);
	ofSetBackgroundColor(0, 0, 0); //pure black
	
	//MUSIC HANDLING
	musicCounter = 0;
	myPlayer.load(musicList[musicCounter] + ".mp3");
	myPlayer.play();



}

//--------------------------------------------------------------
void ofApp::update() {
	if (triggerFill) {
		ofSetLineWidth(1);
		ofFill();
	}
	else {
		ofSetLineWidth(lineWidth);
		ofNoFill();
	}
	ofSetBackgroundColor(backgroundColor);
	if (!myPlayer.isPlaying() && !isPaused) {
		++musicCounter;
		int lengthOfArray = sizeof(musicList) / sizeof(*musicList); //THIS ACTUALLY WORKED WHICH IS JUST WOW
		if (musicCounter >= lengthOfArray ) {
			musicCounter = 0;
		}
		myPlayer.load(musicList[musicCounter] + ".mp3");
		myPlayer.play();
	}

	if (window_width != ofGetWidth()) {
		window_width = ofGetWidth();
	}
	if (window_height != ofGetHeight()) {
		window_height = ofGetHeight();
	}
	
	if ((triggerMultiColorGradient || triggerSingleColorGradient) && triggerGradientShifter && !triggerGradientBrightness) {
		triggerGradientBrightness.set("TriggerGradientBrightness!", false);
		if (isIncreasingGradientShift)
		{
			++gradientShifter;
		}
		else {
			--gradientShifter;
		}
	}
	else if ((triggerMultiColorGradient || triggerSingleColorGradient) && !triggerGradientShifter && triggerGradientBrightness) {
		triggerGradientShifter.set("Trigger Gradient Shifter!", false);
		if (isIncreasingGradientBrightness)
		{
			++gradientBrightness;
		}
		else {
			--gradientBrightness;
		}
	}

	//toggles between increasing and decreasing gradient shifts
	if (gradientShifter >= maxGradientBrightnessShift) {
		isIncreasingGradientShift = false;
	}
	else if (gradientShifter <= minGradientBrightnessShift) {
		isIncreasingGradientShift = true;
	}

	//toggles between increasing and decreasing brightness shifts
	if (gradientBrightness >= maxGradientBrightnessShift) {
		isIncreasingGradientBrightness = false;
	}
	else if (gradientBrightness <= minGradientBrightnessShift) {
		isIncreasingGradientBrightness = true;
	}
	//ofSetColor(redComponent, greenComponent, blueComponent);
	ofSetCircleResolution(circleResolution);
	//increase/decrease each component color separately to show a better range of colors for our pulsating circles
	if ((!triggerMultiColorGradient && !triggerSingleColorGradient) && triggerTheColors) {
		if (isIncreasingRColor) { 
			++redComponent;
		}
		else {
			--redComponent;
		}

		if (isIncreasingGColor) {
			++greenComponent;
		}
		else {
			--greenComponent;
		}

		if (isIncreasingBColor) {
			++blueComponent;
		}
		else {
			--blueComponent;
		}
		ofSetColor(redComponent, greenComponent, blueComponent);


		//toggles between incrementing and decrementing the color components when they hit certain minimums/maximums 
		if (redComponent >= maxColor) {
			isIncreasingRColor = false;
		}
		else if (redComponent <= minColor) {
			isIncreasingRColor = true;
		}

		if (greenComponent >= maxColor) {
			isIncreasingGColor = false;
		}
		else if (greenComponent <= minColor) {
			isIncreasingGColor = true;
		}

		if (blueComponent >= maxColor) {
			isIncreasingBColor = false;
		}
		else if (blueComponent <= minColor) {
			isIncreasingBColor = true;
		}
	}
	if(!triggerTheColors && !triggerMultiColorGradient && !triggerSingleColorGradient){
		ofSetColor(redComponent, greenComponent, blueComponent,alphaComponent);
	}
	if (!triggerMultiColorGradient && !triggerSingleColorGradient) {
		triggerGradientShifter.set("Trigger Gradient Shifter!", false);
		triggerGradientBrightness.set("TriggerGradientBrightness!", false);
	}


	

	//toggles between increasing and decreasing circle size
	if (currentCircleSize >= maxCircleSize) {
		isIncreasingSize = false;
	}
	else if (currentCircleSize <= minCircleSize) {
		isIncreasingSize = true;
	}

	//toggles between moving left and right
	if (movementX >= window_width) {
		isIncreasingMovementX = false;
	}
	if (movementX <= 0) {
		isIncreasingMovementX = true;
	}
	//toggles between moving up and down
	if (movementY >= window_height) {
		isIncreasingMovementY = false;
	}
	if (movementY <= 0) {
		isIncreasingMovementY = true;
	}

	//updates the movement in X direction
	if (isIncreasingMovementX) {
		movementX += movementModifierX;
	}
	else {
		movementX -= movementModifierX;
	}

	//updates the movement in Y direction
	if (isIncreasingMovementY) {
		movementY += movementModifierY;
	}
	else {
		movementY -= movementModifierY;
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	//draw the circles for each row and each column
	for (int x = -window_width; x < window_width + 50; x += xSpacing)
	{
		if (triggerMultiColorGradient) {
			color = singleGradientcolorChoice;
			color.set(color.r, color.g, color.b, alphaComponent);
			triggerTheColors.set("Trigger Colors!", false);
			triggerSingleColorGradient.set("Trigger Single Gradient!", false);
			hueValue = gradientShifter + ofMap(x, -window_width, window_width + 50, 0, 255);
			color.setHsb( hueValue % 255, 255, gradientBrightness);
			ofSetColor(color);
		}
		else if (triggerSingleColorGradient) {
			triggerTheColors.set("Trigger Colors!", false);
			triggerMultiColorGradient.set("Trigger Multi Gradient!", false);
			color = singleGradientcolorChoice;
			color.set(color.r, color.g, color.b, alphaComponent);
			saturationValue = gradientShifter + ofMap(x, -window_width, window_width + 50, 0, 255);
			//color.setHsb(color.getHue(), saturationValue, gradientBrightness);
			color.setHsb(color.getHue(), saturationValue - (int(saturationValue / 255) * (saturationValue % 255)), gradientBrightness);
			ofSetColor(color);
		}
		for (int y = -window_height; y < window_height + 50; y += ySpacing)
		{
			if (isIncreasingSize) {
				currentCircleSize += increasingSizeModifier;
				if(triggerTheRotation){
					ofPushMatrix();
					ofTranslate(x + 25 + movementX, y + 25 + movementY);
					ofRotateZ(ofGetElapsedTimef() * rotationModifier);
					ofCircle(0, 0, currentCircleSize);
					ofPopMatrix();
				}
				else {
					ofCircle(x + 25 + movementX, y + 25 + movementY, currentCircleSize);
				}
			}
			else {
				currentCircleSize -= decreasingSizeModifier;
				if (triggerTheRotation) {
					ofPushMatrix();
					ofTranslate(x + 25 + movementX, y + 25 + movementY);
					ofRotateZ(ofGetElapsedTimef() * rotationModifier);
					ofCircle(0, 0, currentCircleSize);
					ofPopMatrix();
				}
				else {
					ofCircle(x + 25 + movementX, y + 25 + movementY, currentCircleSize);
				}
			}

		}
	}


	if (isDrawingGui) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'x') {
		isDrawingGui = !isDrawingGui;
	}
	else if (key == 's') {
		screenshottedImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshottedImage.save(screenShot.toString() + ".png");
		screenShot.set("Screenshot Saved!");
	}
	else if (key == OF_KEY_RETURN) {
		if (myPlayer.isPlaying()) {
			isPaused = true;
			myPlayer.stop();
		}
		else {
			isPaused = false;
			myPlayer.play();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
