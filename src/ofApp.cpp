#include "ofApp.h"
#include "msgpack.hpp"
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
  radius = guiParameter(conn, "radius");
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, radius.getValue());
  gui.begin();
  if (ImGui::SliderFloat("Float", radius.getValuePtr(), 0.0f, 100.0f)) {
    radius.dbsync();
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
