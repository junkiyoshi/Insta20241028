#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font_size = 40;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 0.72);

	string word =   " junkiyoshi.com anthology(); 2024/11/09 - 2024/11/17 ";
	int sample_count = 180;
	auto noise_param = ofRandom(1000);

	for (int k = 0; k < 20; k++) {

		auto y = ofMap(k, 0, 20, -1000, 1000);

		for (int i = 0; i < word.size(); i++) {

			ofPath chara_path = this->font.getCharacterAsPoints(word[i % word.size()], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			auto deg = i * 7.f;
			auto noise_value = (int)ofMap(ofNoise(cos(deg * DEG_TO_RAD) * 0.5, sin(deg * DEG_TO_RAD) * 0.5, ofGetFrameNum() * 0.02), 0, 1, 0, 10);
			auto noise_y = ofMap(noise_value, 0, 10, -250, 250);

			ofFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 330);

					auto rotation_y = glm::rotate(glm::mat4(), (i * 7.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation_y;
					location.y += y + noise_y;

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(155, 155, 255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 330);

					auto rotation_y = glm::rotate(glm::mat4(), (i * 7.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation_y;
					location.y += y + noise_y;

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}

	this->cam.end();

	/*
	int start = 270;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}