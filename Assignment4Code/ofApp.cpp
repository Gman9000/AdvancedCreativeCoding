#include "ofApp.h"
#include "/Users/granv/Documents/of/of_v0.11.0_vs2017_release/apps/myApps/Assignment4Alt/Shape.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1000, 1000);
	ofSetFrameRate(60);

	bigEllipse = Shape(750,150,500,300, ofColor::brown);
	ellipseImage.loadImage("roundabout.jpg");
	eyesImage.loadImage("eyes.jpg");
	sneakerImage.loadImage("sneaks.jpg");
	leftHornOfSneaker.cropFrom(sneakerImage, 200, 300, 100, 100);
	rightHornOfSneaker.cropFrom(sneakerImage, 1600, 300, 100, 100);

	for (int i = 0; i < 400; i++) {
		shapesForImage1.push_back(Shape(ofRandom(600,900), ofRandom(50,250), ofRandom(40), ofRandom(60), ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 125)));
	}
	for (int i = 0; i < 200; i++) {
		shapesForImage1.push_back(Shape(ofRandom(525, 975), ofRandom(100, 200), ofRandom(40), ofRandom(60), ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 125)));
	}
	for (int i = 0; i < 4000; i++) {
		shapesForImage2.push_back(Shape(ofRandom(500, 1000), ofRandom(300, 600), 1, 1, ofColor(0, 0, 0, 255)));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
//runs every frame
void ofApp::draw(){
	//============================================

	bigEllipse.draw();
	ofSetColor(255);
	ellipseImage.draw(0, 0, 500,300);
	for (Shape &s : shapesForImage1) {
		s.draw();
	}
	//============================================
	ofSetColor(255);
	eyesImage.draw(0, 300, 500, 300);
	ofSetColor(ofColor::beige);
	ofDrawRectangle(500, 300, 500, 300);
	for (Shape &s : shapesForImage2) {
		s.draw();
	}
	ofSetColor(ofColor::forestGreen);
	ofDrawEllipse(650, 525, 100, 150);
	ofDrawEllipse(850, 525, 100, 150);
	ofSetColor(ofColor::slateGray);
	ofDrawEllipse(650, 530, 70, 90);
	ofDrawEllipse(850, 530, 70, 90);
	//============================================
	ofSetColor(255);
	sneakerImage.draw(0, 600, 500, 300);
	sneakerImage.draw(500, 600, 500, 300);
	leftHornOfSneaker.draw(500, 600, 100, 100);
	rightHornOfSneaker.draw(700, 600, 100, 100);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
