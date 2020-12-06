#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    redisContext *conn = NULL;
    redisReply *resp   = NULL;
    conn = redisConnect( "127.0.0.1" , 6379);
    if( ( NULL != conn ) && conn->err ){
      printf("error : %s\n" , conn->errstr );
      redisFree( conn );
        return;
    }else if( NULL == conn ){
        return;
    }
    resp = (redisReply *) redisCommand( conn, "GET sample");
    if( NULL == resp ){
        redisFree( conn );
        return;
    }
    if( REDIS_REPLY_ERROR == resp->type ){
        redisFree( conn );
        freeReplyObject( resp );
        return;
    }
    printf( "sample : %s\n" , resp->str );
    freeReplyObject( resp );
    redisFree( conn );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, radius);
    gui.begin();
    ImGui::SliderFloat("Float", &radius, 0.0f, 100.0f);
    gui.end();
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
