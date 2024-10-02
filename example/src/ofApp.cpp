#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofDrawBitmapString("Press spacebar to open an image, \"s\" to save the processed output", 20, 15);

	for (unsigned int i = 0; i < loadedImages.size(); i++) {
		loadedImages[i].draw(0, 20);
	}

	for (unsigned int i = 0; i < processedImages.size(); i++) {
		processedImages[i].draw(processedImages[i].getWidth(), 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {

		//Open the Open File Dialog
		auto selection = pfd::open_file("Select an image", ".",
			{ "Image Files", "*.png *.jpg *.jpeg *.bmp"}).result();

		if (selection.size() > 0) {
			processOpenFileSelection(selection[0]);
		}
	}

	if (key == 's') {

		if (processedImages.size() == 0) {
			//User is trying to save without anything to output - bail
			return;
		}

		auto destination = pfd::save_file("Save file", ".",
			{ "Image Files", "*.png *.jpg *.jpeg *.bmp"}).result();

		processedImages[0].saveImage(destination);

	}
}

//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction(ofColor i, ofColor j) {
	return (i.getBrightness() < j.getBrightness());
}

void ofApp::processOpenFileSelection(std::string openFileResult) {

	ofFile file(openFileResult);

	if (file.exists()) {
		//Limiting this example to one image so we delete previous ones
		processedImages.clear();
		loadedImages.clear();

		ofLogVerbose("The file exists - now checking the type via file extension");
		std::string fileExtension = ofToUpper(file.getExtension());

		//Save the file extension to use when we save out
		originalFileExtension = fileExtension;

		//Load the selected image
		ofImage image;
		image.load(openFileResult);
		if (image.getWidth() > ofGetWidth() || image.getHeight() > ofGetHeight())
		{
			image.resize(image.getWidth() / 2, image.getHeight() / 2);
		}
		loadedImages.push_back(image);

		//Make some short variables 
		int w = image.getWidth();
		int h = image.getHeight();

		//Make a new image to save manipulation by copying the source
		ofImage processedImage = image;

		//Walk through the pixels
		for (int y = 0; y < h; y++) {

			//Create a vector to store and sort the colors
			vector<ofColor> colorsToSort;

			for (int x = 0; x < w; x++) {

				//Capture the colors for the row
				ofColor color = image.getColor(x, y);
				colorsToSort.push_back(color);
			}

			//Sort the colors for the row
			sort(colorsToSort.begin(), colorsToSort.end(), sortColorFunction);

			for (int x = 0; x < w; x++)
			{
				//Put the sorted colors back in the new image
				processedImage.setColor(x, y, colorsToSort[x]);
			}
		}
		//Store the processed image
		processedImages.push_back(processedImage);
	}

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
