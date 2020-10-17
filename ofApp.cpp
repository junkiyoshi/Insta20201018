#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
}

//--------------------------------------------------------------
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(90);

	int span = 15;
	ofMesh face, frame;
	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	float frame_step = 0.04;
	float len_step = 0.002;
	for (float len = ofGetWidth(); len > 0; len -= span) {

		int index = face.getNumVertices();

		auto loc = glm::vec3(
			len * ofMap(ofNoise(this->noise_param.x, ofGetFrameNum() * frame_step + len * len_step), 0, 1, 0, 0.5),
			len * ofMap(ofNoise(this->noise_param.y, ofGetFrameNum() * frame_step + len * len_step), 0, 1, 0, 0.5),
			len * ofMap(ofNoise(this->noise_param.z, ofGetFrameNum() * frame_step + len * len_step), 0, 1, 0, 0.5)
		);

		auto next = glm::vec3(
			(len - span) * ofMap(ofNoise(this->noise_param.x, ofGetFrameNum() * frame_step + (len - span) * len_step), 0, 1, 0, 0.5),
			(len - span) * ofMap(ofNoise(this->noise_param.y, ofGetFrameNum() * frame_step + (len - span) * len_step), 0, 1, 0, 0.5),
			(len - span) * ofMap(ofNoise(this->noise_param.z, ofGetFrameNum() * frame_step + (len - span) * len_step), 0, 1, 0, 0.5)
		);

		face.addVertex(glm::vec3(loc.x, loc.y, loc.z));
		face.addVertex(glm::vec3(-loc.x, loc.y, loc.z));
		face.addVertex(glm::vec3(-next.x, next.y, next.z));
		face.addVertex(glm::vec3(next.x, next.y, next.z));

		frame.addVertex(glm::vec3(loc.x, loc.y, loc.z));
		frame.addVertex(glm::vec3(-loc.x, loc.y, loc.z));
		frame.addVertex(glm::vec3(-next.x, next.y, next.z));
		frame.addVertex(glm::vec3(next.x, next.y, next.z));

		face.addIndex(index + 0); face.addIndex(index + 1); face.addIndex(index + 2);
		face.addIndex(index + 0); face.addIndex(index + 2); face.addIndex(index + 3);

		frame.addIndex(index + 0); frame.addIndex(index + 3);
		frame.addIndex(index + 1); frame.addIndex(index + 2);
	}

	frame.addIndex(0); frame.addIndex(1);
	frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);


	for (int i = 0; i < 4; i++) {

		ofRotateX(90);

		ofSetColor(39);
		face.draw();

		ofSetColor(239);
		frame.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}