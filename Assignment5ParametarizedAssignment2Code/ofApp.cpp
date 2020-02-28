#include "ofApp.h"
ofImage screenshottedImage;

//--------------------------------------------------------------
void ofApp::setup() {
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	gui.add(circleResolution.set("Circle Resolution", 5, 3, 12));
	gui.add(redComponent.set("Red Color Component", 50, 0, 255));
	gui.add(greenComponent.set("Green Color Component", 100, 0, 255));
	gui.add(blueComponent.set("Blue Color Component", 150, 0, 255));
	gui.add(movementModifierX.set("X movement modifier", 3, 1, 10));
	gui.add(movementModifierY.set("Y movement modifier", 3, 1, 10));
	gui.add(rotationModifier.set("Rotation Speed", 20, 10, 30));
	gui.add(increasingSizeModifier.set("Increasing Size modifier", 0.00015f, 0.00010f, 0.00050f));
	gui.add(decreasingSizeModifier.set("Decreasing Size modifier", 0.00015f, 0.00010f, 0.00050f));
	gui.add(isIncreasingMovementX.set("Move Opposite CurrentX", true));
	gui.add(isIncreasingMovementY.set("Move Opposite CurrentY", true));
	gui.add(triggerTheColors.set("Trigger The Colors!", false));
	gui.add(triggerTheRotation.set("Trigger The Rotation!", true));
	gui.add(screenShot.set("Screenshot"));



	//sizeModifier = 0.00015f;
	isIncreasingSize = true;
	maxCircleSize = 30.0f;
	currentCircleSize = 15.0f;
	minCircleSize = 5.0f;

	//for in trigger the colors mode
	maxColor = 255;
	minColor = 0;

	//starting positions for moving the art
	movementX = 1;
	movementY = 500;

	//screen size
	window_width = 1900;
	window_height = 1000;

	//isIncreasingMovementX = true;
	//isIncreasingMovementY = true;

	//movementModifier = 3;


	ofSetWindowShape(window_width, window_height);
	//different frame rates makes the artwork really interesting. i'm really digging the 30fps perspective
	//ofSetFrameRate(60);
	//ofSetFrameRate(15);
	ofSetFrameRate(30);
	ofSetBackgroundColor(0, 0, 0); //pure black
}

//--------------------------------------------------------------
void ofApp::update() {
	//ofSetColor(redComponent, greenComponent, blueComponent);
	ofSetCircleResolution(circleResolution);
	//increase/decrease each component color separately to show a better range of colors for our pulsating circles
	if (triggerTheColors) {
		if (isIncreasingRColor) {
			++redComponent;
			ofSetColor(redComponent, greenComponent, blueComponent);
		}
		else {
			--redComponent;
			ofSetColor(redComponent, greenComponent, blueComponent);
		}

		if (isIncreasingGColor) {
			++greenComponent;
			ofSetColor(redComponent, greenComponent, blueComponent);
		}
		else {
			--greenComponent;
			ofSetColor(redComponent, greenComponent, blueComponent);
		}

		if (isIncreasingBColor) {
			++blueComponent;
			ofSetColor(redComponent, greenComponent, blueComponent);
		}
		else {
			--blueComponent;
			ofSetColor(redComponent, greenComponent, blueComponent);
		}
	}
	else {
		ofSetColor(redComponent, greenComponent, blueComponent);
	}

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
	for (int x = -window_width; x < window_width + 50; x += 50)
	{
		for (int y = -window_height; y < window_height + 50; y += 50)
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
