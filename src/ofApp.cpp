#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  gui.setup();
  redisContext *conn = NULL;
  redisReply *resp = NULL;
  conn = redisConnect("127.0.0.1", 6379);
  if ((NULL != conn) && conn->err) {
    printf("error : %s\n", conn->errstr);
    redisFree(conn);
    return;
  } else if (NULL == conn) {
    return;
  }
  radius = guiParameter<float>(conn, "radius");
  flag = guiParameter<bool>(conn, "flag");
  int loopnum = 100000;
  int tmp = 0;
  float start = ofGetElapsedTimef();
  for (int i = 0; i < loopnum; i++) {
    tmp = i;
  }
  float end = ofGetElapsedTimef();
  ofLogNotice("normal int") << float(end - start);

  intvalue = guiParameter<int>(conn, "intvalue");
  start = ofGetElapsedTimef();
  for (int i = 0; i < loopnum; i++) {
    intvalue.setValue(i);
    intvalue.dbsync();
  }
  end = ofGetElapsedTimef();
  ofLogNotice("guiParameter int") << float(end - start);
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  if (flag.getValue()) {
    ofSetColor(255, 0, 0);
  } else {
    ofSetColor(255, 255, 255);
  }
  ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, radius.getValue());
  gui.begin();
  if (ImGui::SliderFloat("Float", radius.getValuePtr(), 0.0f, 100.0f)) {
    radius.dbsync();
  }
  if (ImGui::Checkbox("Bool", flag.getValuePtr())) {
    flag.dbsync();
  }
  gui.end();
}

//--------------------------------------------------------------
void ofApp::exit() {
  freeReplyObject(resp);
  redisFree(conn);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
