#pragma once

#include "guiParameter.hpp"
#include "hiredis.h"
#include "ofMain.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
  void exit();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  ofxImGui::Gui gui;
  guiParameter<float> radius;
  guiParameter<bool> flag;
  guiParameter<int> intvalue;
  redisContext *conn = NULL;
  redisReply *resp = NULL;

  float start;
};
